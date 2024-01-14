
#include "battler.hpp"
#include "screens.h"
#include "type.hpp"
#include "utils.hpp"

void init() {
    // Randomize
    srand(time(0));

    // Quitar el INFO
    SetTraceLogLevel(LOG_ERROR);

    // Tamaño pantalla nintendo ds x2(images) x2(virtual screen)
    InitWindow(512 * 2, 384 * 2, "Pokemon ToTo");

    // Poner icono a la ventana
    Image icon = LoadImage("assets/icon.png");
    SetWindowIcon(icon);

    // Ajustar a 60 FPS
    SetTargetFPS(60);
}

int main() {
    init();

    Camera2D worldSpaceCamera = {0};  // Game world camera
    worldSpaceCamera.zoom = 1.0f;

    Camera2D screenSpaceCamera = {0};  // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    RenderTexture2D target = LoadRenderTexture(512, 384);  // This is where we'll draw all our objects.

    // The target's height is flipped (in the source Rectangle), due to OpenGL reasons
    Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height};
    Rectangle destRec = {-2, -2, 512 * 2 + (2 * 2), 384 * 2 + (2 * 2)};

    Vector2 origin = {0.0f, 0.0f};

    // Screens
    ScreenManager screenManager;

    TitleScreen titleScreen;
    titleScreen.SetScreenManager(&screenManager);
    screenManager.AddScreen("Title", &titleScreen);

    BattleScreen battleScreen;
    battleScreen.SetScreenManager(&screenManager);
    screenManager.AddScreen("Battle", &battleScreen);

    screenManager.ChangeScreen("Title");

    // Texture2D background = LoadTexture("assets/BattleBacks/field_bg.png");    // 512x288
    // Texture2D message = LoadTexture("assets/BattleBacks/field_message.png");  // 512x96

    // Font font = LoadFontEx("assets/fonts/pokemon-b-w.ttf", 60, 0, 0);
    // Font fontB = LoadFontEx("assets/fonts/pkmndpb.ttf", 30, 0, 0);

    // Pokemon* pokemon = new Pokemon(494 + 100, 100, true, false, font, fontB);
    // Pokemon* pokemonfoe = new Pokemon(494 + 34, 100, false, true, font, fontB);

    while (!WindowShouldClose()) {
        // Round worldSpace coordinates, keep decimals into screenSpace coordinates
        // ------------------------------------------------------------------------
        worldSpaceCamera.target.x = (int)screenSpaceCamera.target.x;
        screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
        screenSpaceCamera.target.x *= 2;

        worldSpaceCamera.target.y = (int)screenSpaceCamera.target.y;
        screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
        screenSpaceCamera.target.y *= 2;
        // -------------------------------------------------------------------------

        // Draw into target (world space)
        BeginTextureMode(target);

        BeginMode2D(worldSpaceCamera);

        ClearBackground(BLACK);
        screenManager.Update();
        screenManager.Draw();

        // DrawTexture(background, 0, 0, WHITE);
        // pokemonfoe->draw();
        // pokemon->draw();
        // DrawTexture(message, 0, 288, WHITE);
        EndMode2D();

        EndTextureMode();

        // Draw target into screen (screen space)
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(screenSpaceCamera);
        DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}