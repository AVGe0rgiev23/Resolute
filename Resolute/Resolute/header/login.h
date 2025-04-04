#pragma once
#include "raylib.h"
#include <string>

using namespace std;

// Screen settings
extern const int screenWidth;
extern const int screenHeight;

// Function prototypes
void InitGame();
void HandleInput();
void SaveCredentials(const string& user, const string& pass);
bool ValidateLogin(const string& user, const string& pass);
bool CheckIfRegistered();
void DrawLoginScreen();
void DrawMainMenu();

// Global variables
extern string username;
extern string password;
extern bool loginSuccess;
extern bool onUsername;
extern bool onPassword;
extern bool isRegistered;
extern bool registrationInProgress;
extern bool loginButtonActive;


