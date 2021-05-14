# Compare the solution of \nabla \Gamma \nabla E to an independent calculation.

[Mesh]
  [geo]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 5
  []
[]

[Variables]
  [enth]
    initial_condition = 10
  []
  [other]
    initial_condition = 10
  []
[]

[Kernels]
  [cond_enth]
    type = EnthalpyConduction
    variable = enth
  []
  [cond_other]
    type = HeatConduction
    variable = other
  []
[]

[BCs]
  [enth_left]
    type = DirichletBC
    boundary = left
    variable = enth
    value = 10
  []
  [enth_right]
    type = DirichletBC
    boundary = right
    variable = enth
    value = 54
  []
  [other_left]
    type = DirichletBC
    boundary = left
    variable = other
    value = 10
  []
  [other_right]
    type = DirichletBC
    boundary = right
    variable = other
    value = 54
  []
[]

[Materials]
  [mat_props]
    type = GenericConstantMaterial
    prop_names = 'gamma thermal_conductivity'
    prop_values = '5 5'
  []
  [difference]
    type = ParsedMaterial
    args = 'enth other'
    f_name = 'diff'
    function = 'abs(enth - other)'
    outputs = all
  []
[]

[Postprocessors]
  [avg_enth]
    type = ElementAverageValue
    variable = enth
  []
  [avg_other]
    type = ElementAverageValue
    variable = other
  []
  [avg_diff]
    type = ElementAverageMaterialProperty
    mat_prop = 'diff'
  []
[]

[Executioner]
  type = Steady
[]

[Outputs]
  csv = true
[]
