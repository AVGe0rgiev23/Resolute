#pragma once
#include "raylib.h"
#include <string>

using namespace std;

extern const int screenWidth;
extern const int screenHeight;

// Function prototypes
void menu();
void InitLoginScreen();
void HandleLoginInput();
void DrawLoginScreen();
bool ValidateLogin(const string& user, const string& pass);
void SaveCredentials(const string& user, const string& pass);
bool CheckIfRegistered();
void RedirectToGameMenu();

// Global variables for login state
extern bool loginSuccess;
extern string username;
extern string password;
extern bool onUsername;
extern bool onPassword;
extern bool isRegistered;
extern bool loginButtonActive;
