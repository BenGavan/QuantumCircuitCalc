#ifndef QUANTUM_CIRCUIT
#define QUANTUM_CIRCUIT

#include <vector>
#include <memory>
#include "qgate.h"
// #include "qbit.h"
#include "qc_register.h"
#include "cbit.h"

class QuantumCircuit {
protected:
    std::vector<std::shared_ptr<QGate>> gate_ptrs;    

public:
    QCRegister q_register;
    std::vector<CBit> cbits;
    QuantumCircuit(const int &n_qbs, const int &n_cbs);
    void addQGate(std::shared_ptr<QGate> qgate_ptr);
    void addH(const int &qb);
    void addX(const int &qb);
    void addY(const int &qb);
    void addZ(const int &qb);
    void addCX(const int &control_qb, const int &acting_on_qb);
    
    std::string toString() const;
};

#endif // QUANTUM_CIRCUIT