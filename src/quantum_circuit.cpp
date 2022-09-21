#include "quantum_circuit.h"
#include "wire.h"
#include "h.h"
#include "x.h"
#include "y.h"
#include "z.h"
#include "cx.h"


QuantumCircuit::QuantumCircuit(const int &n_qbs, const int &n_cbs) {
    if (n_qbs < 0 || n_cbs < 0) {
        std::cout << "Invalid number of QBits (" << n_qbs << ") or CBits (" << n_cbs << ")" << std::endl;
        return;
    }
    // qbits.resize(n_qbs);
    q_register = QCRegister(n_qbs);
    cbits.resize(n_cbs);
}

void QuantumCircuit::addQGate(std::shared_ptr<QGate> qgate_ptr) {
    gate_ptrs.push_back(qgate_ptr);
}

void QuantumCircuit::addH(const int &qb) {
    auto h = std::shared_ptr<H>(new H(qb));
    this->addQGate(h);
    h->applyTo(q_register);
}

void QuantumCircuit::addX(const int &qb) {
    auto x = std::shared_ptr<X>(new X(qb));
    this->addQGate(x);
    x->applyTo(q_register);
}

void QuantumCircuit::addY(const int &qb) {
    auto x = std::shared_ptr<Y>(new Y(qb));
    this->addQGate(x);
    x->applyTo(q_register);
}

void QuantumCircuit::addZ(const int &qb) {
    auto x = std::shared_ptr<Z>(new Z(qb));
    this->addQGate(x);
    x->applyTo(q_register);
}

void QuantumCircuit::addCX(const int &control_qb, const int &acting_on_qb) {
    auto cx = std::shared_ptr<CX>(new CX(control_qb, acting_on_qb));
    this->addQGate(cx);
    cx->applyTo(q_register);
}

std::string QuantumCircuit::toString() const {
    std::stringstream ss;
    // ss <<   "# qbits: " << q_register.size();
    // ss << "\n# cbits: " << cbits.size();
    // ss << "\nCircuit: " << std::endl;

    std::vector<Wire> wires;

    for (unsigned i=0; i<q_register.size(); i++) {
        wires.push_back(Wire{"qb." + std::to_string(i)});
    }

    for (unsigned i=0; i<cbits.size(); i++) {
        wires.push_back(Wire{"cb." + std::to_string(i)});
    }

    // ss << "n_wires: " << wires.size() << std::endl;

    for (auto iter=gate_ptrs.begin(); iter!=gate_ptrs.end(); ++iter) {
        for (int i=0; i<wires.size(); i++) {
            // std::cout << (*iter)->depends_on << ", " << (*iter)->acts_on << std::endl; 

            if ((*iter)->acts_on == i) {
                wires[i].addGate(*iter);
                continue;
            }
            if ((*iter)->depends_on == i) {
                wires[i].addDownConnecter();
                continue;
            }
            wires[i].addLine();
        }
    }
    ss << std::endl;

    for (auto iter=wires.begin(); iter!=wires.end(); ++iter) {
        (*iter).writeToStream(ss);
        // (*iter).writeToStream(std::cout);
    }


    // std::cout << "Length of gates: " << gate_ptrs.size() << std::endl;
    // std::cout << (*gate_ptrs.begin())->getName();
    
    
    // std::cout << "Adding gate" << std::endl;
    // std::cout << gate_ptrs[0]->acts_on[0] << std::endl;
    // std::cout << "made it" << std::endl;
    // w.addGate(gate_ptrs[0]);
    // std::cout << "writing to stream" << std::endl;
    // w.writeToStream(ss);
    ss << std::endl;
    return ss.str();
}



/*
     ┌───┐                     ░ ┌─┐      
q_0: ┤ H ├──■────■────■────■───░─┤M├──────
     └───┘┌─┴─┐  │  ┌─┴─┐  │   ░ └╥┘┌─┐   
q_1: ─────┤ X ├──┼──┤ X ├──┼───░──╫─┤M├───
          └───┘┌─┴─┐└───┘┌─┴─┐ ░  ║ └╥┘┌─┐
q_2: ──────────┤ X ├─────┤ X ├─░──╫──╫─┤M├
               └───┘     └───┘ ░  ║  ║ └╥┘
c: 3/═════════════════════════════╩══╩══╩═

*/