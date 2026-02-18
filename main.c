#include "raylib.h"
#include "model.h"
#include "mnist_io.h"
#include <string.h>

void run_gui(const char* model_path) {
    Model m;
    model_load(model_path, &m);

    const int screenWidth = 560; // 28 * 20
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Gemini MNIST - Draw a Digit");

    float canvas[784] = { 0 }; // Our 28x28 drawing surface
    float p[OUT] = { 0 };      // Probabilities
    int prediction = -1;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // --- 1. INPUT: Draw with Mouse ---
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mPos = GetMousePosition();
            int x = mPos.x / 20; 
            int y = mPos.y / 20;
            // Draw a "thick" line (3x3 pixels) for better recognition
            for(int dy = -1; dy <= 1; dy++) {
                for(int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < 28 && ny >= 0 && ny < 28) canvas[ny * 28 + nx] = 1.0f;
                }
            }
        }
        if (IsKeyPressed(KEY_C)) {
            memset(canvas, 0, sizeof(canvas));
            prediction = -1;
        }

        // --- 2. INFERENCE: Predict ---
        float z1[H], a1[H], z2[OUT];
        forward(&m, canvas, z1, a1, z2, p);
        prediction = argmax(p, OUT);

        // --- 3. RENDER ---
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // Draw Grid
            for (int i = 0; i < 784; i++) {
                if (canvas[i] > 0.1f) 
                    DrawRectangle((i % 28) * 20, (i / 28) * 20, 20, 20, BLACK);
            }
            // Draw Results
            DrawRectangle(0, 560, screenWidth, 90, DARKGRAY);
            DrawText(TextFormat("PREDICTION: %d", prediction), 20, 580, 40, YELLOW);
            DrawText("Press 'C' to Clear", 380, 610, 15, WHITE);
        EndDrawing();
    }
    CloseWindow();
}