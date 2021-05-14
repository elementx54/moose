# Single Melting Temperature Derivation

An illustration of the process of determining the $\Gamma$ and $S$ terms in
the [enthalpy form](enthalpy_form.md) of the heat conduction equation.
This process is illustrated for a material with constant properties that melts
at a single temperature.

## Determining $\Gamma$ and $S$

Recall the state law equation is used to relate enthlapy change to temperature.
First, set the reference temperature, $T_{ref}$ to the melt temperature, $T_m$, so

\begin{equation}
  E_{ref} = 0 \text{ when } T_{ref} = T_{m},
\end{equation}

which makes the change in enthalpy, $\Delta E$, to be $E - E_{ref} = E$.
The solid region is when $E \leq 0$ and the liquid region is when $E \geq H$,
where $H$ is the latent heat of fusion.
When $0 < E < H$, the material is changing phases.

### Solid Region

For the solid region, the state law is

\begin{equation}
  \int_T^{T_m} \frac{dE}{d\eta} d\eta = \int_T^{T_m} c_s(\eta) d\eta,
\end{equation}

where $c_s$ is the specific heat of the solid. Taking the integral becomes

\begin{equation}\label{eq:solid_func_T}
  \Delta E = E = c_s T_m - c_s T,
\end{equation}

which can be formed as a function of enthalpy change as

\begin{equation}\label{eq:solid_func_E}
  T = \frac{E}{c_s} + T_m,
\end{equation}

where $T$ is the temperature corresponding to the current $E$.

Now apply the Kirchhoff temperature definition as

\begin{equation}
  U = \int_{T_{ref}}^T k_s(\eta) d\eta = k_s (T - T_m),
\end{equation}

where $k_s$ is the thermal conductivity of the solid.
To get $U$ in terms of $E$, substitute [eq:solid_func_E] to get

\begin{equation}\label{eq:solid_U}
  U = \frac{k_s E}{c_s}.
\end{equation}

### During Phase Change

The enthalpy change of a material just reaching $T_m$ until all the material is
liquid but still at $T_m$ is the latent heat of fusion, $H$.

For a material with a single melting temperature, $U = 0$ as $T = T_m$.

### Liquid Region

For the liquid region, the state law is

\begin{equation}
  \int_{T_m}^T \frac{dE}{d\eta} d\eta = \int_{T_m}^T c_l(\eta) d\eta,
\end{equation}

where $c_l$ is the specific heat of the liquid. Taking the integral while taking
into account the change of the material from solid to liquid becomes

\begin{equation}\label{eq:liquid_func_T}
  \Delta E = E = c_l T + H - c_l T_m,
\end{equation}

which can be formed as a function of enthalpy change as

\begin{equation}\label{eq:liquid_func_E}
  T = \frac{E-H}{c_l} + T_m.
\end{equation}

Now apply the Kirchhoff temperature definition as

\begin{equation}
  U = \int_{T_{ref}}^T k_l(\eta) d\eta = k_l (T - T_m),
\end{equation}

where $k_l$ is the thermal conductivity of the liquid.
To get $U$ in terms of $E$, substitute [eq:liquid_func_E] to get

\begin{equation}\label{eq:liquid_U}
  U = \frac{k_l (E - H)}{c_l}.
\end{equation}

## Final Form

Assuming $U$ has the form of

\begin{equation}
  U(E) = \Gamma(E) E + S(E),
\end{equation}

then grouping each regions' $U$, [eq:solid_U] and [eq:liquid_U] into this form
will provide the definitions for $\Gamma$ and $S$:

\begin{equation}
  \Gamma =
  \begin{cases}
    \frac{k_s}{c_s} & \text{for } E \leq 0, \\
    0 & \text{for } 0 < E < H, \\
    \frac{k_l}{c_l} & \text{for } E \geq H.
  \end{cases}
\end{equation}

\begin{equation}
  S =
  \begin{cases}
    0 & \text{for } E \leq 0, \\
    0 & \text{for } 0 < E < H, \\
    \frac{-H k_l}{c_l} & \text{for } E \geq H.
  \end{cases}
\end{equation}
