#include "../header/login.h"
#include <iostream>
#include <fstream>

using namespace std;

// Screen settings
const int screenWidth = 800;
const int screenHeight = 600;

// Global variables
string username = "";
string password = "";
bool loginSuccess = false;
bool onUsername = true;
bool onPassword = false;
bool isRegistered = CheckIfRegistered();
bool registrationInProgress = true;
bool loginButtonActive = false;  // Flag to determine if the login button is active

void InitGame() {
    InitWindow(screenWidth, screenHeight, "Futuristic Login/Registration Menu");
    SetTargetFPS(60);
}

bool CheckIfRegistered() {
    ifstream file("users.txt");
    return file.good(); // If file exists, assume user is registered
}

void SaveCredentials(const string& user, const string& pass) {
    ofstream file("users.txt", ios::app);  // Use 'app' mode to append to the file
    file << user << endl << pass << endl;
}

bool ValidateLogin(const string& user, const string& pass) {
    ifstream file("users.txt");
    string storedUser, storedPass;
    while (getline(file, storedUser)) {
        getline(file, storedPass);
        if (user == storedUser && pass == storedPass) {
            return true;
        }
    }
    return false;
}

void HandleInput() {
    // Handle input for username and password
    if (IsKeyPressed(KEY_TAB)) {
        // Switch between username and password field when tab is pressed
        onUsername = !onUsername;
        onPassword = !onPassword;
    }

    if (onUsername) {
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!username.empty()) {
                username.pop_back();
            }
        }
        else {
            for (int key = 32; key <= 125; key++) {
                if (IsKeyPressed((KeyboardKey)key)) {
                    username += (char)key;
                    break;
                }
            }
        }
    }
    else if (onPassword) {
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!password.empty()) {
                password.pop_back();
            }
        }
        else {
            for (int key = 32; key <= 125; key++) {
                if (IsKeyPressed((KeyboardKey)key)) {
                    password += (char)key;
                    break;
                }
            }
        }
    }

    // Check if the login button should be active (both fields must be non-empty)
    loginButtonActive = (!username.empty() && !password.empty());
}

void DrawLoginScreen() {
    DrawText(isRegistered ? "LOGIN" : "REGISTER", screenWidth / 2 - 50, 50, 30, WHITE);

    // Draw input fields
    DrawRectangle(screenWidth / 2 - 100, 150, 200, 40, GRAY);
    DrawRectangle(screenWidth / 2 - 100, 200, 200, 40, GRAY);

    // Highlight the current field
    if (onUsername) {
        DrawRectangleLines(screenWidth / 2 - 100, 150, 200, 40, BLUE);
    }
    if (onPassword) {
        DrawRectangleLines(screenWidth / 2 - 100, 200, 200, 40, BLUE);
    }

    // Draw text inside input fields
    DrawText(username.c_str(), screenWidth / 2 - 90, 160, 20, WHITE);

    // For password, display "*" for each character
    string passwordDisplay(password.length(), '*');
    DrawText(passwordDisplay.c_str(), screenWidth / 2 - 90, 210, 20, WHITE);

    DrawText("USERNAME", screenWidth / 2 - 100, 130, 15, LIGHTGRAY);
    DrawText("PASSWORD", screenWidth / 2 - 100, 180, 15, LIGHTGRAY);

    // Draw the button for login/register
    Color buttonColor = loginButtonActive ? BLUE : DARKGRAY;
    DrawRectangle(screenWidth / 2 - 50, 260, 100, 40, buttonColor);
    DrawText(isRegistered ? "LOGIN" : "REGISTER", screenWidth / 2 - 40, 270, 20, WHITE);

    // Button click action
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && loginButtonActive) {
        if (!isRegistered && !username.empty() && !password.empty()) {
            SaveCredentials(username, password);
            isRegistered = true;  // Mark as registered
            registrationInProgress = false;  // Stay on the registration screen
        }
        else if (isRegistered && ValidateLogin(username, password)) {
            loginSuccess = true;  // Successful login, move to main menu
        }
    }
}

void DrawMainMenu() {
    DrawText("MAIN MENU", screenWidth / 2 - 80, 50, 30, WHITE);

    // Draw buttons for Start, Settings, How to Play, and Exit
    DrawRectangle(screenWidth / 2 - 100, 150, 200, 50, BLUE);
    DrawText("Start Game", screenWidth / 2 - 60, 165, 20, WHITE);

    DrawRectangle(screenWidth / 2 - 100, 220, 200, 50, BLUE);
    DrawText("Settings", screenWidth / 2 - 50, 235, 20, WHITE);

    DrawRectangle(screenWidth / 2 - 100, 290, 200, 50, BLUE);
    DrawText("How to Play", screenWidth / 2 - 50, 305, 20, WHITE);

    DrawRectangle(screenWidth / 2 - 100, 360, 200, 50, RED);
    DrawText("Exit", screenWidth / 2 - 20, 375, 20, WHITE);

    // Handle button clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseY = GetMouseY();

        // Check if Start Game button is clicked
        if (mouseY > 150 && mouseY < 200) {
            // Implement start game logic here
            std::cout << "Start Game button clicked!" << std::endl;
        }

        // Check if Settings button is clicked
        if (mouseY > 220 && mouseY < 270) {
            // Implement settings logic here
            std::cout << "Settings button clicked!" << std::endl;
        }

        // Check if How to Play button is clicked
        if (mouseY > 290 && mouseY < 340) {
            // Implement how to play logic here
            std::cout << "How to Play button clicked!" << std::endl;
        }

        // Check if Exit button is clicked
        if (mouseY > 360 && mouseY < 410) {
            CloseWindow(); // Close the window and exit
        }
    }
}

int main() {
    InitGame();  // Initialize the game
    while (!WindowShouldClose()) {
        HandleInput();  // Handle input (user interactions)

        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (!loginSuccess) {
            DrawLoginScreen();  // Show login or registration screen
        }
        else {
            DrawMainMenu();  // Show main menu after successful login
        }

        EndDrawing();
    }

    CloseWindow(); // Close the window and exit
    return 0;
}
