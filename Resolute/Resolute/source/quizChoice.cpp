// quizChoice.cpp
#include "../header/quizChoice.h"
#include "../header/quizScreen.h"
#include "raylib.h"
#include <iostream>

using namespace std;

void OpenQuizChoiceScreen() {
    InitWindow(800, 600, "Choose a Quiz");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("CHOOSE A QUIZ", 270, 50, 30, RAYWHITE);

        DrawRectangle(300, 150, 200, 50, DARKBLUE);
        DrawText("C++ Quiz", 355, 165, 20, WHITE);

        DrawRectangle(300, 230, 200, 50, DARKGREEN);
        DrawText("Python Quiz", 340, 245, 20, WHITE);

        DrawRectangle(300, 310, 200, 50, DARKPURPLE);
        DrawText("JavaScript Quiz", 325, 325, 20, WHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseY = GetMouseY();

            if (mouseY > 150 && mouseY < 200) {
                cout << "C++ Quiz selected!" << endl;
                CloseWindow();
                StartQuiz(CPLUSPLUS);
            }

            if (mouseY > 230 && mouseY < 280) {
                cout << "Python Quiz selected!" << endl;
                CloseWindow();
                StartQuiz(PYTHON);
            }

            if (mouseY > 310 && mouseY < 360) {
                cout << "JavaScript Quiz selected!" << endl;
                CloseWindow();
                StartQuiz(JAVASCRIPT);
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
