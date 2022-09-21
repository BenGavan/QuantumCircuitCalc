#ifndef CX_H
#define CX_H

#include "qgate.h"

// controlled not (CNOT)
class CX: public QGate {
public:
    CX(const int &control_bit, const int &acts_on) : QGate{} { this->acts_on = acts_on; this->depends_on = control_bit; };
    void applyTo(QCRegister &qb_register);
    std::string getName() const;
    Matrix matrix() const;
};



#endif // CX_H