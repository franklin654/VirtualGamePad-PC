#ifndef GAMEPADINJECTOR_HPP
#define GAMEPADINJECTOR_HPP

// Exclude rarely-used stuff from Windows headers. Required for WinSoc2 to work.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.UI.Input.Preview.Injection.h>

using namespace winrt;
using namespace Windows::Gaming::Input;
using namespace Windows::UI::Input::Preview::Injection;

class GamepadInjector
{
  private:
	bool isConnected;
	InjectedInputGamepadInfo gamepadState;
	InputInjector injector;

	void disconnectGamepad();

  public:
	GamepadInjector();
	void connectGamepad();
	void inject();
	~GamepadInjector();

	void Update(InjectedInputGamepadInfo state);
	void PressButton(GamepadButtons button);
	void ReleaseButton(GamepadButtons button);

};

#endif // GAMEPADINJECTOR_HPP
