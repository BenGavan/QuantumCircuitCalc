#include "z.h"

void Z::applyTo(QCRegister &qb_register) {
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

    std::cout << x << std::endl;
    
    qb_register.applyMatrix(x); // apply X
}

Matrix Z::matrix() const {
    Matrix m{2, 2};
    m(1, 0) = {1, 0};
    m(0, 1) = {-1, 0};
    return m;
}

std::string Z::getName() const {
    return  "Z";
}
