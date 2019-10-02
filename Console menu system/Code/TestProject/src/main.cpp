#include <iostream>
#include <thread>

#include "MenuAPI.h"
#include "Input.h"

#include "Timer.h"
#include "Test.h"

using namespace MenuSystem;
using namespace MenuSystem::Input;
using namespace MenuSystem::Utility;

using namespace std;

int main()
{
	MenuSystemOption option;
	option.backgroundColor = COLOR_Black;
	option.blockingInput = false;
	option.cursorPos = Pos();
	option.cursorSize = 25;
	option.cursorVisible = false;
	option.windowSize = Pos(120, 40);
	option.windowTitle = "Console test";

	if(!API::Init(option))
	{
		return 1;
	}

	Timer timer;
	Timer timer2;
	Test test;
	test.Init();

	API::Render();
	float fps2 = 0;
	float fps = 0;
	float time = 0.000001f;
	float oldTime = 0;
	int frames = 0;
	timer.Start();
	timer2.Start();
	while(1)
	{
		oldTime = time;
		time = (float)timer.ElapsedSecounds();
		fps2 += 1.0f / (time - oldTime);
		if(timer2.ElapsedSecounds() >= 1.0f)
		{
			timer2.Start();
			fps = fps2 / frames;
			fps2 = 0;
			frames = 0;
		}

		if(!test.Update(fps))
			break;
		API::Render();
		// std::this_thread::sleep_for(10ms);

		frames++;
	}

	API::Shutdown();

	return 0;
}