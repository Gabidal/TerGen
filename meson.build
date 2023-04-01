project(
  'TerGen', 'cpp',
  version : '0.1.5',
  default_options : ['warning_level=3', 'cpp_std=c++17', 'debug=true', 'buildtype=debug']
)

sources = [
  'Dependencies/Simplex/Simplex.cpp',

  'src/Args.cpp',
  'src/Utils.cpp',
  'src/Core.cpp',

  'main.cpp',
]

static_library(
  'TerGen',
  sources
)