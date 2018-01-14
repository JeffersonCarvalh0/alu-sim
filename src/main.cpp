# include "datapath.h"
# include <iostream>
# include <string>

using namespace std;

int main() {
    // Create the devices of the datapath
    RegisterBank *registerBank = new RegisterBank();
    ControlUnit *control = new ControlUnit();
    ALUControl *aluControl = new ALUControl();
    FullALU *alu = new FullALU();
    MainMemory *mem = new MainMemory();

    // Create the datapath
    MinorDevices *others = new MinorDevices();
    Datapath datapath(registerBank, control, aluControl, alu, mem, others);

    // vector<bit> addi = {
    //     // addi $t0, $zero, 5
    //     0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1
    // };

    string addi = "00100000000010000000000000000101";

    datapath.setInstruction(addi);
    datapath.processInstruction();
    datapath.showRegData();
    datapath.showALUData();
    datapath.showMainMemData();

    return 0;
}
