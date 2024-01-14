#include "utils.hpp"

void printBattler(const Pkm& battler) {
    std::cout << "ID: " << battler.ID << std::endl;
    std::cout << "Name: " << battler.name << std::endl;
    std::cout << "PS: " << battler.ps << std::endl;
    std::cout << "Attack: " << static_cast<int>(battler.attack) << std::endl;
    std::cout << "Defense: " << static_cast<int>(battler.defense) << std::endl;
    std::cout << "Special Attack: " << static_cast<int>(battler.specialAttack) << std::endl;
    std::cout << "Special Defense: " << static_cast<int>(battler.specialDefense) << std::endl;
    std::cout << "Speed: " << static_cast<int>(battler.speed) << std::endl;
    std::cout << "Type 1: " << static_cast<int>(battler.type1) << std::endl;
    std::cout << "Type 2: " << static_cast<int>(battler.type2) << std::endl;
    std::cout << std::endl;
}

void printBattlerHex(const Pkm& battler) {
    std::cout << "Name: " << std::dec << battler.name << std::endl;
    std::cout << "ID: 0x" << std::hex << std::setw(4) << std::setfill('0') << battler.ID << std::dec << std::endl;
    std::cout << "PS: 0x" << std::hex << std::setw(4) << std::setfill('0') << battler.ps << std::dec << std::endl;
    std::cout << "Attack: 0x" << std::hex << static_cast<int>(battler.attack) << std::dec << std::endl;
    std::cout << "Defense: 0x" << std::hex << static_cast<int>(battler.defense) << std::dec << std::endl;
    std::cout << "Special Attack: 0x" << std::hex << static_cast<int>(battler.specialAttack) << std::dec << std::endl;
    std::cout << "Special Defense: 0x" << std::hex << static_cast<int>(battler.specialDefense) << std::dec << std::endl;
    std::cout << "Speed: 0x" << std::hex << static_cast<int>(battler.speed) << std::dec << std::endl;
    std::cout << "Type 1: 0x" << std::hex << static_cast<int>(battler.type1) << std::dec << std::endl;
    std::cout << "Type 2: 0x" << std::hex << static_cast<int>(battler.type2) << std::dec << std::endl;
    std::cout << std::endl;
}

std::string randomPkm(bool back) {
    uint16_t randomPkm = (rand() % (649 - 494 + 1)) + 494;

    return "assets/gen5pkm/" + std::to_string(randomPkm) + (back ? "b.png" : ".png");
}

Texture2D getBattlerTexture(int battlerPokedexNumber, bool shiny, bool back) {
    
    std::string str = "assets/gen5pkm/" + std::to_string(battlerPokedexNumber) + (shiny ? "s" : "") + (back ? "b" : "") + ".png";

    return LoadTexture(str.c_str());
}

void saveToFile(const Pkm& pkm) {
    std::ofstream outFile("pokedex.dat", std::ios::binary | std::ios::app);

    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(&pkm), sizeof(Pkm));

        outFile.close();
    } else {
        std::cerr << "Error opening the file for writing." << std::endl;
    }
}

bool readBattlerFromFile(uint16_t pokedexNumber, Pkm& pkm) {
    std::ifstream inFile("pokedex.dat", std::ios::binary);

    if (!inFile.is_open()) {
        // Print an error message with the specific error
        std::cerr << "Error opening the file: " << strerror(errno) << "\n";
        return false;
    }

    std::streampos position = (pokedexNumber - 494) * sizeof(Pkm);
    inFile.seekg(position, std::ios::beg);
    inFile.read(reinterpret_cast<char*>(&pkm), sizeof(Pkm));

    if (inFile.fail() && !inFile.eof()) {
        // Print an error message if the read operation fails
        std::cerr << "Error reading from the file: " << strerror(errno) << "\n";
        inFile.close();
        return false;
    }

    inFile.close();

    return true;
}

bool saveBattlersToDatFile() {
    Pkm pkm;
    std::ifstream inputFile("P2.csv");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return false;
    }

    // Define a vector to store rows from the CSV file
    std::vector<std::vector<std::string>> csvData;

    // Read the file line by line
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream ss(line);
        std::vector<std::string> row;

        // Split the line into fields using a comma as a delimiter
        while (std::getline(ss, line, ',')) {
            row.push_back(line);
        }

        // Add the row to the vector
        csvData.push_back(row);
    }

    inputFile.close();

    for (const auto& row : csvData) {
        pkm = Pkm{};

        pkm.ID = static_cast<uint16_t>(std::strtoul(row[0].c_str(), nullptr, 0));
        pkm.ps = static_cast<uint16_t>(std::strtoul(row[2].c_str(), nullptr, 0));
        pkm.attack = static_cast<uint8_t>(std::strtoul(row[3].c_str(), nullptr, 0));
        pkm.defense = static_cast<uint8_t>(std::strtoul(row[4].c_str(), nullptr, 0));
        pkm.specialAttack = static_cast<uint8_t>(std::strtoul(row[5].c_str(), nullptr, 0));
        pkm.specialDefense = static_cast<uint8_t>(std::strtoul(row[6].c_str(), nullptr, 0));
        pkm.speed = static_cast<uint8_t>(std::strtoul(row[7].c_str(), nullptr, 0));
        pkm.type1 = static_cast<uint8_t>(std::strtoul(row[8].c_str(), nullptr, 0));
        if (row.size() == 10) pkm.type2 = static_cast<uint8_t>(std::strtoul(row[9].c_str(), nullptr, 0));

        strncpy(pkm.name, row[1].c_str(), sizeof(pkm.name) - 1);
        pkm.name[sizeof(pkm.name) - 1] = '\0';

        printBattlerHex(pkm);

        saveToFile(pkm);
    }

    return true;
}
