// Hadamard Gate
#include "h.h"

Matrix H::matrix() const {
    Matrix m{2, 2};
    m(0, 0) = 1 / std::sqrt(2);
    m(1, 0) = 1 / std::sqrt(2);
    m(0, 1) = 1 / std::sqrt(2);
    m(1, 1) = -1 / std::sqrt(2);
    return m;
}

void H::applyTo(QCRegister &qb_register) {
    Matrix m = matrix();

    Matrix identity(2, 2);
    identity(0, 0) = 1;
    identity(1, 1) = 1;

    Matrix x;
    x = (this->acts_on == 0) ? m : identity;
    
    for (int i=1; i<qb_register.size(); i++) {
        if (i == this->acts_on) {
            x = x.tensor_product(m);
        } else {
            x = x.tensor_product(identity);
        }
    }
    
    qb_register.applyMatrix(x); // apply H
}

std::string H::getName() const {
    return "H";
}
