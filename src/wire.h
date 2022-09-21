#ifndef WIRE_H
#define WIRE_H

#include <vector>
#include "qgate.h"

class Wire {
protected:
    std::vector<std::stringstream> sss{3};

public:
    Wire(const std::string &label);
    void addGate(const std::shared_ptr<QGate> gate);
    void addLine();
    void addUpConnecter();
    void addDownConnecter();
    void addCrossing();
    void writeToStream(std::ostream &s);
};

#endif // WIRE_H