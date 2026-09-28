#ifndef PAGERBASESTATION_H
#define PAGERBASESTATION_H

#include <string>

// <<Adaptee>>
class PagerBaseStation {
public:
    int transmitPage(int zoneCode, const std::string& text, int urgency);
};

#endif
