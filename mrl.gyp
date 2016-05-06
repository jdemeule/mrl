{
  'includes': [
    'common.gypi',
  ],
  'targets': [
    {
      'target_name': 'mrl',
      'type': 'none',
      'xcode_settings': {
        'OTHER_FLAGS': [
        ],
      },
      'defines': [
      ],
      'include_dirs': [
        '.',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          '.',
        ],
      },
      'sources': [
        'mrl/linq.hpp',
        'mrl/range.hpp',
        'mrl/stream.hpp',
        'mrl/details/basic_range.hpp',
        'mrl/details/concat_operator.hpp',
        'mrl/details/concat_range.hpp',
        'mrl/details/chunk_range.hpp',
        'mrl/details/chunk_operator.hpp',
        'mrl/details/filter_operator.hpp',
        'mrl/details/filter_range.hpp',
        'mrl/details/flatten_operator.hpp',
        'mrl/details/flatten_range.hpp',
        'mrl/details/for_each_range.hpp',
        'mrl/details/iterator_range.hpp',
        'mrl/details/join_operator.hpp',
        'mrl/details/join_range.hpp',
        'mrl/details/mbind_operator.hpp',
        'mrl/details/num_range.hpp',
        'mrl/details/owner_range.hpp',
        'mrl/details/pipeable_operator.hpp',
        'mrl/details/ref_range.hpp',
        'mrl/details/repeat_operator.hpp',
        'mrl/details/repeat_range.hpp',
        'mrl/details/skip_operator.hpp',
        'mrl/details/skip_range.hpp',
        'mrl/details/take_n_operator.hpp',
        'mrl/details/take_n_range.hpp',
        'mrl/details/transform_operator.hpp',
        'mrl/details/transform_range.hpp',
        'mrl/details/zip_operator.hpp',
        'mrl/details/zip_range.hpp',
      ],
    },
  ],
}
