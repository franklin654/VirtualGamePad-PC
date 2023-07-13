#include "gamepadinjector.hpp"
#include <QtCore>

GamepadInjector::GamepadInjector() : injector(InputInjector::TryCreate())
{
	if (injector == NULL)
	{
		qDebug() << "Unable to create Input Injection.";
		exit(1);
	}
	qDebug() << "Address of Injector:" << &injector;
	isConnected = false;
}

void GamepadInjector::connectGamepad()
{
	if (!isConnected)
	{
		try
		{
			injector.InitializeGamepadInjection();
			isConnected = true;
		}
		catch (std::exception e)
		{
			qDebug() << e.what();
		}
	}
}

void GamepadInjector::disconnectGamepad()
{
	if (isConnected)
	{
		try
		{
			injector.UninitializeGamepadInjection();
			isConnected = false;
		}
		catch (std::exception e)
		{
			qDebug() << e.what();
		}
	}
}

void GamepadInjector::Update(InjectedInputGamepadInfo state)
{
	gamepadState = state;
}

void GamepadInjector::PressButton(GamepadButtons button)
{
	gamepadState.Buttons(gamepadState.Buttons() | button);
}

void GamepadInjector::ReleaseButton(GamepadButtons button)
{
	gamepadState.Buttons(gamepadState.Buttons() & ~button);
}

void GamepadInjector::inject()
{
	if (isConnected)
	{
		injector.InjectGamepadInput(gamepadState);
	}
}

GamepadInjector::~GamepadInjector()
{
	disconnectGamepad();
}
