#include "qbit.h"


std::string QBit::toString() const {
    std::stringstream ss;
    ss << state << std::flush;
    return ss.str();
}

void QBit::set_std_state(const int &new_std_state) {
    // could change to state[new_std_state] = 1; state[(new_std_state+1)%2] = 0;
    state = Matrix{2, 1};
    state(new_std_state, 0) = 1;
    // switch (new_std_state) {
    // case 0:
    //     state(1, 1) = 1;
    //     break;
    // case 1:
    //     state(2, 1) = 1;
    // default:
    //     break;
    // }
}
