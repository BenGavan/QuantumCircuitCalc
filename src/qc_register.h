#ifndef QC_REGISTER_H
#define QC_REGISTER_H

#include "qbit.h"
#include "matrix.h"
#include <vector>

class QCRegister {
protected:
    Matrix vector;
    bool is_finished = false;
public:
    std::vector<QBit> qbits;
    
    QCRegister() {};
    QCRegister(const int &nqbits);

    // only available when is_finished = false
    void addQBit(QBit qb);
    void addQBit();
    void addQBit(const int &x);
    void addQBitInStdState(const int &x);

    int size() const { return qbits.size(); };

    Matrix getVector();
    // void setVector(Matrix v);
    void applyMatrix(const Matrix &m);

    void finish();
};

#endif // QC_REGISTER_H
