#include <raylib.h>

#include "battler.hpp"
#include "screenManager.hpp"

class BattleScreen : public Screen {
   private:
    Texture2D background;  // 512x288
    Texture2D message;     // 512x96
    Battler* pokemon;
    Battler* pokemonFoe;
    Font font;
    Font fontB;

   public:
    void Load() override {
        font = LoadFontEx("assets/fonts/pokemon-b-w.ttf", 60, 0, 0);
        fontB = LoadFontEx("assets/fonts/pkmndpb.ttf", 30, 0, 0);

        background = LoadTexture("assets/BattleBacks/field_bg.png");
        message = LoadTexture("assets/BattleBacks/field_message.png");

        pokemon = new Battler(494 + 69, 100, true, false, font, fontB);
        pokemonFoe = new Battler(494 + 69, 100, true, true, font, fontB);
    }

    void Unload() override {
        UnloadTexture(background);
    }

    void Update() override {
        if (IsKeyPressed(KEY_ENTER)) {
            screenManager->ChangeScreen("Title");
        }
    }

    void Draw() override {
        DrawTexture(background, 0, 0, WHITE);
        pokemon->draw();
        pokemonFoe->draw();
        DrawTexture(message, 0, 288, WHITE);
    }
};