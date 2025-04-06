#include "../header/quizScreen.h"
#include "../header/quizChoice.h"
#include "raylib.h"
#include <iostream>
#include <string.h>

using namespace std;

// Question structure
struct Question {
    const char* question;
    const char* options[3];
    int correctIndex;
};

// C++ quiz questions
Question cppQuestions[] = {
    {"What is a pointer?", {"A variable", "A memory address", "A function"}, 1},
    {"What does 'new' do?", {"Deletes memory", "Allocates memory", "Compiles code"}, 1},
    {"Which of the following is a valid pointer declaration?", {"int* p;", "pointer int p;", "int p*;"}, 0},
    {"What does the 'delete' operator do?", {"Deallocates memory", "Allocates memory", "Creates a pointer"}, 0},
    {"What is the size of an 'int' in C++?", {"4 bytes", "8 bytes", "2 bytes"}, 0},
    {"Which of these is a function pointer?", {"void(*func)()", "void func()", "func* void"}, 0},
    {"Which operator is used for dereferencing a pointer?", {"*", "&", "->"}, 0},
    {"What is a reference in C++?", {"An alias for a variable", "A pointer", "A function"}, 0},
    {"What is a constructor in C++?", {"A method that initializes objects", "A function to delete objects", "A variable declaration"}, 0},
    {"Which C++ feature supports object-oriented programming?", {"Classes and objects", "Functions", "Pointers"}, 0},
    {"Which of the following is a feature of C++?", {"Multiple inheritance", "Dynamic typing", "Garbage collection"}, 0}
};

// Python quiz questions
Question pythonQuestions[] = {
    {"What is a list?", {"An array", "An object", "A sequence"}, 2},
    {"How to define a function?", {"def", "func", "lambda"}, 0},
    {"Which of these is a mutable type in Python?", {"list", "string", "tuple"}, 0},
    {"How do you declare a variable in Python?", {"var x = 10", "x = 10", "int x = 10"}, 1},
    {"What is the output of 'print(2 ** 3)'?", {"5", "6", "8"}, 2},
    {"Which of the following is used for string formatting?", {"f-strings", "format()", "Both"}, 2},
    {"What is a tuple?", {"A list", "An immutable list", "A dictionary"}, 1},
    {"How do you handle exceptions in Python?", {"try...except", "catch...throw", "error...handle"}, 0},
    {"What is the result of '5 // 2'?", {"2", "2.5", "3"}, 0},
    {"Which method is used to add an item to the end of a list?", {"append()", "add()", "insert()"}, 0},
    {"What is the purpose of the 'self' keyword?", {"Refers to the instance of the class", "Defines a function", "None of the above"}, 0}
};

// JavaScript quiz questions
Question jsQuestions[] = {
    {"What is 'var' used for?", {"Variable declaration", "Function", "Loop"}, 0},
    {"Which is a JS framework?", {"React", "Laravel", "Flask"}, 0},
    {"What is 'let' used for?", {"Variable declaration", "Creating a constant", "None"}, 0},
    {"What does 'console.log()' do?", {"Prints to the console", "Declares a variable", "Loops over an array"}, 0},
    {"What is a promise in JavaScript?", {"A function that returns a value", "An object representing the eventual completion or failure of an asynchronous operation", "None of the above"}, 1},
    {"Which of the following is used to create a new object in JavaScript?", {"new Object()", "create Object()", "new Array()"}, 0},
    {"Which of these is a data structure in JavaScript?", {"Array", "Tuple", "Stack"}, 0},
    {"Which method is used to convert a string into a number?", {"parseInt()", "toNumber()", "parseFloat()"}, 0},
    {"What does '=== ' mean in JavaScript?", {"Strict equality", "Equality", "Assignment"}, 0},
    {"Which of the following is a JavaScript object method?", {"toString()", "toFixed()", "Both"}, 2},
    {"What is an arrow function in JavaScript?", {"A shorthand for defining functions", "A type of object", "A new data structure"}, 0}
};

// Get questions based on quiz type
Question* GetQuestions(QuizType type, int& totalQuestions) {
    if (type == CPLUSPLUS) {
        totalQuestions = 12;
        return cppQuestions;
    }
    else if (type == PYTHON) {
        totalQuestions = 12;
        return pythonQuestions;
    }
    else {
        totalQuestions = 12;
        return jsQuestions;
    }
}

void StartQuiz(QuizType type) {
    InitWindow(800, 600, "Quiz Time");
    SetTargetFPS(60);

    int totalQuestions;
    Question* questions = GetQuestions(type, totalQuestions);

    int current = 0;
    int score = 0;
    bool showResult = false;
    bool answered = false;
    int selectedOption = -1;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Back button
        DrawRectangle(20, 530, 100, 40, RED);
        DrawText("Back", 45, 540, 20, WHITE);

        // Back button click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            if (mouse.x >= 20 && mouse.x <= 120 && mouse.y >= 530 && mouse.y <= 570) {
                CloseWindow();
                OpenQuizChoiceScreen();
                return;
            }
        }

        if (showResult) {
            DrawText("Quiz Complete!", 280, 200, 30, WHITE);
            DrawText(TextFormat("Score: %d / %d", score, totalQuestions), 300, 250, 25, GREEN);
        }
        else {
            Question q = questions[current];

            DrawText(q.question, 50, 50, 25, RAYWHITE);

            // Show 3 options
            for (int i = 0; i < 3; i++) {
                int y = 150 + i * 60;
                Color color = BLUE;

                DrawRectangle(100, y, 600, 40, color);
                DrawText(q.options[i], 120, y + 10, 20, WHITE);

                // Option click
                if (!answered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse = GetMousePosition();
                    if (mouse.x >= 100 && mouse.x <= 700 && mouse.y >= y && mouse.y <= y + 40) {
                        answered = true;
                        selectedOption = i;
                        if (i == q.correctIndex) score++;
                    }
                }
            }

            // After answering, automatically go to next question
            if (answered) {
                answered = false;
                selectedOption = -1;
                current++;
                if (current >= totalQuestions) {
                    showResult = true;
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
