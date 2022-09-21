#ifndef Y_H
#define Y_H

#include "qgate.h"

class Y: public QGate {
public:
    Y(const int &acts_on) : QGate{} { this->acts_on = acts_on; };
    
    void applyTo(QCRegister &qb_register);
    std::string getName() const;
    Matrix matrix() const;
};

#endif // Y_H