test_sources = [
    'test_poll.c',
    'test_async.c',
    'test_ucontext.c',
    'test_async_lib.c',
]

foreach test_name : test_sources
    test_exe = executable(
        test_name.split('.')[0],
        test_name,
        include_directories: include_dirs,
        link_with: async_lib,
        win_subsystem: 'console'
    )
    test(test_name.split('.')[0], test_exe)
endforeach 