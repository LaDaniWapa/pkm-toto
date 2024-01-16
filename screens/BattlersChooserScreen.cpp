#include "BattlersChooserScreen.hpp"

void BattlersChooserScreen::Load() {
    // Cargar fuente necesarioa
    font = LoadFontEx("assets/fonts/pokemon-b-w.ttf", 60, 0, 0);

    // Cargar shader
    outlineShader = LoadShader(0, "assets/shaders/outline.fs");

    // Get shader variables locations
    int outlineSizeLoc = GetShaderLocation(outlineShader, "outlineSize");
    int outlineColorLoc = GetShaderLocation(outlineShader, "outlineColor");
    int textureSizeLoc = GetShaderLocation(outlineShader, "textureSize");

    // Set shaders variables
    float outlineSize = 2.f;
    float outlineColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float textureSize[2] = {192.f, 192.f};

    // Send shader variables values
    SetShaderValue(outlineShader, outlineSizeLoc, &outlineSize, SHADER_UNIFORM_FLOAT);
    SetShaderValue(outlineShader, outlineColorLoc, &outlineColor, SHADER_UNIFORM_VEC4);
    SetShaderValue(outlineShader, textureSizeLoc, &textureSize, SHADER_ATTRIB_VEC2);

    // Cargar texturas de pokemons y tipos
    typesTexture = LoadTexture("assets/types.png");
    pokemonTexture = getPokemonTexture(pkxn, false, false);
    pokemonFoeTexture = getPokemonTexture(pkxnF, false, false);
    // Cargar datos de los pokemons generados aleatoriamente
    readPokemonFromFile(pkxn, pokemon);
    readPokemonFromFile(pkxnF, pokemonFoe);
}

void BattlersChooserScreen::Unload() {
    UnloadTexture(pokemonTexture);
    UnloadTexture(pokemonFoeTexture);
    UnloadTexture(typesTexture);
    UnloadFont(font);
}

void BattlersChooserScreen::Update() {
    // Actualizar la posicion del raton
    mousePoint = GetMousePosition();
    // Actualizar los shaders
    pokemonShader = false;
    pokemonFoeShader = false;

    // La funcion usa la resolucion final de la pantalla (x2)
    if (CheckCollisionPointCircle(mousePoint, Vector2{256, 282}, 192)) {
        pokemonShader = true;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            BattlersListScreen* battlersListscreen =
                dynamic_cast<BattlersListScreen*>(screenManager->getScreen("BattlersList"));

            if (battlersListscreen) {
                battlersListscreen->setOldPokedexNumber(pokemonFoe.ID);
                battlersListscreen->setIsFoe(false);
                screenManager->ChangeScreen("BattlersList");
            }
        }
    }

    // La funcion usa la resolucion final de la pantalla (x2)
    if (CheckCollisionPointCircle(mousePoint, Vector2{768, 282}, 192)) {
        pokemonFoeShader = true;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            BattlersListScreen* battlersListscreen =
                dynamic_cast<BattlersListScreen*>(screenManager->getScreen("BattlersList"));

            if (battlersListscreen) {
                battlersListscreen->setOldPokedexNumber(pokemon.ID);
                battlersListscreen->setIsFoe(true);
                screenManager->ChangeScreen("BattlersList");
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        BattleScreen* battleScreen = dynamic_cast<BattleScreen*>(screenManager->getScreen("Battle"));
        if (battleScreen) {
            battleScreen->setPokemonPokedexNumber(pokemon.ID);
            battleScreen->setPokemonFoePokedexNumber(pokemonFoe.ID);
            screenManager->ChangeScreen("Battle");
        }
    }
}

void BattlersChooserScreen::Draw() {
    // Imprimir los nombres de los pokemons
    DrawText(pokemon.name, 128 - (MeasureText(pokemon.name, 20) / 2), 15, 20, RED);
    DrawText(pokemonFoe.name, 385 - (MeasureText(pokemonFoe.name, 20) / 2), 15, 20, RED);

    // Dibujar background de los pokemons
    DrawCircleGradient(128, 141, 96, GRAY, DARKGRAY);
    DrawCircleGradient(384, 141, 96, GRAY, DARKGRAY);

    // Dibujar pokemon con o sin outlineShader
    if (pokemonShader) {
        BeginShaderMode(outlineShader);
        DrawTexture(pokemonTexture, 32, 45, WHITE);
        EndShaderMode();
    } else
        DrawTexture(pokemonTexture, 32, 45, WHITE);

    if (pokemonFoeShader) {
        BeginShaderMode(outlineShader);
        DrawTexture(pokemonFoeTexture, 288, 45, WHITE);
        EndShaderMode();
    } else
        DrawTexture(pokemonFoeTexture, 288, 45, WHITE);

    // Boton para empezar
    DrawRectangle(161, 309, 200, 50, GRAY);
    DrawText("START BATTLE", 178, 325, 20, RED);
}

void BattlersChooserScreen::setPokemon(int pokedexnumber) {
    pkxn = pokedexnumber;
}

void BattlersChooserScreen::setFoePokemon(int pokedexnumber) {
    pkxnF = pokedexnumber;
}