#
#
#
our $aps =
[
 {
   name => 'Snorlax',
   key  => 's',
   header => 'Snorlax.h',
   cpp    => ['Snorlax.cpp'],
   constructor => 'ai::Sample::Snorlax(opts)',
 },
 {
   name => 'Manual',
   key  => 'm',
   header => 'Manual.h',
   cpp    => ['Manual.cpp'],
   constructor => 'ai::Sample::Manual()',
 },
 {
   name => 'WyWy',
   key  => 'w',
   header => 'naaWyWy.h',
   cpp    => ['naaWyWy.cpp', 'naaModel.cpp', 'naaState.cpp'],
   constructor => 'naa::WyWy(opts)',
 },
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
 ];

1;
