test_sources = [
    'test_poll.c',
]

foreach test_name : test_sources
    test_exe = executable(
        test_name.split('.')[0],
        test_name,
        include_directories: [include_dirs],
        dependencies: [],
        link_with: [polling_lib]
    )
    test(test_name.split('.')[0], test_exe)
endforeach 