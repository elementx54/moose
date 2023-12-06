# Verification with analystical solution 1D ice melting without flow.
# Follows information from Gerasimov 2022, Benchmark test for the heat
# conduction equation with phase change: two-phase Stefan problem for melting
# of an ice slab
[GlobalParams]
  order = SECOND
  family = LAGRANGE
[]
[Problem]
  type = ReferenceResidualProblem
  extra_tag_vectors = 'ref'
  reference_vector = 'ref'
[]

[Mesh]
  [slab]
    type = GeneratedMeshGenerator
    dim = 1
    xmax = 4.0 # m
    #nx = 80 # 0.05 m size
    nx = 800 # size should be 0.005 m
    #nx = 799 # size should be 0.005 m
    #nx = 1600 # size should be 0.0025 m
    elem_type = EDGE3
  []
[]

[Variables]
  [Enthalpy]
    #initial_condition = -20900.0
  []
[]

[ICs]
  [enth_init_func]
    type = FunctionIC
    variable = Enthalpy
    function = ic_function
  []
[]

[AuxVariables]
  [ref_T]
    #order = CONSTANT
    #family = MONOMIAL
    initial_condition = 273.15 # K
  []
  [one_day_enth]
    #order = FIRST
    #family = LAGRANGE
    [InitialCondition]
      type = FunctionIC
      function = solution_function
    []
  []
  [S_val]
    order = SECOND
    family = LAGRANGE
    initial_condition = 0.0
  []
[]

[AuxKernels]
  [calc_S]
    type = ParsedAux
    variable = S_val
    coupled_variables = Enthalpy
    expression = 'if(Enthalpy>=3.34e5, -3.34e5 * 0.58 / 4190.0, 0.0)'
    execute_on = 'initial timestep_begin linear nonlinear timestep_end'
  []
[]

[Functions]
  [ic_function]
    type = PiecewiseLinear
    data_file = 'single_slab_IC.csv'
    format = columns
    axis = x
  []
  [solution_function]
    type = PiecewiseLinear
    data_file = 'solAT1day.csv'
    format = columns
    axis = x
  []
[]

[Kernels]
  [time_enth]
    type = EnthalpyTimeDerivative
    variable = Enthalpy
    extra_vector_tags = 'ref'
  []
  [cond_enth]
    type = EnthalpyConduction
    variable = Enthalpy
    extra_vector_tags = 'ref'
  []
  [phase_enth]
    type = EnthalpyPhaseChange
    variable = Enthalpy
    S_enthalpy = S_val
    extra_vector_tags = 'ref'
  []
[]

[BCs]
  #[left_T]
  #  type = EnthalpyFixTemperatureBC
  #  boundary = 'left'
  #  variable = Enthalpy
  #  bc_temperature_function = 308.15 # K
  #  quality = 1 # Liquid
  #  heat_fusion = 3.34e5 # J/kg
  #  reference_T = ref_T
  #[]
  [left_T]
    type = DirichletBC
    boundary = 'left'
    variable = Enthalpy
    value = 480650.0
  []
  [right_T]
    type = DirichletBC
    boundary = 'right'
    variable = Enthalpy
    value = -20900.0
  []
  #[right_T]
  #  type = EnthalpyFixTemperatureBC
  #  boundary = 'right'
  #  variable = Enthalpy
  #  bc_temperature_function = 263.15 # K
  #  quality = 0 # Solid
  #  heat_fusion = 3.34e5 # J/kg
  #  reference_T = ref_T
  #[]
[]

[Materials]
  [solidus_liquidus]
    type = GenericConstantMaterial
    prop_names = 'solidus liquidus'
    prop_values = '273.15 273.15'
  []
  [single_melt_rho]
    type = ParsedMaterial
    property_name = 'density'
    coupled_variables = 'Enthalpy'
    outputs = all
    expression = 'if(Enthalpy<=0, 1000.0, if(Enthalpy>=3.34e5, 920.0, 960.0))'
    #expression = 'if(Enthalpy<=0, 1000.0, if(Enthalpy>=3.34e5, 920.0, 1000.0))'
    # During melt, the density is assumed to be the average
  []
  [single_melt_cp]
    type = ParsedMaterial
    property_name = 'specific_heat'
    coupled_variables = 'Enthalpy'
    outputs = all
    expression = 'if(Enthalpy<=0, 2090.0, if(Enthalpy>=3.34e5, 4190.0, 3140.0))'
    # During melt, the specific heat is assumed to be the average
  []
  [single_melt_k]
    type = ParsedMaterial
    property_name = 'thermal_conductivity'
    coupled_variables = 'Enthalpy'
    outputs = all
    expression = 'if(Enthalpy<=0, 2.2, if(Enthalpy>=3.34e5, 0.58, 1.39))'
    # During melt, the thermal conductivity is assumed to be the average
  []
  [single_melt_Gamma]
    type = ParsedMaterial
    property_name = 'gamma'
    coupled_variables = 'Enthalpy'
    material_property_names = 'thermal_conductivity specific_heat'
    expression = 'if(Enthalpy<=2, thermal_conductivity / specific_heat, if(
                  Enthalpy>=3.34e5, thermal_conductivity / specific_heat, 0.0))'
    outputs = all
    #expression = 'thermal_conductivity / specific_heat'
  []
  [set_T]
    type = ParsedMaterial
    property_name = 'Temperature'
    coupled_variables = 'Enthalpy'
    material_property_names = 'specific_heat'
    outputs = all
    expression = 'if(Enthalpy<=0, Enthalpy / specific_heat + 273.15, if(
                  Enthalpy>=3.34e5, (Enthalpy - 3.34e5) / specific_heat +
                  273.15, 273.15))'
  []
  [set_solution_T]
    type = ParsedMaterial
    property_name = 'solution_T'
    coupled_variables = 'one_day_enth'
    outputs = all
    expression = 'if(one_day_enth<=0, one_day_enth / 2090.0 + 273.15, if(
                  one_day_enth>=3.34e5, (one_day_enth - 3.34e5) / 4190.0 +
                  273.15, 273.15))'
  []
[]

[Executioner]
  type = Transient
  dt = 36.0 # sec
  dtmin = 1.0 # sec
  start_time = 3600.0 # sec, 1 hour
  #end_time = 3600.0 # sec, 1 hour
  end_time = 86400.0 # sec, 24 hours
  #end_time = 864000.0 # sec, 240 hours
[]

[Outputs]
  [out_exodus]
    type = Exodus
    elemental_as_nodal = true
  []
[]

