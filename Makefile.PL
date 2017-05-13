use 5.008001; use strict; use warnings; use utf8;

use lib 'inc';
use ExtUtils::MakeMaker;
use Inline::Module;

WriteMakefile(
  NAME => 'YAML::LibYAML::Emitter',
  VERSION => '0.0.2',
  ABSTRACT => 'LibYAML Emitter',
  AUTHOR => 'Ingy döt Net <ingy@cpan.org>',
  LICENSE => 'perl',
  MIN_PERL_VERSION => '5.010001',
  test => { TESTS => 't/*.t' },
  postamble => {
    inline => {
      module => 'YAML::LibYAML::Emitter',
      makestub => 1,
    },
  },
  INC => '-Ilibyaml/include',
  META_MERGE => {
    'meta-spec' => { version => 2 },
    prereqs => {
        develop => {
          requires => {
            'Inline::C' => '0.68',
            'Inline::Module' => '0.31',
        },
      },
    },
    no_index => {
      directory => [
        'inc',
      ],
    },
  },
);
