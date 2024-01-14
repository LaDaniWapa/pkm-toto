#include "screenManager.hpp"
#include <raylib.h>

class TitleScreen : public Screen {
    private:
    Texture2D background;

    public:
    void Load() override {
        background = LoadTexture("assets/title.png");
    }

    void Unload() override {
        UnloadTexture(background);
    }

    void Update() override {
        if (IsKeyPressed(KEY_ENTER)) {
            screenManager->ChangeScreen("Battle");
        }
    }

    void Draw() override {
        DrawTexture(background, 0, 0, WHITE);
    }
};