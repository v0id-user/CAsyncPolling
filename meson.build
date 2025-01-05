project('polling_app', 'c')


# Add compiler flags
if host_machine.system() == 'darwin'
    add_project_arguments('-Wno-deprecated-declarations', language: 'c')
    add_project_arguments('-Wno-incompatible-pointer-types', language: 'c')  # Suppress the warning
elif host_machine.system() == 'windows'
    add_project_arguments('-Wno-incompatible-pointer-types', language: 'c')
    add_project_arguments('-Wno-incompatible-pointer-types-discards-qualifiers', language: 'c')
endif

# Add _DEBUG definition when building in debug mode
if get_option('buildtype').startswith('debug')
    add_project_arguments('-D_DEBUG', language: 'c')
endif

include_dirs = include_directories('include')
subdir('src')
subdir('tests')