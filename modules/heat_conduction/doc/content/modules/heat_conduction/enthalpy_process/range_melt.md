# Range Melting Temperature Derivation

An illustration of the process of determining the $\Gamma$ and $S$ terms in
the [enthalpy form](enthalpy_form.md) of the heat conduction equation.
This process is illustrated for a material with constant properties that melts
over a range of temperatures.
The material starts melting at $T_1$ and finishes melting at $T_2$.
The material is termed "mushy" during this temperature range of
$\Delta T_m = T_2 - T_1$.

## Determining $\Gamma$ and $S$

Recall the state law equation is used to relate enthlapy change to temperature.
First, set the reference temperature, $T_{ref}$ to the lower melt temperature, $T_1$, so

\begin{equation}
  E_{ref} = 0 \text{ when } T_{ref} = T_{1},
\end{equation}

which makes the change in enthalpy, $\Delta E$, to be $E - E_{ref} = E$.
The solid region is when $E \leq 0$,
the mushy region is when $0 < E < H + c_m \Delta T_m$,
and the liquid region is when $E \geq H + c_m \Delta T_m$.

### Solid Region

For the solid region, the state law is

\begin{equation}
  \int_{T_1}^{T} \frac{dE}{d\eta} d\eta = \int_{T_1}^{T} c_s(\eta) d\eta,
\end{equation}

where $c_s$ is the specific heat of the solid. Taking the integral and assuming
a negative $E$ becomes

\begin{equation}\label{eq:solid_func_T}
  \Delta E = E = c_s T - c_s T_1,
\end{equation}

which can be formed as a temperature change function of enthalpy change as

\begin{equation}\label{eq:solid_func_E}
  T - T_1 = \frac{E}{c_s},
\end{equation}

where $T$ is the temperature corresponding to the current $E$.

Now apply the Kirchhoff temperature definition as

\begin{equation}
  U = \int_{T_{1}}^T k_s(\eta) d\eta = k_s (T - T_1),
\end{equation}

where $k_s$ is the thermal conductivity of the solid.
To get $U$ in terms of $E$, substitute [eq:solid_func_E] to get

\begin{equation}\label{eq:solid_U}
  U = \frac{k_s E}{c_s}.
\end{equation}

### Mushy Region

For the mushy region, the state law is

\begin{equation}
  \int_{T_1}^{T} \frac{dE}{d\eta} d\eta = \int_{T_1}^{T} c_m(\eta) d\eta,
\end{equation}

where $c_m$ is the specific heat of the mushy material. Taking the integral becomes

\begin{equation}\label{eq:mushy_func_T}
  \Delta E = E = c_m T + \frac{T - T_1}{\Delta T_m} H - c_m T_1,
\end{equation}

which can be formed as a temperature change function of enthalpy change as

\begin{equation}\label{eq:mushy_func_E}
  T - T_1 = \frac{\Delta T_m E}{c_m \Delta T_m + H},
\end{equation}

where $T$ is the temperature corresponding to the current $E$.

Now apply the Kirchhoff temperature definition as

\begin{equation}
  U = \int_{T_{1}}^T k_m(\eta) d\eta = k_m (T - T_1),
\end{equation}

where $k_m$ is the thermal conductivity of the mushy material.
To get $U$ in terms of $E$, substitute [eq:mushy_func_E] to get

\begin{equation}\label{eq:mushy_U}
  U = \frac{k_m \Delta T_m E}{H + c_m \Delta T_m}.
\end{equation}

### Liquid Region

For the liquid region, the state law is

\begin{equation}
  \int_{T_1}^T \frac{dE}{d\eta} d\eta = \int_{T_2}^T c_l(\eta) d\eta
    + \int_{T_1}^{T_2} c_m(\eta) d\eta,
\end{equation}

where $c_l$ is the specific heat of the liquid. Taking the integrals becomes

\begin{equation}\label{eq:liquid_func_T}
  \Delta E = E = (T - T_1) c_l + H + (c_m - c_l) \Delta T_m
\end{equation}

which can be formed as a temperature change function of enthalpy change as

\begin{equation}\label{eq:liquid_func_E}
  T - T_1 = \frac{E}{c_l} - \frac{H + (c_m - c_l) \Delta T_m}{c_l}
\end{equation}

Now apply the Kirchhoff temperature definition as

\begin{equation}
  U = \int_{T_{1}}^T k_l(\eta) d\eta = \int_{T_2}^T k_l(\eta) d\eta
    + \int_{T_1}^{T_2} k_m(\eta) d\eta =
    k_l (T - T_1) + (k_m - k_l) \Delta T_m,
\end{equation}

where $k_l$ is the thermal conductivity of the liquid.
To get $U$ in terms of $E$, substitute [eq:liquid_func_E] to get

\begin{equation}\label{eq:liquid_U}
  U = \frac{k_l E}{c_l} + \frac{\Delta T_m}{c_l}(k_m c_l - k_l c_m) -
    \frac{k_l}{c_l} H.
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
    \frac{k_m \Delta T_m}{H + c_m \Delta T_m} & \text{for } 0 < E < H + c_m \Delta T_m, \\
    \frac{k_l}{c_l} & \text{for } E \geq H + c_m \Delta T_m.
  \end{cases}
\end{equation}

\begin{equation}
  S =
  \begin{cases}
    0 & \text{for } E \leq 0, \\
    0 & \text{for } 0 < E < H + c_m \Delta T_m, \\
    \frac{\Delta T_m}{c_l}(k_m c_l - k_l c_m) - \frac{k_l}{c_l} H &
    \text{for } E \geq H + c_m \Delta T_m.
  \end{cases}
\end{equation}
