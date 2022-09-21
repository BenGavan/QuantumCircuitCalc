#include "qc_register.h"

QCRegister::QCRegister(const int &nqbits) {
    qbits = std::vector<QBit>(nqbits);
}

void QCRegister::addQBit() {
    qbits.push_back(QBit());
}

void QCRegister::addQBit(const int &x) {
    qbits.push_back(QBit(x));
}

void QCRegister::addQBitInStdState(const int &x) {
    addQBit(x);
}

Matrix QCRegister::getVector() {
    return vector;
}

void QCRegister::applyMatrix(const Matrix &m) {
    vector = m * vector;
}

void QCRegister::finish() {
    if (size() == 0) return;

    vector = qbits[0].state;
    for (int i=1; i<size(); i++) {
        vector = vector.tensor_product(qbits[i].state);
    }

    is_finished = true;
}
