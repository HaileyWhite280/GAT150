#pragma once
#include "Framework/System.h"
#include <SDL.h>
#include <vector>

namespace nc
{
	
	class InputSystem : public System
	{
	public:
		enum class eKeyState
		{
			Idle,
			Pressed,
			Held,
			Release
		};
		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id);
		bool isPreviousKeyDown(int id);

		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState;
		int numKeys;
	};
}