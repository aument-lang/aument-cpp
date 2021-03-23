project('aument-cpp', 'cpp')

aument = find_program('aument')

arg = run_command(aument, [ '--cflags' ]).stdout()
if arg != ''
    add_project_arguments(arg, language: ['cpp'])
endif

arg = run_command(aument, [ '--libs' ]).stdout()
if arg != ''
    add_global_link_arguments(arg, language: ['cpp'])
endif

src = [
    'tests/module.cpp',
]
shared_module('aument_hpp', src,
    include_directories: include_directories('src'))