lib_src = [
    'async.c',
    'asyncio.c',
    'poll.c',
    'scheduler.c',
]

async_lib = static_library('async',
    lib_src,
    include_directories: include_dirs,
    name_prefix: '',  # Avoid 'lib' prefix on Windows
    install: false)

executable(
    'polling_app', 
    ['main.c'],
    include_directories: include_dirs,
    link_with: async_lib,
    win_subsystem: 'console')