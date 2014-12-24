#
#
#
our $aps =
[
 {
   name => 'Simpleton',
   key  => 'S',
   header => 'Simpleton.h',
   cpp    => ['Simpleton.cpp'],
   constructor => 'ai::Sample::Simpleton()',
 },
 {
   name => 'Aristotle',
   key  => 'A',
   header => 'Aristotle.h',
   cpp    => ['Aristotle.cpp'],
   constructor => 'ai::Sample::Aristotle()',
 },
{
  name => 'Hunter',
  key  => 'h',
  header => 'naaHunter.h',
  cpp => ['naaHunter.cpp', 'naaState.cpp', 'naaProblem.cpp', 'naaAction.cpp', 'naaKnowledge.cpp'],
  constructor => 'naa::Hunter()',
},
 ];

1;
