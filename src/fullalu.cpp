# include "fullalu.h"
# include <iostream>

using namespace std;

FullALU::FullALU() {
    aluArr = vector<ALU*>(BITS);
    for (int i = BITS - 1; i > 0; --i)
        aluArr[i] = new ALU();
    aluArr[0] = new MSALU();

    result = vector<bit>(BITS, 0);
}

inline void FullALU::setBits(const int i, const bit lastCarryOut) const {
    aluArr[i]->AInvert = AInvert;
    aluArr[i]->BInvert = BNegate;
    aluArr[i]->carryIn = lastCarryOut;
    aluArr[i]->a = inputA[i];
    aluArr[i]->b = inputB[i];
    aluArr[i]->less = 0;
}

void FullALU::process() {
    bit lastCarryOut = BNegate;

    for (int i = BITS - 1; i >= 0; --i) {
        cout << "ULA Atual: " << i << '\n';
        setBits(i, lastCarryOut);
        aluArr[i]->process(operation);
        result[i] = aluArr[i]->result;
        lastCarryOut = aluArr[i]->carryOut;
    }

    overflow = static_cast<MSALU*>(aluArr[0])->overflow;
    aluArr[BITS - 1]->less = static_cast<MSALU*>(aluArr[0])->set;
    aluArr[BITS - 1]->AInvert = aluArr[BITS - 1]->BInvert = false;
    aluArr[BITS - 1]->process(operation);
    result[BITS - 1] = aluArr[BITS - 1]->result;
}