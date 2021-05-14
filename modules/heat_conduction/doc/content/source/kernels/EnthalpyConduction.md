# EnthalpyConduction

!syntax description /Kernels/EnthalpyConduction

## Description

This kernel implements the conduction-like term in the [enthalpy form](enthalpy_form.md)
of the heat equation whose weak form is

\begin{equation}
  (\Gamma \nabla E, \nabla \psi),
\end{equation}

where $\Gamma$ is related to the [Kirchhoff temperature](enthalpy_form.md)
definition and form, $E$ is enthalpy change from a reference enthalpy state,
and $\psi$ is the test function.

The Automatic differentiation (AD) version is also available by adding the
prefix `AD` to the name for the "type" parameter.

## Example Input Syntax

!listing test/tests/enthalpy_form/conduction/calc.i block=Kernels/cond_enth

!syntax parameters /Kernels/EnthalpyConduction

!syntax inputs /Kernels/EnthalpyConduction

!syntax children /Kernels/EnthalpyConduction
