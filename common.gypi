{
  'target_defaults': {
    'defines': [
      'UNIX',
      'NDEBUG',
    ],
  },
  'conditions': [
    [ 'OS=="mac"', {
      'target_defaults': {
        'defines': [
          'UNIX',
          'NDEBUG',
        ],
        'xcode_settings': {
          'ALWAYS_SEARCH_USER_PATHS': 'NO',
          'CLANG_CXX_LIBRARY': 'libc++',
          'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
          'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
          'GCC_OPTIMIZATION_LEVEL': '0',
          'OTHER_CPLUSPLUSFLAGS': [
            '-std=c++14',
            '-stdlib=libc++',
            '-fexceptions',
            '-Wall',
          ],
          'MACOSX_DEPLOYMENT_TARGET': '10.11'
        },
      },
    }],
  ],
}
