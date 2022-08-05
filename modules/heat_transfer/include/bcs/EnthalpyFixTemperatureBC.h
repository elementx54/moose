//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "GenericIntegratedBC.h"

/**
 * Boundary condition class for fixing a temperature at the boundary for the
 * enthalpy form of the heat conduction governing equation.
 */
template <bool is_ad>
class EnthalpyFixTemperatureBCTempl : public GenericIntegratedBC<is_ad>
{
public:
  /// Constructor for the fixed temperature BC.
  static InputParameters validParams();
  EnthalpyFixTemperatureBCTempl(const InputParameters & params);

protected:
  /// Computes the Dirichlet condition of the boundary
  virtual GenericReal<is_ad> computeQpResidual() override;

  /// Function describing the temperature boundary value.
  const Function & _funcT;
  /// Liquidus temperature of the material.
  const GenericMaterialProperty<Real, is_ad> & _liquidus;
  /// Solidus temperature of the material.
  const GenericMaterialProperty<Real, is_ad> & _solidus;
  /// Variable containing reference temperature linked to reference enthalpy.
  const GenericVariableValue<is_ad> & _ref_T;
  ///@{ Specific heat material property
  const GenericMaterialProperty<Real, is_ad> & _sp_cur;
  const MaterialProperty<Real> & _sp_old;
  ///@}
  /// Variable containing solid to liquid state
  const GenericVariableValue<is_ad> & _fracQ;
  /// Heat of fusion value.
  const Real _h_fusion;

  usingGenericIntegratedBCMembers;
};

typedef EnthalpyFixTemperatureBCTempl<false> EnthalpyFixTemperatureBC;
typedef EnthalpyFixTemperatureBCTempl<true> ADEnthalpyFixTemperatureBC;
