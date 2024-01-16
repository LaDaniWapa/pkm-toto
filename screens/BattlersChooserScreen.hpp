#ifndef BATTLERCHOOSERSCREEN_HPP
#define BATTLERCHOOSERSCREEN_HPP

#include <raylib.h>

#include "screenManager.hpp"
#include "type.hpp"
#include "utils.hpp"
#include "BattlerListScreen.hpp"
#include "BattleScreen.hpp"

class BattlersChooserScreen : public Screen {
   private:
    // Texturas de los pokemons
    Texture2D pokemonTexture, pokemonFoeTexture;
    // Textura de los tipos
    Texture2D typesTexture;
    // Fuente
    Font font;
    // Estructura de los pokemons
    Pkm pokemon, pokemonFoe;
    // Shadder
    Shader outlineShader;
    // Rectangles para recortar la textura de tipos
    Rectangle type1, type2, type1Foe, type2Foe;
    // Numeros de la pokedex
    int pkxn, pkxnF;
    // Posicion del raton
    Vector2 mousePoint{.0f, .0f};
    // Usar outlineShader o no
    bool pokemonShader = false, pokemonFoeShader = false;

   public:
    void Load() override;
    void Unload() override;
    void Update() override;
    void Draw() override;

    void setPokemon(int pokedexnumber);
    void setFoePokemon(int pokedexnumber);
};

#endif  // BATTLERCHOOSERSCREEN_HPP