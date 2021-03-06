//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PINSFVEnergyEffectiveDiffusion.h"
#include "INSFVEnergyVariable.h"

registerMooseObject("NavierStokesApp", PINSFVEnergyEffectiveDiffusion);

InputParameters
PINSFVEnergyEffectiveDiffusion::validParams()
{
  auto params = FVFluxKernel::validParams();
  params.addClassDescription(
      "Effective diffusion term in the porous media incompressible Navier-Stokes "
      "equations : $-div(kappa grad(T))");
  params.addRequiredParam<MaterialPropertyName>("kappa", "Effective thermal conductivity");
  params.set<unsigned short>("ghost_layers") = 2;
  return params;
}

PINSFVEnergyEffectiveDiffusion::PINSFVEnergyEffectiveDiffusion(const InputParameters & params)
  : FVFluxKernel(params),
    _kappa_elem(getADMaterialProperty<Real>("kappa")),
    _kappa_neighbor(getNeighborADMaterialProperty<Real>("kappa"))
{
#ifndef MOOSE_GLOBAL_AD_INDEXING
  mooseError("PINSFV is not supported by local AD indexing. In order to use PINSFV, please run the "
             "configure script in the root MOOSE directory with the configure option "
             "'--with-ad-indexing-type=global'");
#endif
  if (!dynamic_cast<INSFVEnergyVariable *>(&_var))
    mooseError("PINSFVEnergyEffectiveDiffusion may only be used with a fluid temperature variable, "
               "of variable type INSFVEnergyVariable.");
}

ADReal
PINSFVEnergyEffectiveDiffusion::computeQpResidual()
{
  // Interpolate thermal conductivity times porosity on the face
  ADReal k_eps_face;
  interpolate(Moose::FV::InterpMethod::Average,
              k_eps_face,
              _kappa_elem[_qp],
              _kappa_neighbor[_qp],
              *_face_info,
              true);

  // Compute the temperature gradient dotted with the surface normal
  auto dTdn = gradUDotNormal();

  return -k_eps_face * dTdn;
}
