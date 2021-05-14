# Compare the solution of \rho dE/dt = q_{dot} to an independent calculation.

[Mesh]
  [geo]
    type = GeneratedMeshGenerator
    dim = 1
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
  [time_enth]
    type = EnthalpyTimeDerivative
    variable = enth
  []
  [source_enth]
    type = BodyForce
    variable = enth
    value = 1
  []
  [time_other]
    type = HeatConductionTimeDerivative
    variable = other
  []
  [source_other]
    type = BodyForce
    variable = other
    value = 1
  []
[]

[Materials]
  [mat_props]
    type = GenericConstantMaterial
    prop_names = 'density specific_heat'
    prop_values = '2 1'
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
  type = Transient
  num_steps = 3
  dt = 4
[]

[Outputs]
  csv = true
[]
