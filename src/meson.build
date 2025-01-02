lib_src = [
    'async.c',
    'asyncio.c',
    'poll.c',
    'scheduler.c',
]

polling_lib = library('polling',
    lib_src,
    include_directories: include_dirs)

executable(
    'polling_app', 
    ['main.c'],
    include_directories: include_dirs,
    link_with: polling_lib,
    win_subsystem: 'console')