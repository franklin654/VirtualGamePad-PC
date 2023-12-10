#pragma once
#ifndef SETTINGS_KEY_VARIABLES_H
#define SETTINGS_KEY_VARIABLES_H
#include <windows.h>
#include <QList>

#include <map>
#include "../VGP_Data_Exchange/C/GameButtons.h"

struct TRIAL{
	WORD vk;
	uint is_mouse_key = 0;
};

extern int mouse_sensivity;
extern int port;
extern std::map<GamepadButtons, TRIAL> GAMEPAD_BUTTONS;

enum Thumbstick
{
    LeftThumbstickUp,
    LeftThumbstickDown,
    LeftThumbstickLeft,
    LeftThumbstickRight,
    RightThumbstickUp,
    RightThumbstickDown,
    RightThumbstickLeft,
    RightThumbstickRight
};

extern std::map<Thumbstick, WORD> THUMBSTICK_KEYS;
extern std::map<UINT, const char*> vk_maps;

extern const QList<UINT> MOUSE_BUTTONS;

#endif // SETTINGS_KEY_VARIABLES_H
