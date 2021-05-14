//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "TimeKernel.h"
#include "ADTimeKernel.h"

// Select the parent class base on the is_ad boolean parameter.
template <bool is_ad>
using EnthalpyTimeDerivativeParent = typename std::conditional<is_ad,
      ADTimeKernel, TimeKernel>::type;

/**
 * Kernel class for the time derivative term multipled by density for the
 * enthalpy form of the heat conduction governing equation.
 */
template <bool is_ad>
class EnthalpyTimeDerivativeTempl : public EnthalpyTimeDerivativeParent<is_ad>
{
public:
  /// Constructor for the time derivative term.
  static InputParameters validParams();
  EnthalpyTimeDerivativeTempl(const InputParameters & params);

protected:
  /// Computes the residual from the time derivative.
  virtual GenericReal<is_ad> computeQpResidual();
  /// Compute jacobian of the time derivative.
  virtual Real computeQpJacobian();

  /// Density material property.
  const GenericMaterialProperty<Real, is_ad> & _density;

  using KernelBase::_qp;
  using KernelBase::_i;
  using KernelBase::_j;
};

typedef EnthalpyTimeDerivativeTempl<false> EnthalpyTimeDerivative;
typedef EnthalpyTimeDerivativeTempl<true> ADEnthalpyTimeDerivative;
