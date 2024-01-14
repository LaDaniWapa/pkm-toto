#ifndef BATTLER_HPP
#define BATTLER_HPP

#include "type.hpp"
#include "utils.hpp"

class Battler {
   private:
    uint8_t level;
    Pkm basePkm;
    uint16_t maxPS;
    uint16_t currentPS;
    uint16_t attack;
    uint16_t defense;
    uint16_t specialAttack;
    uint16_t specialDefense;
    uint16_t speed;
    bool male;

    bool foe;

    Texture2D battlerTexture;
    Texture2D databox;
    Texture2D base;
    Texture2D health;
    Rectangle healthRect;

    Font font;
    Font fontB;

    Font font2;

    uint16_t getStat(uint8_t baseStat) {
        return (((baseStat * 2 + IV + EV / 4) * level / 100) + 5);
    }

   public:
    Battler(int pokedexNumber, int level, bool shiny, bool foe, Font& font, Font& fontB);
    ~Battler();

    void draw();
    void updateHeatlRect();
};

#endif  // BATTLER_HPP