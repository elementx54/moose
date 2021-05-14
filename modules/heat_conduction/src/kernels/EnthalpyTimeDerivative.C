//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EnthalpyTimeDerivative.h"

registerMooseObject("HeatConductionApp", EnthalpyTimeDerivative);
registerMooseObject("HeatConductionApp", ADEnthalpyTimeDerivative);

template <bool is_ad>
InputParameters
EnthalpyTimeDerivativeTempl<is_ad>::validParams()
{
  InputParameters params = EnthalpyTimeDerivativeParent<is_ad>::validParams();
  params.addClassDescription(
      "Time derivative term $\\rho \\frac{\\partial E}{\\partial t}$ of "
      "the enthalpy form of the heat equation for quasi-constant density $\\rho$.");
  // Density may change with deformation, so must integrate over current volume.
  params.set<bool>("use_displaced_mesh") = true;
  params.addParam<MaterialPropertyName>("density_name", "density", "Name of density material property.");
  return params;
}

template <bool is_ad>
EnthalpyTimeDerivativeTempl<is_ad>::EnthalpyTimeDerivativeTempl(const InputParameters & parameters)
  : EnthalpyTimeDerivativeParent<is_ad>(parameters),
    _density(this->template getGenericMaterialProperty<Real, is_ad>(
          this->template getParam<MaterialPropertyName>("density_name")))
{
}

template <bool is_ad>
GenericReal<is_ad>
EnthalpyTimeDerivativeTempl<is_ad>::computeQpResidual()
{
  return _density[_qp] * this->_test[_i][_qp] * this->_u_dot[_qp];
}

template <>
Real
EnthalpyTimeDerivativeTempl<true>::computeQpJacobian()
{
  mooseError("Internal error. computeQpJacobian should not be called with AD.");
}

template <>
Real
EnthalpyTimeDerivativeTempl<false>::computeQpJacobian()
{
  return _density[_qp] * this->_test[_i][_qp] * this->_phi[_j][_qp] * this->_du_dot_du[_qp];
}

template class EnthalpyTimeDerivativeTempl<false>;
template class EnthalpyTimeDerivativeTempl<true>;
