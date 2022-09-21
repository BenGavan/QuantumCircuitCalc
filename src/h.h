#ifndef H_H
#define H_H

#include "qgate.h"
// #include "one_bit_qgate.h"

class H: public QGate {
protected:

public:
    
    H(const int &act_on_qb) : QGate{} { acts_on = act_on_qb; };
    // H(const int &act_on_qb) : OneBitQGate{act_on_qb} {};
    ~H() {};

    std::string getName() const;
    Matrix matrix() const;
    void applyTo(QCRegister &qb_register);
};

// // Hadamard Gate
// class H: public QGate {
// protected:

// public:
    
//     H(const int &act_on_qb) : QGate{} { acts_on = act_on_qb; };
//     ~H() {};

//     std::string getName() const;
//     Matrix matrix() const;
//     void applyTo(QBit &qb);
// };

// Matrix H::matrix() const {
//     Matrix m{2, 2};
//     m(0, 0) = 1 / std::sqrt(2);
//     m(1, 1) = -1 / std::sqrt(2);
//     return m;
// }

// void H::applyTo(QBit &qb) {
//     qb.state = this->matrix() * qb.state;
// }

// std::string H::getName() const {
//     return "H";
// }

#endif // H_H