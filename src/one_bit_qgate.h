#ifndef ONE_BIT_QGATE
#define ONE_BIT_QGATE

#include "qgate.h"

class OneBitQGate: public QGate {
public:
    OneBitQGate(const int &act_on_qb) : QGate{} { acts_on = {act_on_qb}; };
    ~OneBitQGate() {};

    void applyTo(QBit &qb);
};

void OneBitQGate::applyTo(QBit &qb) {
    qb.state = this->matrix() * qb.state;
}

#endif // ONE_BIT_QGATE