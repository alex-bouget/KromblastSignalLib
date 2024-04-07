project(
    'SignalLib',
    'cpp',
    version : '0.1',
    default_options : ['warning_level=3', 'cpp_std=c++20']
)

cc = meson.get_compiler('cpp')

# if get_option('buildtype').startswith('debug')
#   add_project_arguments('-DDEBUG', language : 'cpp')
# endif

kromblast_api_dep = subproject('kromblast').get_variable('kromblast_api_dep')

signal_lib_dep = declare_dependency(
    include_directories : include_directories('src'),
)

signal_lib = shared_library(
    'signal_lib',
    'src/main.cpp',
    'src/signallib.cpp',
    dependencies: [
        kromblast_api_dep,
        signal_lib_dep
    ]
)