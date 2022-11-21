# Combinatorial Testing
(Note - for running the code, see the .mp4 video included in the "resources" folder)

The purpose of this project is to simulate the existence of a singular "problem causer" within a set of variables in a System. Any subset of variables being set to "on" or "off", so to speak, could be responsible for the problem. The purpose of this C++ project is to simulate a strategic guessing game for pinpointing what subset of variables with given states is causing a (simulated) "problem".<br>
In addition, given a set of configurations, with all variables set to different values in each configuration, instances of the defined "CoverageCalculator" class can calculate the combinatorial coverage of said configurations for a given error set size. For instance, a set of configurations could test out (A=1, B=1) as an error source when testing for an error set of size 2, but what about (C=1, D=0), or any other of the possible pairs of variables set at values? A CoverageCalculator instance can count all of the different sets of size 2 covered by a clutch of configurations, and compare that to the total number of possible configurations of size 2, given our variables.<br>
Another feature of this application is, given a certain number of covering arrays to work with, is it possible to achieve total t-way coverage? That is, when a CoveringArraySizeValidator object, with n variables as its argument constructor, has its 'covers' method called with a given number of vectors and fault size, are all possible minimal error sets of size 'fault size' covered by any possible collection of six configurations?<br>
<br>
Covering for 11 parameters using 7 arrays:<br>
0 0 0 1 0 0 0 1 0 1 0 <br>
0 1 0 0 1 1 0 0 1 0 0 <br>
1 0 1 0 0 0 1 0 1 0 0 <br>
1 1 1 0 0 1 1 1 0 0 1 <br>
1 1 0 1 1 0 1 0 0 1 1 <br>
1 0 1 1 1 1 0 0 1 0 1 <br>
0 1 1 0 1 1 1 1 1 1 1 <br>
<br>
Covering for 12 parameters using 7 arrays:<br>
0 0 0 0 0 0 0 0 1 0 1 0 <br>
0 1 0 0 1 0 1 0 0 1 0 1 <br>
1 0 0 1 0 1 0 1 1 1 0 1 <br>
1 1 1 1 1 1 0 0 0 0 0 0 <br>
1 0 1 1 1 0 1 1 0 0 1 1 <br>
1 1 1 0 1 1 1 1 1 0 0 0 <br>
0 1 1 1 0 1 1 1 0 1 1 0 <br>
<br>
Covering for 13 parameters using 7 arrays:<br>
0 0 1 1 0 1 1 0 0 0 1 1 1 <br>
0 1 0 0 0 0 0 0 0 1 1 1 0 <br>
1 0 0 1 1 0 1 1 1 1 0 0 1 <br>
1 1 0 0 1 1 0 0 1 0 1 1 1 <br>
0 1 1 1 1 1 0 1 0 1 1 0 0 <br>
1 1 1 0 0 0 1 0 0 0 0 0 0 <br>
0 0 1 0 0 1 0 1 1 0 0 1 0 <br>
<br>
Covering for 14 parameters using 7 arrays:<br>
0 0 1 1 1 0 1 1 0 1 1 1 1 0 <br>
0 1 0 0 1 0 1 0 1 1 0 0 0 1 <br>
1 0 0 1 0 1 1 0 0 0 1 0 0 1 <br>
1 1 1 0 1 1 0 1 1 0 1 0 1 1 <br>
0 0 0 0 0 1 0 0 1 0 0 0 1 0 <br>
1 1 0 1 0 0 0 1 1 0 0 1 0 0 <br>
1 1 1 0 0 1 0 0 0 1 0 1 0 1 <br>
<br>
Covering for 15 parameters using 7 arrays:<br>
<br>
0 0 0 1 1 1 1 1 1 1 1 0 1 1 1 <br>
0 1 1 0 0 1 0 0 0 1 0 0 1 1 1 <br>
1 0 0 0 0 0 1 0 0 0 1 0 1 1 0 <br>
1 1 0 1 0 1 0 1 0 0 1 1 1 0 1 <br>
0 0 1 0 0 0 0 1 1 0 1 1 0 1 1 <br>
0 0 0 0 1 1 0 1 0 0 0 0 0 0 0 <br>
1 1 1 1 1 0 1 0 1 1 0 1 0 0 0 <br>
<br>