#include "raylib.h"
#include "../header/login.h"
#include <fstream>
#include <iostream>

using namespace std;

// Global variables for login state
const int screenWidth = 800;  // Define the screen size
const int screenHeight = 600;

bool loginSuccess = false;
string username = "";
string password = "";
bool onUsername = true;
bool onPassword = false;
bool isRegistered = CheckIfRegistered();  // This checks if there is any user data
bool loginButtonActive = false;
bool isInLoginMode = true;  // Flag to switch between login and registration


int main() {
    InitLoginScreen();  // Initialize the login screen

    while (!WindowShouldClose()) {
        HandleLoginInput();  // Handle user input (username/password)
        BeginDrawing();
        ClearBackground(BLACK);

        if (loginSuccess) {
            RedirectToGameMenu();  // Redirect to the game menu after successful login
        }
        else {
            DrawLoginScreen();  // Show login/registration screen
        }

        EndDrawing();
    }

    CloseWindow();  // Close the window and exit
}

void InitLoginScreen() {
    InitWindow(screenWidth, screenHeight, "Futuristic Login/Registration Menu");
    SetTargetFPS(60);
}

bool CheckIfRegistered() {
    ifstream file("users.txt");
    return file.good(); // If file exists and is not empty, we assume user is registered
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

// Handle user input for the login screen
void HandleLoginInput() {
    // Handle input for username and password
    if (IsKeyPressed(KEY_ENTER)) {
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

    // Check if the login/register button should be active (both fields must be non-empty)
    loginButtonActive = (!username.empty() && !password.empty());
}

// Draw the login screen
void DrawLoginScreen() {
    // Display different text based on login mode
    if (isInLoginMode) {
        DrawText("LOGIN", screenWidth / 2 - 50, 50, 30, WHITE);
    }
    else {
        DrawText("REGISTER", screenWidth / 2 - 60, 50, 30, WHITE);
    }

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
    DrawText(isInLoginMode ? "LOGIN" : "REGISTER", screenWidth / 2 - 40, 270, 20, WHITE);

    // Button click action
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && loginButtonActive) {
        if (!isInLoginMode && !username.empty() && !password.empty()) {
            // Register the user if not in login mode and fields are filled
            SaveCredentials(username, password);
            isRegistered = true;  // Mark as registered after saving the credentials
            isInLoginMode = true; // Switch back to login mode after registration
        }
        else if (isInLoginMode && ValidateLogin(username, password)) {
            // Validate login and set login success
            loginSuccess = true;  // Successful login, move to main menu
            RedirectToGameMenu();  // Redirect to game menu after successful login
        }
    }

    // Switch between login and registration mode
    if (IsKeyPressed(KEY_TAB)) {
        isInLoginMode = !isInLoginMode;
        username = "";  // Clear input fields when switching
        password = "";
    }
}
