//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EnthalpyFixTemperatureBC.h"

registerMooseObject("HeatConductionApp", EnthalpyFixTemperatureBC);
registerMooseObject("HeatConductionApp", ADEnthalpyFixTemperatureBC);

template <bool is_ad>
InputParameters
EnthalpyFixTemperatureBCTempl<is_ad>::validParams()
{
  InputParameters params = GenericIntegratedBC<is_ad>::validParams();
  params.addClassDescription("Fixed temperature boundary condition for the "
      "enthalpy form of the heat equation.");
  params.addRequiredParam<FunctionName>("bc_temperature_function", "Temperature at the boundary.");
  params.addParam<MaterialPropertyName>("liquidus", "liquidus",
      "Liquidus temperature material property.");
  params.addParam<MaterialPropertyName>("solidus", "solidus",
      "Solidus temperature material property.");
  params.addRequiredCoupledVar("reference_T", "Reference temperature variable.");
  params.addParam<MaterialPropertyName>("specific_heat", "specific_heat",
      "Specific heat material property name.");
  params.addRequiredCoupledVar("quality", "Fractional phase change variable.");
  params.addRequiredRangeCheckedParam<Real>("heat_fusion", "heat_fusion > 0.0",
      "Material's latent heat of fusion."); // I should probably change this to a material property, not declared here
  return params;
}

template <bool is_ad>
EnthalpyFixTemperatureBCTempl<is_ad>::EnthalpyFixTemperatureBCTempl(const InputParameters & parameters)
  : GenericIntegratedBC<is_ad>(parameters),
    _funcT(getFunction("bc_temperature_function")),
    _liquidus(this->template getGenericMaterialProperty<Real, is_ad>(
          this->template getParam<MaterialPropertyName>("liquidus"))),
    _solidus(this->template getGenericMaterialProperty<Real, is_ad>(
          this->template getParam<MaterialPropertyName>("solidus"))),
    _ref_T(this->template coupledGenericValue<is_ad>("reference_T")),
    _sp_cur(this->template getGenericMaterialProperty<Real, is_ad>(
          this->template getParam<MaterialPropertyName>("specific_heat"))),
    _sp_old(this->template getMaterialPropertyOld<Real>(
          this->template getParam<MaterialPropertyName>("specific_heat"))),
    _fracQ(this->template coupledGenericValue<is_ad>("quality")),
    _h_fusion(this->template getParam<Real>("heat_fusion"))
{
}

template <bool is_ad>
GenericReal<is_ad>
EnthalpyFixTemperatureBCTempl<is_ad>::computeQpResidual()
{
  GenericReal<is_ad> ret_value;
  const GenericReal<is_ad> sp_avg = (_sp_cur[_qp] + _sp_old[_qp]) / 2.0;
  // Given temperature and need to return change enthalpy from reference enthalpy.
  const auto bc_T = _funcT.value(_t, _q_point[_qp]);
  const auto deltaT_mush = _liquidus[_qp] - _solidus[_qp];
  if (bc_T > _liquidus[_qp])
  {
    // Boundary is completely liquid
    if (_ref_T[_qp] > _liquidus[_qp])
      ret_value = sp_avg * (bc_T - _ref_T[_qp]); // Both have already melted
    else if (_ref_T[_qp] < _solidus[_qp])
      ret_value = sp_avg * (bc_T - _ref_T[_qp]) + _h_fusion; // Still fully solid
    else
      ret_value = sp_avg * (bc_T - _ref_T[_qp]) + _h_fusion * (1.0 - _fracQ[_qp]); // Is melting
  }
  else if (bc_T < _solidus[_qp])
  {
    // Boundary is completely solid
    if (_ref_T[_qp] > _liquidus[_qp])
      ret_value = sp_avg * (bc_T - _ref_T[_qp]) - _h_fusion; // Is fully liquid
    else if (_ref_T[_qp] < _solidus[_qp])
      ret_value = sp_avg * (bc_T - _ref_T[_qp]); // Both are solid
    else
      ret_value = sp_avg * (bc_T - _ref_T[_qp]) - _h_fusion * _fracQ[_qp]; // Is solidifying
  }
  else
  {
    // At melting or mushy melting
    if (deltaT_mush == 0.0)
      mooseError("In",
                 _name,
                 ": Cannot set boundary to solidus and liquidus temperature.");
    if (_ref_T[_qp] > _liquidus[_qp])
      ret_value = sp_avg * (bc_T - _ref_T[_qp]) - _h_fusion * (
          _liquidus[_qp] - bc_T) / deltaT_mush; // Is partially solidifying
    else if (_ref_T[_qp] < _solidus[_qp])
      ret_value = sp_avg * (bc_T - _ref_T[_qp]) + _h_fusion * (
          bc_T - _solidus[_qp]) / deltaT_mush; // Is partially melting
    else
      ret_value = sp_avg * (bc_T - _ref_T[_qp]) + _h_fusion * (
          bc_T - _ref_T[_qp]) / deltaT_mush; // Stays mushy
  }
  return _u[_qp] - ret_value;
}

template class EnthalpyFixTemperatureBCTempl<false>;
template class EnthalpyFixTemperatureBCTempl<true>;
