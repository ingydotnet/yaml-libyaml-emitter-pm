use strict; use warnings;
package YAML::LibYAML::Emitter;
# our $VERSION = 'x.x.x';

use Cwd;

use YAML::LibYAML::Emitter::Inline C
    => 'lib/YAML/LibYAML/Emitter.c'
    => inc => "-I${\ cwd()}/libyaml/include"
    => myextlib => "${\ cwd()}/libyaml/src/.libs/libyaml.so";

1;

