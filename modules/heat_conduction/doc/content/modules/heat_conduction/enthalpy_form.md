# Enthalpy Form of Heat Conduction

The change-in-enthalpy form or the heat conduction is mainly used for cases where
phase change occurs (melting or solidification) and material does *not* move.
This mainly occurs in applications for internal or zero-gravity phase change.

The heat conduction governing equation is cast in terms of a change in enthalpy,
$\Delta E$, from some previously chosen reference temperature, $T_{ref}$,
at which the reference enthalpy is zero, $E_{ref} = 0$.
Any change in enthalpy from this reference is abbreviated as $E$ due to
$\Delta E = E - E_{ref}$.

As such the governing equation takes the form

\begin{equation}\label{eq:governing_enthalpy}
  \rho\frac{\partial E}{\partial t} =
    \nabla \Gamma \nabla E + \nabla^2 S + \dot{q},
\end{equation}

where $\rho$ is density, $t$ is time, and $\dot{q}$ is an energy source or sink.
The $\Gamma$ and $S$ material property terms are derived from specific heat,
$c$, and thermal conductivity, $k$. Both are affected by $E$.

## Derivation of Enthalpy Materials

Before showing the concept of the derivation of $\Gamma$ and $S$ material properties,
two definitions are needed: the state law of enthalpy change and the Kirchhoff temperature.

The state law of enthalpy is

\begin{equation}\label{eq:state_law}
  \Delta E = \int_{T}^{T_{ref}} \frac{dE}{d\eta} d\eta =
    \int_{T}^{T_{ref}} c(\eta) d\eta.
\end{equation}

The heat of vaporization, $H$, accounts for the enthalpy change while a material
is melting or solidifying and temperature remains somewhat constant.

The Kirchhoff temperature, $U$, is

\begin{equation}\label{eq:kirchhoff_temperature}
  U = \int_{T}^{T_{ref}} k(\eta) d\eta.
\end{equation}

This also means that $\nabla U = k \nabla T$. If the assumed form of $U$ is

\begin{equation}\label{eq:U_form}
  U(E) = \Gamma(E)E + S(E),
\end{equation}

then $\Gamma$ is the terms multiplied by $E$ and $S$ is the terms not multiplied by $E$.
Example derivations assuming constant properties for a material with a
[single melt temperature](single_melt.md)
or a [range of temperatures](range_melt.md)
over which melting occurs illustrate the form of $\Gamma$ and $S$.

## Boundary Conditions

TODO: Follow heat conduction description for BC
