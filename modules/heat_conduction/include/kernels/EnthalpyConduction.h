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
using EnthalpyConductionParent = typename std::conditional<is_ad,
      ADKernelGrad, KernelGrad>::type;
// Couldn't find a GenericRealGradient.
template <bool is_ad>
using EnthalpyConductionRealGrad = typename std::conditional<is_ad,
      ADRealGradient, RealGradient>::type;

/**
 * Kernel class for the conduction-like term containing Gamma in the enthalpy
 * form of the heat conduction governing equation.
 */
template <bool is_ad>
class EnthalpyConductionTempl : public EnthalpyConductionParent<is_ad>
{
public:
  /// Constructor for the conduction-like term.
  static InputParameters validParams();
  EnthalpyConductionTempl(const InputParameters & params);

protected:
  /// Computes the reidual from the conduction-like term.
  virtual EnthalpyConductionRealGrad<is_ad> precomputeQpResidual();
  /// Compute jacobian of the conduction-like term.
  virtual RealGradient precomputeQpJacobian();

  /// Gamma material property.
  const GenericMaterialProperty<Real, is_ad> & _gamma;

  using KernelBase::_qp;
  using KernelBase::_j;
};

typedef EnthalpyConductionTempl<false> EnthalpyConduction;
typedef EnthalpyConductionTempl<true> ADEnthalpyConduction;
