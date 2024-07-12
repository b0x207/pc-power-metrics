project('pc-power-metrics', 'c', version: '0.0.1')

include_dirs = include_directories('include')

sources = files(
  'src/main.c',
  'src/checks.c',
  'src/zones.c',
  'src/reading.c',
)

executable(
  'pc-power-metrics',
  sources,
  include_directories: include_dirs
)
