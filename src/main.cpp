#include <tuple>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

#include <string>

#include <iostream>

#include "sunpos.h"

void ReadMICAData(std::string& filename,  std::vector<std::tuple<cLocation, cTime, cSunCoordinates>>& data);


int main()
{
    //Reading MICA Data
    std::cout << "Reading MICA Data!" << std::endl;

    //Assume a specific MICA Data input file and location
    std::string input_file = "../../test_data/MICA_reference_data.csv";

    // Create a vector of <cLocation, cTme, cSunCoordinates> tuples to store the result of reading the MICA data
    std::vector<std::tuple<cLocation, cTime, cSunCoordinates>> MICA_data;

    ReadMICAData(input_file, MICA_data);

    std::cout << "Total MICA points read: " << MICA_data.size() << std::endl << std::endl;

    cLocation location;
    cTime time;
    cSunCoordinates sunCoordinates_MICA;
    cSunCoordinates sunCoordinates_sunpos;

    std::cout << std::fixed << std::setprecision(5);
    for (auto & element : MICA_data)
    {
        location = std::get<0>(element);
        time = std::get<1>(element);
        sunCoordinates_MICA = std::get<2>(element);
        sunpos(time,location, &sunCoordinates_sunpos); // Call to the updated PSA sun position algorithm

        std::cout << "Latitude (deg): " << location.dLatitude << ", \n"
                  << "longitude (deg): " << location.dLongitude << ", \n"
                  << "year: " << time.iYear << ", \n"
                  << "month: " << time.iMonth << ", \n"
                  << "day: " << time.iDay << ", \n"
                  << "hour: " << time.dHours << ", \n"
                  << "minute: " << time.dMinutes << ", \n"
                  << "seconds: " << time.dSeconds << ", \n"
                  << "Zenith Angle MICA (deg): " << sunCoordinates_MICA.dZenithAngle << ", \n"
                  << "Zenith Angle PSA+ (deg): " << sunCoordinates_sunpos.dZenithAngle/rad << ", \n"
                  << "Azimuth MICA (deg): " << sunCoordinates_MICA.dAzimuth << ", \n"
                  << "Azimuth PSA+ (deg): " << sunCoordinates_sunpos.dAzimuth/rad << ", \n"
                  << "Zenith Angle Error (arc seconds): " << (sunCoordinates_sunpos.dZenithAngle/rad - sunCoordinates_MICA.dZenithAngle)*3600.0 << ", \n"
                  << "Azimuth Error (arc seconds): " << (sunCoordinates_sunpos.dAzimuth/rad - sunCoordinates_MICA.dAzimuth)*3600.0 << ", \n"
                  << "----------------------------------------------- \n";
    }

    std::string output_file = "PSA+ComparisonWithMica.csv";

    // Create an output filestream
    std::ofstream myFile(output_file);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    myFile << std::fixed << std::setprecision(7);
    for (auto & element : MICA_data)
    {
        location = std::get<0>(element);
        time = std::get<1>(element);
        sunCoordinates_MICA = std::get<2>(element);
        sunpos(time,location, &sunCoordinates_sunpos);

        myFile << location.dLatitude << ","
               << location.dLongitude << ","
               << time.iYear << ","
               << time.iMonth << ","
               << time.iDay << ","
               << time.dHours << ","
               << time.dMinutes << ","
               << time.dSeconds << ","
               << sunCoordinates_MICA.dZenithAngle << ","
               << sunCoordinates_sunpos.dZenithAngle/rad << ","
               << sunCoordinates_MICA.dAzimuth << ","
               << sunCoordinates_sunpos.dAzimuth/rad << ","
               << (sunCoordinates_sunpos.dZenithAngle/rad - sunCoordinates_MICA.dZenithAngle)*3600.0 <<","
               << (sunCoordinates_sunpos.dAzimuth/rad - sunCoordinates_MICA.dAzimuth)*3600.0 << "\n";
    }

    // Close file
    myFile.close();

    return 0;
}

void ReadMICAData(std::string& filename,  std::vector<std::tuple<cLocation, cTime, cSunCoordinates>>& data)
{
    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;

    // Read data, line by line
    while(std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        cLocation location;

        ss >> location.dLatitude;
        if(ss.peek() == ',') ss.ignore();
        ss >> location.dLongitude;
         if(ss.peek() == ',') ss.ignore();

        cTime time;

        ss >> time.iYear;
        if(ss.peek() == ',') ss.ignore();
        ss >> time.iMonth;
        if(ss.peek() == ',') ss.ignore();
        ss >> time.iDay;
        if(ss.peek() == ',') ss.ignore();
        ss >> time.dHours;
        if(ss.peek() == ',') ss.ignore();
        ss >> time.dMinutes;
        if(ss.peek() == ',') ss.ignore();
        ss >> time.dSeconds;
        if(ss.peek() == ',') ss.ignore();

        cSunCoordinates sunAngles;

        ss >> sunAngles.dZenithAngle;
        if(ss.peek() == ',') ss.ignore();
        ss >> sunAngles.dAzimuth;

        data.push_back(std::make_tuple(location, time, sunAngles));
    }

    // Close file
    myFile.close();
}
