#include "cx.h"

Matrix CX::matrix() const {
    // depends_on
    // TODO: calculate for sepecific register
    Matrix m{4, 4};
    m(0, 0) = 1;
    m(1, 1) = 1;
    m(2, 3) = 1;
    m(3, 2) = 1;
    return m;
}

void CX::applyTo(QCRegister &qb_register) {
    qb_register.applyMatrix(matrix()); // apply CNOT
}

std::string CX::getName() const {
    return "X";
}
