def Settings( **kwargs ):
    return {
        'flags' : [
            '-x',
            'c',
            '-Wall',
            '-Wextra',
            '-Werror',
            # libs
            '-lsystemd',
            '-pthread',
            '-lpcre2-8 ',
            # includes
            '-I./src/boards/template',
            '-I./src/boards/template/object_dictionary',
            '-I./src/common',
            '-I./src/system_apps',
            '-I./src/socketCAN',
            '-I./src/CANopenNode',
            '-I./src/CANopenNode/301',
            '-I./src/CANopenNode/305',
            '-I./src/CANopenNode/309',
            ],
        }
