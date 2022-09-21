#ifndef X_H
#define X_H

#include "qgate.h"

class X: public QGate {
public:
    X(const int &acts_on) : QGate{} { this->acts_on = acts_on; };
    
    void applyTo(QCRegister &qb_register);
    std::string getName() const;
    Matrix matrix() const;
};

#endif // X_H