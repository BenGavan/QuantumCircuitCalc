#ifndef QGATE_H
#define QGATE_H

#include <vector>
#include "qbit.h"
#include "qc_register.h"

class QGate {
public:
    QGate() {}
    ~QGate() {}
    int acts_on = -1;    // -1 = not set
    int depends_on = -1; // -1 = not set
    virtual void applyTo(QCRegister &qb_register) = 0;
    virtual std::string getName() const = 0;
    virtual Matrix matrix() const = 0;
};

#endif // QGATE_H
