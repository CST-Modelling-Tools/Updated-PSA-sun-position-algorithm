#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>

#include "sunpos.h"

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <latitude> <longitude> <UTC_date_time>" << std::endl;
        std::cerr << "Example: " << argv[0] << " 40.7128 -74.0060 \"2026-03-24 15:52:52\"" << std::endl;
        return 1;
    }

    // Parse latitude
    double latitude;
    try {
        latitude = std::stod(argv[1]);
    } catch (const std::exception&) {
        std::cerr << "Invalid latitude: " << argv[1] << std::endl;
        return 1;
    }

    // Parse longitude
    double longitude;
    try {
        longitude = std::stod(argv[2]);
    } catch (const std::exception&) {
        std::cerr << "Invalid longitude: " << argv[2] << std::endl;
        return 1;
    }

    // Parse date time string
    std::string dateTimeStr = argv[3];
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        std::cerr << "Invalid date format. Use YYYY-MM-DD HH:MM:SS" << std::endl;
        return 1;
    }

    cLocation location;
    location.dLatitude = latitude;
    location.dLongitude = longitude;

    cTime time;
    time.iYear = tm.tm_year + 1900;
    time.iMonth = tm.tm_mon + 1;
    time.iDay = tm.tm_mday;
    time.dHours = tm.tm_hour;
    time.dMinutes = tm.tm_min;
    time.dSeconds = tm.tm_sec;

    cSunCoordinates sunCoordinates;

    sunpos(time, location, &sunCoordinates);

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Latitude: " << location.dLatitude << " degrees" << std::endl;
    std::cout << "Longitude: " << location.dLongitude << " degrees" << std::endl;
    std::cout << "Date/Time: " << dateTimeStr << " UTC" << std::endl;
    std::cout << "Zenith Angle: " << sunCoordinates.dZenithAngle / rad << " degrees" << std::endl;
    std::cout << "Azimuth: " << sunCoordinates.dAzimuth / rad << " degrees" << std::endl;
    std::cout << "Declination: " << sunCoordinates.dDeclination / rad << " degrees" << std::endl;

    return 0;
}