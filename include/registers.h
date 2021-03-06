# ifndef REGISTERS_H
# define REGISTERS_H

# include "defs.h"
# include <vector>

/* In this file, the processor's registers and its register bank are defined. */

# define REG_NUM 32

class Register {
    /* Represents a single register. */
    friend class RegisterBank;
private:
    std::vector<bit> data;

public:
    Register();
    void operator = (std::vector<bit> &r);
};

class RegisterBank {
    /* Represents the bank of registers in the datapath. */
    friend class Datapath;

private:
    std::vector<Register> registers;
    std::vector<bit> readReg1, readReg2, writeReg, writeData; // Inputs
    std::vector<bit> readData1, readData2; // Outputs
    bool regWrite; // Control line

public:
    RegisterBank();
    void read();
    void write();
};

# endif /* end of include guard: REGISTERS_H */
