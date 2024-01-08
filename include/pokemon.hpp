#ifndef POKEMON_HPP
#define POKEMON_HPP

#define IV (std::rand() % 32)  // Random 0 ~ 31
#define EV 510                 // Max EV

#include "type.hpp"
#include "utils.hpp"

class Pokemon {
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

    Texture2D pokemonTexture;
    Texture2D databox;
    Texture2D base;
    Texture2D health;
    Rectangle healthRect;

    Font font;
    Font fontB;

    uint16_t getStat(uint8_t baseStat) {
        return (((baseStat * 2 + IV + EV / 4) * level / 100) + 5);
    }

   public:
    Pokemon(int pokedexNumber, int level, bool foe, Font font, Font fontB);
    ~Pokemon();

    void draw();
    void updateHeatlRect();
};

Pokemon::Pokemon(int pokedexNumber, int level, bool foe, Font font, Font fontB) {
    this->foe = foe;
    this->font = font;
    this->fontB = fontB;
    this->level = level;

    if (readPokemonFromFile(pokedexNumber, basePkm)) {
        printPokemon(basePkm);

        maxPS = ((basePkm.ps * 2 + IV + EV / 4) * level / 100) + 10 + level;
        currentPS = maxPS;
        updateHeatlRect();
        attack = getStat(basePkm.attack);
        defense = getStat(basePkm.defense);
        specialAttack = getStat(basePkm.specialAttack);
        specialDefense = getStat(basePkm.specialDefense);
        speed = getStat(basePkm.speed);
        male = std::rand() % 2;

        pokemonTexture = getPokemonTexture(pokedexNumber, !foe);
        health = LoadTexture("assets/overlay_hp.png");

        if (foe) {
            databox = LoadTexture("assets/databox_normal_foe.png");
            base = LoadTexture("assets/BattleBacks/grass_base1.png");
        } else {
            databox = LoadTexture("assets/databox_normal.png");
            base = LoadTexture("assets/BattleBacks/grass_base0.png");
        }
    }
}

Pokemon::~Pokemon() {
    UnloadTexture(pokemonTexture);
    UnloadTexture(databox);
    UnloadTexture(base);
    UnloadFont(font);
    UnloadFont(fontB);
}

void Pokemon::draw() {
    if (this->foe) {
        DrawTexture(base, 256, 100, WHITE);
        DrawTexture(databox, 0, 37, WHITE);
        DrawTextEx(font, basePkm.name, Vector2{7, 50}, 20, 1, PKGREY);
        DrawTextureRec(health, healthRect, Vector2{118, 77}, WHITE);
        DrawTextEx(fontB, TextFormat("Lv.%i", level), Vector2{170, 52}, 11, 1, PKGREY);
        DrawTexture(pokemonTexture, 285, 15, WHITE);
    } else {
        DrawTexture(base, -145, 240, WHITE);
        DrawTexture(databox, 252, 192, WHITE);
        DrawTextEx(font, basePkm.name, Vector2{295, 205}, 20, 1, PKGREY);
        DrawTextureRec(health, healthRect, Vector2{388, 232}, WHITE);
        DrawTextEx(fontB, TextFormat("%i/%i", currentPS, maxPS), Vector2{400, 245}, 11, 1, PKGREY);
        DrawTextEx(fontB, TextFormat("Lv.%i", level), Vector2{440, 207}, 11, 1, PKGREY);
        DrawTextureEx(pokemonTexture, Vector2{20, 90}, 0, 1.25f, WHITE);
    }
}

void Pokemon::updateHeatlRect() {
    float percent = currentPS * 100 / maxPS;

    // 0 green 1 orange 2 red
    uint8_t color;

    if (currentPS < maxPS / 3)
        color = 2;
    else if (currentPS < maxPS * 2 / 3)
        color = 1;
    else
        color = 0;

    this->healthRect = {0, 6.f * color, 96 * percent / 100, 6};
}

#endif  // POKEMON_HPP