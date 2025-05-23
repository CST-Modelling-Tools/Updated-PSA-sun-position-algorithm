#include "sunpos.h"
#include <cmath>

void sunpos(cTime udtTime,cLocation udtLocation, cSunCoordinates *udtSunCoordinates)
{
    // Calculate the difference in days between the current Julian Day
    // and JD 2451545.0, which is noon 1 January 2000 Universal Time

    double dElapsedJulianDays;
    double dDecimalHours;

    {
        double dJulianDate;
        long int liAux1;
        long int liAux2;

        // Calculate time of the day in UT decimal hours
        dDecimalHours = udtTime.dHours + (udtTime.dMinutes + udtTime.dSeconds / 60.0 ) / 60.0;

        // Calculate current Julian Day
        liAux1 = (udtTime.iMonth-14)/12;
        liAux2 = (1461*(udtTime.iYear + 4800 + liAux1))/4 
               + (367*(udtTime.iMonth - 2-12*liAux1))/12
               - (3*((udtTime.iYear + 4900 + liAux1)/100))/4
               + udtTime.iDay - 32075;

        dJulianDate = static_cast<double>(liAux2)-0.5+dDecimalHours/24.0;

        // Calculate difference between current Julian Day and JD 2451545.0
        dElapsedJulianDays = dJulianDate-2451545.0;
    }

    // Compute ecliptic coordinates (longitude and obliquity) in radians
    // without limiting the angle to be less than 2*Pi

    double dEclipticLongitude;
    double dEclipticObliquity;

    {
        double dMeanLongitude;
        double dMeanAnomaly;
        double dOmega;

        dOmega = 2.267127827 - 0.00093003392670 * dElapsedJulianDays;
        dMeanLongitude = 4.895036035 + 0.01720279602 * dElapsedJulianDays;
        dMeanAnomaly = 6.239468336 + 0.01720200135 * dElapsedJulianDays;

        dEclipticLongitude = dMeanLongitude 
            + 0.03338320972 * std::sin( dMeanAnomaly )
            + 0.0003497596876 * std::sin( 2*dMeanAnomaly ) 
            - 0.0001544353226
            - 0.00000868972936 * std::sin(dOmega);

        dEclipticObliquity = 0.4090904909 
            - 6.213605399e-9 * dElapsedJulianDays
            + 0.00004418094944 * std::cos(dOmega);
    }

    // Compute celestial coordinates ( right ascension and declination ) in radians
    // without limiting the angle to be less than 2*Pi

    double dDeclination;
    double dRightAscension;

    {
        double dSin_EclipticLongitude = std::sin(dEclipticLongitude);

        double dY = std::cos(dEclipticObliquity) * dSin_EclipticLongitude;
        double dX = std::cos(dEclipticLongitude);

        dRightAscension = atan2( dY,dX );
        if( dRightAscension < 0.0 ) dRightAscension += twopi;

        dDeclination = asin( sin( dEclipticObliquity )*dSin_EclipticLongitude );
        udtSunCoordinates->dDeclination = dDeclination;
    }

    // Compute local coordinates ( azimuth and zenith angle )
    {
        double dGreenwichMeanSiderealTime = 6.697096103 
                  + 0.06570984737 * dElapsedJulianDays
                  + dDecimalHours;

        double dLocalMeanSiderealTime = (dGreenwichMeanSiderealTime*15 + udtLocation.dLongitude)*rad;
        double dHourAngle = dLocalMeanSiderealTime - dRightAscension;      
        double dLatitudeInRadians = udtLocation.dLatitude * rad;

        double dCos_Latitude = std::cos( dLatitudeInRadians );
        double dSin_Latitude = std::sin( dLatitudeInRadians );
        double dSin_HourAngle = std::sin( dHourAngle );
        double dCos_HourAngle= std::cos( dHourAngle );

        udtSunCoordinates->dBoundedHourAngle = std::atan2(dSin_HourAngle, dCos_HourAngle); 

        double dZenithAngle = std::acos( dCos_Latitude*dCos_HourAngle * std::cos(dDeclination) 
                 + std::sin( dDeclination ) * dSin_Latitude );

        // Azimuth
        double dY = -std::sin( dHourAngle );
        double dX = std::tan( dDeclination ) * dCos_Latitude - dSin_Latitude * dCos_HourAngle;
        double dAzimuth = atan2( dY, dX );
        if ( dAzimuth < 0.0 ) dAzimuth += twopi;

        // Parallax Correction
        double dParallax=(dEarthMeanRadius/dAstronomicalUnit) * std::sin(dZenithAngle);
        dZenithAngle += dParallax;

        // Output results
        udtSunCoordinates->dAzimuth = dAzimuth;
        udtSunCoordinates->dZenithAngle = dZenithAngle;
    }
}