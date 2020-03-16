#include "console.h"

Console* Console::singleton = nullptr;

Console* Console::newChoice(std::string text) {
    this->choices.clear();
    this->choiceText = text;
    return this;
}

Console* Console::addChoice(std::string choice) {
    this->choices.push_back(choice);
    return this;
}

int Console::getInput(bool clearScreen) {
    int input = -1;
    while (input < 0 || input >= this->choices.size()) {
        if (clearScreen) {
            Console::clearScreen();
        }

        std::cout << this->choiceText << std::endl;

        for (unsigned int i = 0; i < this->choices.size(); i++) {
            std::cout << i << ") " << this->choices.at(i) << std::endl;
        }
        std::cin >> input;
    }
    return input;
}

Console* Console::newText() {
    this->menuText.clear();
    return this;
}

Console* Console::addText(std::string text) {
    this->menuText.push_back(text);
    return this;
}

void Console::drawText(bool clearScreen) {
    if (clearScreen) {
        Console::clearScreen();
    }

    for (unsigned int i = 0; i < this->menuText.size(); i++) {
        std::cout << this->menuText.at(i) << std::endl;
    }
    std::cin.clear();
    fflush(stdin);
    getchar();
}