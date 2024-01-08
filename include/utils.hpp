#ifndef UTILS_HPP
#define UTILS_HPP

#define PGREY 
#define PKGREY      CLITERAL(Color){ 72, 72, 72, 255 }


#include <raylib.h>
#include <time.h>

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef struct Pkm {
    uint16_t ID;
    uint16_t ps;
    uint8_t attack;
    uint8_t defense;
    uint8_t specialAttack;
    uint8_t specialDefense;
    uint8_t speed;
    uint8_t type1;
    uint8_t type2;
    char name[18];
} Pkm;

/**
 * @brief Imprime los detalles de un Pokémon en formato hexadecimal.
 *
 * @param pokemon La estructura del Pokémon que se imprimirá.
 */
void printPokemon(const Pkm& pokemon);

/**
 * @brief Imprime los detalles de un Pokémon en formato hexadecimal.
 *
 * @param pokemon La estructura del Pokémon que se imprimirá en formato hexadecimal.
 */
void printPokemonHex(const Pkm& pokemon);

/**
 * @brief Genera la ruta a un archivo de imagen de un Pokémon aleatorio.
 *
 * @param back Indica si se busca la imagen posterior del Pokémon.
 * @return La ruta al archivo de imagen del Pokémon aleatorio.
 */
std::string randomPkm(bool back = false);

/**
 * @brief Obtiene la textura de un Pokémon de la generación 5.
 *
 * @param pokemonPokedexNumber El número en el Pokédex del Pokémon.
 * @param back Indica si se busca la textura posterior del Pokémon.
 *
 * @return La textura del Pokémon especificado.
 */
Texture2D getPokemonTexture(int pokemonPokedexNumber, bool back = false);

/**
 * @brief Guarda un Pokémon en pokedex.dat.
 *
 * @param pkm El Pokémon que se va a guardar.
 */
void saveToFile(const Pkm& pkm);

/**
 * @brief Lee los datos de un Pokémon de pokedex.dat.
 *
 * @param pokedexNumber El número de la Pokédex general del Pokémon a leer.
 * @param pkm La estructura donde se almacenarán los datos del Pokémon.
 * @return true si la lectura fue exitosa, false en caso contrario.
 */
bool readPokemonFromFile(uint16_t pokedexNumber, Pkm& pkm);

/**
 * @brief Guarda datos de Pokémon desde un archivo CSV a pokedex.dat.
 *
 * @return true si la operación fue exitosa, false en caso contrario.
 */
bool savePokemonsToDatFile();

#endif  // UTILS_HPP