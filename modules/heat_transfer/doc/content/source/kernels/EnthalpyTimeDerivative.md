# EnthalpyTimeDerivative

!syntax description /Kernels/EnthalpyTimeDerivative

## Description

Assuming that density, $\rho$, is quasi-constant value over a time step,
this kernel implements the time derivative term

\begin{equation}
  \rho \frac{\partial E}{\partial t}
\end{equation}

in the [enthalpy form](enthalpy_form.md) of the heat equation,
where $E$ is enthalpy change from a reference enthalpy state and $t$ is time.

The Automatic differentiation (AD) version is also available by adding the
prefix `AD` to the name for the "type" parameter.

## Example Input Syntax

!listing test/tests/enthalpy_form/time_derivative/calc.i block=Kernels/time_enth

!syntax parameters /Kernels/EnthalpyTimeDerivative

!syntax inputs /Kernels/EnthalpyTimeDerivative

!syntax children /Kernels/EnthalpyTimeDerivative
