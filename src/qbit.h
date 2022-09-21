#ifndef QBIT_H
#define QBIT_H

#include <string>
#include "matrix.h"

class QBit {
protected:
    
public:
    Matrix state{2, 1};
    std::string toString() const;
    void set_std_state(const int &new_std_state);

    QBit() { set_std_state(0); };
    QBit(const int &std_state) { set_std_state(std_state); };
};

#endif // QBIT_H