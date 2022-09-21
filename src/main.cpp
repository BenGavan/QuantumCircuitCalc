#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <complex>

#include "qbit.h"
#include "qgate.h"
#include "quantum_circuit.h"
#include "matrix.h"

#include "h.h"
#include "x.h"
#include "y.h"
#include "z.h"


int main() {
    std::cout << "--------------------------" << std::endl;
    std::cout << "Qauntum circuit calculator" << std::endl;
    std::cout << "--------------------------\n\n" << std::endl;

    QuantumCircuit qcirc{2, 1};

    qcirc.q_register.finish();
    std::cout << "Intial:\n" << qcirc.q_register.getVector() << std::endl;

    qcirc.addX(0);
    qcirc.addH(0);
    qcirc.addCX(0, 1);
    qcirc.addH(1);

    // Apply inverse
    qcirc.addH(1);
    qcirc.addCX(0, 1);
    qcirc.addH(0);
    qcirc.addX(0);

    // std::cout << qcirc.q_register.getVector() << std::endl;

    std::cout << qcirc.toString();

    std::cout << "Final:\n" << qcirc.q_register.getVector() << std::endl;


    return 0;

    // assert(1==1);

    std::shared_ptr<H> h{new H(0)}; 
    std::cout << h->matrix() << std::endl;
    std::cout << "H acts on: " << h->acts_on << std::endl;

    std::vector<std::shared_ptr<QGate>> gates;
    gates.push_back(h);
    std::cout << gates[0]->acts_on << std::endl;
    std::cout << "len: " << gates.size() << std::endl;

    qcirc.addQGate(h);
    qcirc.addQGate(h);
    qcirc.addQGate(std::shared_ptr<H>{new H(1)});
    qcirc.addQGate(std::shared_ptr<X>{new X{0}});
    qcirc.addQGate(std::shared_ptr<Y>{new Y{0}});
    qcirc.addQGate(std::shared_ptr<Z>{new Z{0}});
    qcirc.addH(1);
    qcirc.addX(0);
    std::cout << qcirc.toString();
    // qcirc.addQGate();
    // std::shared_ptr<H>(new H{1});

    // for (auto iter=qcirc.qbits.begin(); iter!=qcirc.qbits.end(); ++iter) {
    //     std::cout << iter->toString() << std::endl;
    // }

    
    // qcirc.addQGate();

    return 0;
}
