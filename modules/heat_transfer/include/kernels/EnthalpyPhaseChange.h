//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "KernelGrad.h"
#include "ADKernelGrad.h"

// Select the parent class base on the is_ad boolean parameter.
template <bool is_ad>
using EnthalpyPhaseChangeParent = typename std::conditional<is_ad,
      ADKernelGrad, KernelGrad>::type;
// Couldn't find a GenericRealGradient.
template <bool is_ad>
using EnthalpyPhaseChangeRealGrad = typename std::conditional<is_ad,
      ADRealGradient, RealGradient>::type;

/**
 * Kernel class for the phase change term containing in the enthalpy
 * form of the heat conduction governing equation.
 */
template <bool is_ad>
class EnthalpyPhaseChangeTempl : public EnthalpyPhaseChangeParent<is_ad>
{
public:
  /// Constructor for the conduction-like term.
  static InputParameters validParams();
  EnthalpyPhaseChangeTempl(const InputParameters & params);

protected:
  /// Computes the reidual from the phase change term.
  virtual EnthalpyPhaseChangeRealGrad<is_ad> precomputeQpResidual();

  /// Gradient of S term
  const GenericVariableGradient<is_ad> & _grad_S;

  using KernelBase::_qp;
};

typedef EnthalpyPhaseChangeTempl<false> EnthalpyPhaseChange;
typedef EnthalpyPhaseChangeTempl<true> ADEnthalpyPhaseChange;
