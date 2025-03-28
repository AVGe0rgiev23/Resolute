#pragma once
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
extern string username;
extern string password;
extern bool loginSuccess;
extern bool isRegistered;
