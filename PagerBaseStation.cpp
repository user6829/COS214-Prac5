#include "PagerBaseStation.h"
// #include "Incident.h"
#include <iostream>

int PagerBaseStation::transmitPage(int zoneCode, const std::string& text, int urgency) {
    std::cout << "[PagerBaseStation] Transmitting Page -> Zone: " << zoneCode 
              << " | Urgency: " << urgency 
              << " | Message: " << text << std::endl;
    return 0;
}