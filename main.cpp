
#include "pokemon.hpp"
#include "type.hpp"
#include "utils.hpp"

int main() {
    // Randomize
    srand(time(0));

    // Quitar el INFO
    SetTraceLogLevel(LOG_ERROR);

    // Tamaño pantalla nintendo ds x2
    InitWindow(512 * 2, 384 * 2, "Pokemon peste");

    Camera2D worldSpaceCamera = {0};  // Game world camera
    worldSpaceCamera.zoom = 1.0f;

    Camera2D screenSpaceCamera = {0};  // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    RenderTexture2D target = LoadRenderTexture(512, 384);  // This is where we'll draw all our objects.

    // The target's height is flipped (in the source Rectangle), due to OpenGL reasons
    Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height};
    Rectangle destRec = {-2, -2, 512 * 2 + (2 * 2), 384 * 2 + (2 * 2)};

    Vector2 origin = {0.0f, 0.0f};

    SetTargetFPS(60);

    // Poner icono a la ventana
    Image icon = LoadImage("assets/icon.png");
    SetWindowIcon(icon);

    Texture2D background = LoadTexture("assets/BattleBacks/field_bg.png");    // 512x288
    Texture2D message = LoadTexture("assets/BattleBacks/field_message.png");  // 512x96

    Font font = LoadFontEx("assets/fonts/pokemon-b-w.ttf", 60, 0 ,0);
    Font fontB = LoadFontEx("assets/fonts/pkmndpb.ttf", 30, 0, 0);

    Pokemon* pokemon = new Pokemon(494 + 9, 100, false, font, fontB);
    Pokemon* pokemonfoe = new Pokemon(497, 100, true, font, fontB);

    Texture2D type = LoadTexture("assets/types.png");

    while (!WindowShouldClose()) {
        // Round worldSpace coordinates, keep decimals into screenSpace coordinates
        worldSpaceCamera.target.x = (int)screenSpaceCamera.target.x;
        screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
        screenSpaceCamera.target.x *= 2;

        worldSpaceCamera.target.y = (int)screenSpaceCamera.target.y;
        screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
        screenSpaceCamera.target.y *= 2;

        BeginTextureMode(target);
        BeginMode2D(worldSpaceCamera);
        DrawTexture(background, 0, 0, WHITE);
        pokemonfoe->draw();
        pokemon->draw();
        DrawTexture(message, 0, 288, WHITE);

        DrawTextureRec(type, Rectangle{0,0,64,28}, Vector2{10, 298}, WHITE);

        EndMode2D();

        EndTextureMode();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(screenSpaceCamera);
        DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}