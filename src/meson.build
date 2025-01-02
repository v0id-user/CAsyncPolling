lib_src = [
    'async.c',
    'asyncio.c',
    'poll.c',
    'scheduler.c',
]

async_lib = library('async',
    lib_src,
    include_directories: include_dirs)


executable(
    'polling_app', 
    ['main.c'],
    include_directories: include_dirs,
    link_with: async_lib,
    win_subsystem: 'console')