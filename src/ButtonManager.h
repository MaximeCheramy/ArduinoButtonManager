#pragma once

#include "Arduino.h"

typedef void (*Handler)(bool down, int id);

struct Button
{
    int id;
    int low;
    int high;
    Handler handler;
};

class ButtonManager
{

public:
    ButtonManager(uint8_t port) : _port(port)
    {
    }

    void begin()
    {
        pinMode(_port, INPUT);
    }

    void loop()
    {
        static unsigned long lastDebounceTime = 0;
        static Button *lastSwitch = NULL;
        unsigned int debounceDelay = 50;
        Button *pressedSwitch = readState();

        // Reset the lastDebounceTime if the reading is not stable yet
        if (lastSwitch != pressedSwitch)
        {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay)
        {
            if (_currentSwitch != pressedSwitch)
            {
                if (_currentSwitch != NULL)
                {
                    _currentSwitch->handler(false, _currentSwitch->id);
                }
                if (pressedSwitch != NULL)
                {
                    pressedSwitch->handler(true, pressedSwitch->id);
                }
                _currentSwitch = pressedSwitch;
            }
        }

        lastSwitch = pressedSwitch;
    }

    int addButton(int low, int high, Handler handler)
    {
        Button button;
        button.id = _buttonCount;
        button.handler = handler;
        button.low = low;
        button.high = high;
        _buttons[_buttonCount++] = button;

        return button.id;
    }

private:
    Button *_currentSwitch = NULL;
    int _port;
    Button _buttons[10];
    int _buttonCount = 0;

    Button *readState()
    {
        int v = analogRead(_port);

        if (v <= 35)
        {
            return NULL;
        }

        for (int i = 0; i < _buttonCount; i++)
        {
            Button *button = &_buttons[i];
            if (v >= button->low && v <= button->high)
            {
                return button;
            }
        }

        return NULL;
    }
};
