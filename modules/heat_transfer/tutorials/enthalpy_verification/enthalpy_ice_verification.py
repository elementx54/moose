#!/usr/bin/python
# -*- coding: utf-8 -*-
# onetrueplot.py

# Original Author
__author__="Adam Zabriskie <adam.zabriskie@inl.gov>"

__version__="0.0.0"

__doc__="""\
Analytical solution for semi-infinite slab of ice melting.

This follows the information from Gerasimov 2022, Benchmark test for the heat
conduction equation with phase change: two-phase Stefan problem for melting
of an ice slab
"""

import math
from scipy import optimize

# Water Properties
rho_liq = 1000.0 # kg/m3
cp_liq = 4190.0 # J/(kg K)
lam_liq = 0.58 # W/(m K)
alpha_liq = lam_liq / (rho_liq * cp_liq)

# Ice Properties
rho_ice = 920.0 # kg/m3
cp_ice = 2090.0 # J/(kg K)
lam_ice = 2.2 # W/(m K)
alpha_ice = lam_ice / (rho_ice * cp_ice)

fusion_heat = 3.34e5 # J/kg
T_melt = 273.15 # K

# Ice melts from heat added in from the right
bc_left = 308.15 # K
bc_right = 263.15 # K

# Stefan numbers
St_liq = cp_liq * (bc_left - T_melt) / fusion_heat
St_ice = cp_ice * (T_melt - bc_right) / fusion_heat

# Dimensionless Parameters
rho_star = rho_liq / rho_ice
alpha_star = math.sqrt(alpha_liq / alpha_ice)

def trans_equ(LAMBDA):
    ''' Function to find a root. '''
    return St_liq / (LAMBDA * math.exp(LAMBDA**2) * math.erf(LAMBDA)
                     ) - St_ice / (rho_star * alpha_star * LAMBDA *
                                   math.exp((rho_star * alpha_star *
                                            LAMBDA)**2) *
                                   math.erfc(rho_star * alpha_star * LAMBDA)
                                   ) - math.sqrt(math.pi)

sol_Lambda = optimize.root_scalar(trans_equ, bracket=[0.00001,2], method='bisect')
print("Lambda root = \n{}".format(sol_Lambda))

def X_front(time):
    ''' Position of water-ice interface front. '''
    return 2.0 * sol_Lambda.root * math.sqrt(alpha_liq * time)

def Temperature(x_pos, time):
    ''' Temperature solution when given position and time. '''
    front_loc = X_front(time)
    if (x_pos > front_loc):
        # In Ice
        sol_T = bc_right + (T_melt - bc_right) * math.erfc(x_pos / (2.0 *
            math.sqrt(alpha_ice * time)) - (1.0 - rho_star) * alpha_star *
            sol_Lambda.root) / math.erfc(rho_star * alpha_star * sol_Lambda.root)
    else:
        # In Liquid Water
        sol_T = bc_left - (bc_left - T_melt) * math.erf(x_pos / (3.0 * math.sqrt(
            alpha_liq * time))) / math.erf(sol_Lambda.root)
    return sol_T

# Simulation parameters
#name_0 = "solAT1day.csv"
#t_0 = 72.0 * 60.0 * 60.0 # sec
name_0 = "single_slab_IC.csv"
t_0 = 3600.0 # sec
delta_t = 36.0 # sec
delta_x = 0.005 # m
x_max = 4.0 # m

# Output initial condition csv
init_front = X_front(t_0)
print("Front location = {} m".format(init_front))
with open(name_0, 'w') as file_ic:
    x = 0.0 # m
    while (x <= x_max):
        # Convert from temperature to enthalpy
        T_x = Temperature(x, t_0)
        if (x > init_front):
            # Ice
            E_x = (T_x - T_melt) * cp_ice
        else:
            # Water
            E_x = (T_x - T_melt) * cp_liq + fusion_heat

        file_ic.write("{0}, {1}\n".format(x, E_x))
        x += delta_x

print("Left Enthalpy BC: {}".format((bc_left - T_melt) * cp_liq + fusion_heat))
print("Right Enthalpy BC: {}".format((bc_right - T_melt) * cp_ice))

