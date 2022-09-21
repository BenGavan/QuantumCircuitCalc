#include "wire.h"

Wire::Wire(const std::string &label) {
    std::string space;
    for (unsigned i=0; i<label.length()+2; i++) {
        space += " ";
    }
    sss[0] << space << std::flush;
    sss[1] << label << ": " << std::flush;
    sss[2] << space << std::flush;
}

void Wire::addGate(const std::shared_ptr<QGate> gate) {
    sss[0] <<  " ┌───┐ " << std::flush;
    sss[1] << "─┤ " << gate->getName() << " ├─" << std::flush;
    sss[2] <<  " └───┘ " << std::flush;
}

void Wire::addLine() {
    std::string line = "───────";
    std::string space = "       ";
    sss[0] << space << std::flush;
    sss[1] << line << std::flush;
    sss[2] << space << std::flush;
}

void Wire::addDownConnecter() {
    sss[0] << "       " << std::flush;
    sss[1] <<  "───■───" << std::flush;
    sss[2] << "   │   " << std::flush;
    
}

void Wire::writeToStream(std::ostream &s) {
    for (unsigned i=0; i<3; i++) {
        s << sss[i].str() << std::endl; 
    }
}
