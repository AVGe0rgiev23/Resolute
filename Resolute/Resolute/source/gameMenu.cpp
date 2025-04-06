#include "../header/gameMenu.h"
#include "../header/quizChoice.h"  // Include the new header
#include "raylib.h"
#include <iostream>

using namespace std;

// Screen settings
const int screenWidth = 800;
const int screenHeight = 600;

void ShowSettings() {
    // Settings window
    InitWindow(screenWidth, screenHeight, "Settings");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawText("Settings: Adjust volume and change preferences.", 50, 150, 20, WHITE);
        DrawText("Press Backspace to go back to the main menu.", 50, 180, 20, WHITE);

        // Check if Backspace key is pressed
        if (IsKeyPressed(KEY_BACKSPACE)) {
            CloseWindow();  // Close settings window
            return;         // Return to the main menu
        }

        EndDrawing();
    }

    CloseWindow();
}

void ShowHowToPlay() {
    // How to play window
    InitWindow(screenWidth, screenHeight, "How to Play");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawText("How to Play: Answer quiz questions to score points.", 50, 150, 20, WHITE);
        DrawText("Click on the correct option for each question.", 50, 180, 20, WHITE);
        DrawText("Press Backspace to go back to the main menu.", 50, 210, 20, WHITE);

        // Check if Backspace key is pressed
        if (IsKeyPressed(KEY_BACKSPACE)) {
            CloseWindow();  // Close how to play window
            return;         // Return to the main menu
        }

        EndDrawing();
    }

    CloseWindow();
}

void menu() {
    InitWindow(screenWidth, screenHeight, "Game Menu");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw title
        DrawText("MAIN MENU", screenWidth / 2 - 80, 50, 30, WHITE);

        // Draw buttons for Start, Settings, How to Play, and Exit
        DrawRectangle(300, 150, 200, 50, GREEN);
        DrawText("Start Game", 360, 165, 20, WHITE);

        DrawRectangle(300, 220, 200, 50, GRAY);
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
                CloseWindow();                // Close menu
                OpenQuizChoiceScreen();      // Open quiz choice screen
            }

            if (mouseY > 220 && mouseY < 270) {
                cout << "Settings button clicked!" << endl;
                CloseWindow();    // Close menu
                ShowSettings();   // Open settings window
                InitWindow(screenWidth, screenHeight, "Game Menu"); // Reopen main menu window after closing settings
            }

            if (mouseY > 290 && mouseY < 340) {
                cout << "How to Play button clicked!" << endl;
                CloseWindow();    // Close menu
                ShowHowToPlay();  // Open how to play window
                InitWindow(screenWidth, screenHeight, "Game Menu"); // Reopen main menu window after closing how to play
            }

            if (mouseY > 360 && mouseY < 410) {
                CloseWindow();  // Close the window and exit
            }
        }

        // Check if Backspace is pressed to go back to main menu
        if (IsKeyPressed(KEY_BACKSPACE)) {
            // Reinitialize the main menu window
            CloseWindow();  // Close current window
            InitWindow(screenWidth, screenHeight, "Game Menu"); // Open main menu again
        }

        EndDrawing();
    }

    CloseWindow();  // Close the game menu window
}

void RedirectToGameMenu() {
    menu();  // Call the menu function when login is successful
}
