#pragma once
#include "Global.h"

class Button;
extern Button* buttonK1;
extern Button* buttonK2;
extern Button* buttonK3;
extern Button* buttonK4;

class ButtonController;

extern ButtonController buttonManager;

class Button
{
private:
    bool last_down = false;
    bool down = false;
    uint8_t pin;
    int inputType;
    friend class ButtonController;

public:
    void (*pressedFunction)() = nullptr;
    void (*releasedFunction)() = nullptr;
    void (*downFunction)() = nullptr;
    Button(uint8_t b_pin, int b_input_type);
    Button();
    bool isDown() const;
    void buttonDown();
    void buttonPressed();
    void buttonReleased();
};

class ButtonController
{
private:
    Button *buttons[4];
    int buttonCount = 0;

public:
    ButtonController();
    Button *createButton(uint8_t b_pin, int b_input_type);
    Button *getButton(uint8_t b_pin);
    bool buttonsEnabled = false;
    void updateButtons();
};