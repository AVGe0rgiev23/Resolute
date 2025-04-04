#include "../header/gameMenu.h"
#include "raylib.h"
#include <iostream>

using namespace std;

// Screen settings
const int screenWidth = 800;
const int screenHeight = 600;

void menu() {
    InitWindow(screenWidth, screenHeight, "Game Menu");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Draw title
        DrawText("MAIN MENU", screenWidth / 2 - 80, 50, 30, WHITE);

        // Draw buttons for Start, Settings, How to Play, and Exit
        DrawRectangle(300, 150, 200, 50, BLUE);
        DrawText("Start Game", 360, 165, 20, WHITE);

        DrawRectangle(300, 220, 200, 50, BLUE);
        DrawText("Settings", 370, 235, 20, WHITE);

        DrawRectangle(300, 290, 200, 50, BLUE);
        DrawText("How to Play", 355, 305, 20, WHITE);

        DrawRectangle(300, 360, 200, 50, RED);
        DrawText("Exit", 370, 375, 20, WHITE);

        // Handle button clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseY = GetMouseY();

            if (mouseY > 150 && mouseY < 200) {
                cout << "Start Game button clicked!" << endl;
            }

            if (mouseY > 220 && mouseY < 270) {
                cout << "Settings button clicked!" << endl;
            }

            if (mouseY > 290 && mouseY < 340) {
                cout << "How to Play button clicked!" << endl;
            }

            if (mouseY > 360 && mouseY < 410) {
                CloseWindow();  // Close the window and exit
            }
        }

        EndDrawing();
    }

    CloseWindow();  // Close the game menu window
}

void RedirectToGameMenu() {
    menu();  // Call the menu function when login is successful
}
