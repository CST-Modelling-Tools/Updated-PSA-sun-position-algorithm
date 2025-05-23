#ifndef __SUNPOS_H
#define __SUNPOS_H
#include <numbers>   // C++20 standard constants

// Declaration of physical and mathematical constants
constexpr double pi = std::numbers::pi;
constexpr double twopi = 2.0 * pi;
constexpr double rad = pi / 180.0;
constexpr double dEarthMeanRadius = 6371.01;        // in km
constexpr double dAstronomicalUnit = 149597870.7;   // in km

// Struct for universal time specification
struct cTime {
    int iYear;
    int iMonth;
    int iDay;
    double dHours;
    double dMinutes;
    double dSeconds;
};

// Struct for geographic position
struct cLocation {
    double dLongitude;  // in degrees
    double dLatitude;   // in degrees
};

// Struct to hold output solar coordinates (in radians)
struct cSunCoordinates {
    double dZenithAngle;        // zenith angle (rad)
    double dAzimuth;            // azimuth angle from North to East (rad)
    double dDeclination;        // declination (rad)
    double dBoundedHourAngle;   // hour angle [-π, π] (rad)
};

// Compute sun position for a given time and location
void sunpos(cTime udtTime, cLocation udtLocation, cSunCoordinates* udtSunCoordinates);

#endif // __SUNPOS_H