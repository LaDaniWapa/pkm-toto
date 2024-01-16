#ifndef BATTLESCREEN_HPP
#define BATTLESCREEN_HPP

#include <raylib.h>

#include "battler.hpp"
#include "screenManager.hpp"

class BattleScreen : public Screen {
   private:
    Texture2D background, message;
    Battler *pokemon, *pokemonFoe;
    Font font, fontB;
    int pokemonPokedexNumber = 494, pokemonFoePokedexNumber = 494;

   public:
    void Load() override;
    void Unload() override;
    void Update() override;
    void Draw() override;

    void setPokemonPokedexNumber(int n);
    void setPokemonFoePokedexNumber(int n);
};

#endif  // BATTLESCREEN_HPP