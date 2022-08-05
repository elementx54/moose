# EnthalpyFixTemperatureBC

!syntax description /BCs/EnthalpyFixTemperatureBC

## Description

The `EnthalpyFixTemperatureBC` boundary condition creates an enthalpy Dirichlet
boundary condition when the temperature of the boundary is provided.
The temperature of the boundary is converted into a change in enthalpy value
that is required to attain the temperature provided at the boundary.

The calculated enthalpy change at the boundary is determined from the reference enthalpy
associated with the provided reference temperature.
This boundary condition is also valid if the initial enthalpy is set to zero
when setting the initial temperature.

The calculation uses the solid state equation relating enthalpy to temperature:
\begin{equation}
  \int_{T_{ref}}^{T_{bc}} \frac{dE}{d\eta} d\eta = \int_{T_{ref}}^{T_{bc}} \overline{c}_s d\eta
\end{equation}
where $T_{ref}$ is the reference temperature, $T_{bc}$ is the set temperature boundary condition,
$E$ is enthalpy, and $\overline{c}_s$ is the average specific heat.
With the use of average properties calculated using the boundary temperature
and reference temperature of the current reference enthalpy,
as the reference temperature near the boundary approaches the specified boundary temperature,
the approximation of using average properties improves.

If the solidus and liquidus temperatures are the same as the provided temperature boundary condition,
an error will occur as the enthalpy value of the boundary cannot be determined uniquely from the boundary temperature.

The Automatic differentiation (AD) version is also available by adding the
prefix `AD` to the name for the "type" parameter.

## Example Input Syntax

!listing test/tests/enthalpy_form/fix_temperature_bc/fix_T.i block=BCs/temp_bc

!syntax parameters /BCs/EnthalpyFixTemperatureBC

!syntax inputs /BCs/EnthalpyFixTemperatureBC

!syntax children /BCs/EnthalpyFixTemperatureBC
