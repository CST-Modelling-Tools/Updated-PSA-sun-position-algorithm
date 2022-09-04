# Updated-PSA-sun-position-algorithm

Repository to provide versions of the PSA+ sun position algorithm, which is the updated version of the PSA sun position algorithm, in diffirent computer languages. This algorithm reaches an excellent compromise between the accuracy and precision with which it estimates the ture solar vector and its computation footprint.

The formal range of validity of this algorithm is 1 January 2020 to 31 December 2050. Within this range:
- the average errors of the algorithm in computing the azimuth and zenith angle of the sun are 1.93 and -1.0 seconds of arc, respectively;
- the standard deviations of those errors are 14.47 and 9.04 seconds of arc and,
- the mean deviations of those errors are 10.61 and 7.28 seconds of arc;
- all vector estimates are enclosed in a circle around the actual true position of the sun -as determined by the Multiyear Interactive Computer Almanac (MICA)- of less than 30 second of arcs.

Currently, this repository provides an implementation of the updated PSA algorithm in C++. This implementation can be found in the "src" subfolder of the folders titled "c++". These subfolder, provide also a basic example of how to run the algorithm and test if it is working properly and it is providing the expected accurate sun position estimates.

More information about the updated PSA sun position algorithm can be found in the wiki associated to this repository.
