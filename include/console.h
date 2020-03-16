#pragma once
#include <string>
#include <vector> 
#include <iostream>

class Console {
public:
    Console* newText();
    Console* addText(std::string text);
    void drawText(bool clearScreen);

    Console* newChoice(std::string choice);
    Console* addChoice(std::string choice);
    int getInput(bool clearScreen);

    static Console* get() {
        if (!singleton) {
            singleton = new Console();
        }
        return singleton;
    }

    static void clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }
    
    std::string choiceText;
    std::vector<std::string> choices;

    std::vector<std::string> menuText;
private:
    Console() {}
    static Console* singleton;
};