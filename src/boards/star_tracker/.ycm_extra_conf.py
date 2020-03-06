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
            # includes
            '-I.',
            '-I./object_dictionary',
            '-I../common',
            '-I../socketCAN',
            '-I../CANopenNode',
            '-I../CANopenNode/stack',
            ],
        }
