#ifndef Z_H
#define Z_H

#include "qgate.h"

class Z: public QGate {
public:
    Z(const int &acts_on) : QGate{} { this->acts_on = acts_on; };
    
    void applyTo(QCRegister &qb_register);
    std::string getName() const;
    Matrix matrix() const;
};

#endif // Z_H