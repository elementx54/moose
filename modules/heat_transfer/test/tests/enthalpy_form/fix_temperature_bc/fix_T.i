# Compare the fixed temperature boundary condition solution to an independent calculation.

[Mesh]
  [geo]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 5
  []
[]

[Variables]
  [enth]
    initial_condition = 0
  []
[]

[AuxVariables]
  [ref_T]
    initial_condition = 300 # Assume reference enthalpy is zero at 300 K
  []
  [qual]
    initial_condition = 0
  []
[]

[Kernels]
  [cond_enth]
    type = EnthalpyConduction
    variable = enth
  []
[]

[BCs]
  [temp_bc]
    type = EnthalpyFixTemperatureBC
    boundary = 'right'
    variable = enth
    bc_temperature_function = 375
    reference_T = ref_T
    quality = qual
    heat_fusion = 2500
  []
  [enth_bc]
    type = DirichletBC
    boundary = 'left'
    variable = enth
    value = 17500
  []
[]

[Materials]
  [mat_props]
    type = GenericConstantMaterial
    prop_names = 'gamma thermal_conductivity specific_heat liquidus solidus'
    prop_values = '0.1 20 200 350 325'
  []
[]

[Postprocessors]
  [avg_enth]
    type = ElementAverageValue
    variable = enth
  []
[]

[Executioner]
  type = Steady
[]

[Outputs]
  csv = true
[]
