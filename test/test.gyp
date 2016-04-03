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
        'scratch.cpp',
      ],
    },
  ],
}
