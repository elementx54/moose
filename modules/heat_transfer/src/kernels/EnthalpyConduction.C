//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EnthalpyConduction.h"

registerMooseObject("HeatConductionApp", EnthalpyConduction);
registerMooseObject("HeatConductionApp", ADEnthalpyConduction);

template <bool is_ad>
InputParameters
EnthalpyConductionTempl<is_ad>::validParams()
{
  InputParameters params = EnthalpyConductionParent<is_ad>::validParams();
  params.addClassDescription(
      "Conduction-like term $(\\Gamma \\nabla E, \\nabla \\psi)$ of the "
      "enthalpy form of the heat equation.");
  // Density may change with deformation, so must integrate over current volume.
  params.set<bool>("use_displaced_mesh") = true;
  params.addParam<MaterialPropertyName>("gamma", "gamma", "Name of Gamma material property.");
  return params;
}

template <bool is_ad>
EnthalpyConductionTempl<is_ad>::EnthalpyConductionTempl(const InputParameters & parameters)
  : EnthalpyConductionParent<is_ad>(parameters),
    _gamma(this->template getGenericMaterialProperty<Real, is_ad>(
          this->template getParam<MaterialPropertyName>("gamma")))
{
}

template <bool is_ad>
EnthalpyConductionRealGrad<is_ad>
EnthalpyConductionTempl<is_ad>::precomputeQpResidual()
{
  return _gamma[_qp] * this->_grad_u[_qp];
}

template <>
RealGradient
EnthalpyConductionTempl<true>::precomputeQpJacobian()
{
  mooseError("Internal error. precomputeQpJacobian should not be called with AD.");
}

template <>
RealGradient
EnthalpyConductionTempl<false>::precomputeQpJacobian()
{
  return _gamma[_qp] * this->_grad_phi[_j][_qp];
}

template class EnthalpyConductionTempl<false>;
template class EnthalpyConductionTempl<true>;
