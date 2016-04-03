{
  'includes': [
    'common.gypi',
  ],
  'targets': [
    {
      'target_name': 'gtest',
      'type': 'static_library',
      'sources': [
        '../gtest-1.7.0/src/gtest-all.cc',
        '../gtest-1.7.0/src/gtest_main.cc',
      ],
      'include_dirs': [
        '../gtest-1.7.0/include',
	'../gtest-1.7.0',
      ],
      'direct_dependent_settings': {
        'defines': [
          'UNIT_TEST',
        ],
        'include_dirs': [
          '../gtest-1.7.0/include',
        ],
      },      
    },
  ],
}
