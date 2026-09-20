#include "buttons.h"

Button* buttonK1;
Button* buttonK2;
Button* buttonK3;
Button* buttonK4;
ButtonController buttonManager;

Button::Button(uint8_t b_pin, int b_input_type) : pin(b_pin), inputType(b_input_type)
{
    pinMode(pin, inputType);
}

Button::Button() {}

bool Button::isDown() const{
    return down;
}

void Button::buttonDown()
{

    if (downFunction) downFunction();
}

void Button::buttonPressed()
{
    if (pressedFunction) pressedFunction();
}
void Button::buttonReleased()
{
    if (releasedFunction) releasedFunction();
}

ButtonController::ButtonController() {};

Button *ButtonController::createButton(uint8_t b_pin, int b_input_type)
{
    Button *b = new Button(b_pin, b_input_type);
    buttons[buttonCount++] = b;
    return b;
};

void ButtonController::updateButtons()
{
    if(!buttonsEnabled) return;
    
    for (int i = 0; i < buttonCount; i++)
    {
        Button *b = buttons[i];
        b->down = digitalRead(b->pin) ^ 1;

        if (b->last_down && !b->down)
        {
            b->buttonReleased();
        }
        else if (!b->last_down && b->down)
        {
            b->buttonPressed();
        }
        b->last_down = b->down;
    }
}
Button *ButtonController::getButton(u_int8_t pin)
{
    for (int i = 0; i < buttonCount; i++)
    {
        if (buttons[i]->pin == pin)
        {
            return buttons[i]; // return the real pointer, not a local's address
        }
    }
    return nullptr; // handle not-found
}

void setupButtons()
{
    buttonK1 = buttonManager.createButton(K1_PIN, INPUT_PULLUP);
    buttonK2 = buttonManager.createButton(K2_PIN, INPUT_PULLUP);
    buttonK3 = buttonManager.createButton(K3_PIN, INPUT_PULLUP);
    buttonK4 = buttonManager.createButton(K4_PIN, INPUT_PULLUP);

    Serial.println("Setup All Buttons");
}