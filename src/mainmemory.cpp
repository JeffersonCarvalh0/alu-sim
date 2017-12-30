# include "mainmemory.h"
# include "utils.h"     // bitVecToInt
# include <vector>
# include <cmath>       // log2

using namespace std;

// AddressDecoder
void AddressDecoder::decode(const vector<bit> &address,
    vector<MemoryChip> &chips) {
    int selectedChip = bitVecToInt(address);

    int size = chips.size();

    for (int i = 0; i < size; ++i)
        chips[i].CS = (i == selectedChip) ? 0 : 1;
}

// MemoryChip
vector<bit> MemoryChip::readData() const {
    vector<bit> data(WORD);
    for (int i = 0; i < WORD; ++i)
        data[i] = cells[i].data;

    return data;
}

void MemoryChip::writeData(const vector<bit> &data) {
    for (int i = 0; i < WORD; ++i)
        cells[i].data = data[i];
}

// Main Memory
MainMemory::MainMemory(const int size) {
    this->size = size;
    chipsNum = size / WORD;
    addrLinesNum = log2(chipsNum);
    memChips = vector<MemoryChip>(chipsNum);
}

void MainMemory::process() {
    decoder.decode(address, memChips);

    for (auto &chip : memChips) {
        if (memWrite)
            chip.WR = 0;
        else if (memRead)
            chip.WR = 1;

        if (chip.CS && chip.WR) // Selected for read
            readData = chip.readData();
        else if(chip.CS && !chip.WR) // Selected for write
            chip.writeData(writeData);
    }
}
