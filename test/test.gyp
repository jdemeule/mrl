{
  'includes': [
    '../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'test',
      'type': 'executable',
      'xcode_settings': {
        'OTHER_FLAGS': [
        ],
      },
      'dependencies': [
        '../mrl.gyp:mrl',
        '../gtest.gyp:gtest',
      ],
      'defines': [
      ],
      'include_dirs': [
      ],
      'sources': [
        'build_range_test.cpp',
        'scratch.cpp',
      ],
    },
  ],
}
