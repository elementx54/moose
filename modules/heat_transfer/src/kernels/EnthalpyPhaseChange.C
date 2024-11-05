//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EnthalpyPhaseChange.h"

registerMooseObject("HeatTransferApp", EnthalpyPhaseChange);
registerMooseObject("HeatTransferApp", ADEnthalpyPhaseChange);

template <bool is_ad>
InputParameters
EnthalpyPhaseChangeTempl<is_ad>::validParams()
{
  InputParameters params = EnthalpyPhaseChangeParent<is_ad>::validParams();
  params.addClassDescription(
      "Phase change term $(\\nabla S, \\nabla \\psi)$ of the "
      "enthalpy form of the heat equation.");
  // Density may change with deformation, so must integrate over current volume.
  params.set<bool>("use_displaced_mesh") = true;
  params.addRequiredCoupledVar("S_enthalpy", "S value in enthalpy form of the heat equation.");
  return params;
}

template <bool is_ad>
EnthalpyPhaseChangeTempl<is_ad>::EnthalpyPhaseChangeTempl(const InputParameters & parameters)
  : EnthalpyPhaseChangeParent<is_ad>(parameters),
    _grad_S(this->template coupledGenericGradient<is_ad>("S_enthalpy"))
{
}

template <bool is_ad>
EnthalpyPhaseChangeRealGrad<is_ad>
EnthalpyPhaseChangeTempl<is_ad>::precomputeQpResidual()
{
  return _grad_S[_qp];
}

template class EnthalpyPhaseChangeTempl<false>;
template class EnthalpyPhaseChangeTempl<true>;
