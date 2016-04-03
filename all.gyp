{
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'xcode_create_dependents_test_runner': 1,
      'dependencies': [
        'mrl.gyp:*',
        'test/test.gyp:*',
      ],
    },
  ],
}
