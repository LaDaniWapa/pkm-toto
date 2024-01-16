#include "TitleScreen.hpp"

void TitleScreen::Load() {
    background = LoadTexture("assets/title.png");
}

void TitleScreen::Unload() {
    UnloadTexture(background);
}

void TitleScreen::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        BattlersChooserScreen *battlerChooserScreen =
            dynamic_cast<BattlersChooserScreen *>(screenManager->getScreen("BattlersChooser"));

        if (battlerChooserScreen) {
            // Generar pokemons random
            battlerChooserScreen->setPokemon(rand() % 155 + 494);
            battlerChooserScreen->setFoePokemon(rand() % 155 + 494);
            screenManager->ChangeScreen("BattlersChooser");
        }
    }
}

void TitleScreen::Draw() {
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITE);
}