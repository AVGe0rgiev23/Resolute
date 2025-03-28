#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Screen settings
const int screenWidth = 800;
const int screenHeight = 600;

// Function prototypes
void DrawLoginScreen();
void DrawMainMenu();
bool CheckIfRegistered();
void SaveCredentials(const string& user, const string& pass);
bool ValidateLogin(const string& user, const string& pass);

// Global variables
string username = "";
string password = "";
bool loginSuccess = false;
bool onUsername = true;
bool onPassword = false;
bool isRegistered = CheckIfRegistered();

int main() {
    InitWindow(screenWidth, screenHeight, "Futuristic Login/Registration Menu");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (!loginSuccess) {
            DrawLoginScreen();
        }
        else {
            DrawMainMenu();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

bool CheckIfRegistered() {
    ifstream file("users.txt");
    return file.good(); // If file exists, assume user is registered
}

void SaveCredentials(const string& user, const string& pass) {
    ofstream file("users.txt");
    file << user << endl << pass << endl;
    file.close();
}

bool ValidateLogin(const string& user, const string& pass) {
    ifstream file("users.txt");
    string storedUser, storedPass;
    getline(file, storedUser);
    getline(file, storedPass);
    file.close();
    return (user == storedUser && pass == storedPass);
}

void DrawLoginScreen() {
    DrawText(isRegistered ? "LOGIN" : "REGISTER", screenWidth / 2 - 50, 50, 30, WHITE);
    DrawRectangle(screenWidth / 2 - 100, 150, 200, 40, GRAY);
    DrawRectangle(screenWidth / 2 - 100, 200, 200, 40, GRAY);
    DrawText(username.c_str(), screenWidth / 2 - 90, 160, 20, WHITE);
    DrawText(password.c_str(), screenWidth / 2 - 90, 210, 20, WHITE);

    DrawText("USERNAME", screenWidth / 2 - 100, 130, 15, LIGHTGRAY);
    DrawText("PASSWORD", screenWidth / 2 - 100, 180, 15, LIGHTGRAY);

    DrawRectangle(screenWidth / 2 - 50, 260, 100, 40, BLUE);
    DrawText(isRegistered ? "LOGIN" : "REGISTER", screenWidth / 2 - 40, 270, 20, WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (!isRegistered) {
            SaveCredentials(username, password);
            isRegistered = true;
        }
        else if (ValidateLogin(username, password)) {
            loginSuccess = true;
        }
    }
}

void DrawMainMenu() {
    DrawText("MAIN MENU", screenWidth / 2 - 80, 50, 30, WHITE);
    DrawRectangle(screenWidth / 2 - 100, 150, 200, 50, BLUE);
    DrawText("Start Game", screenWidth / 2 - 60, 165, 20, WHITE);
    DrawRectangle(screenWidth / 2 - 100, 220, 200, 50, BLUE);
    DrawText("Settings", screenWidth / 2 - 50, 235, 20, WHITE);
    DrawRectangle(screenWidth / 2 - 100, 290, 200, 50, RED);
    DrawText("Exit", screenWidth / 2 - 20, 305, 20, WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && GetMouseY() > 150 && GetMouseY() < 200) {
        if (!isRegistered) {
            loginSuccess = false; // Force login/registration before starting
        }
    }
}