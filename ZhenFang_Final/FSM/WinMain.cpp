#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>
#include "Survivor.h"
#include "ZombieWorld.h"

Survivor survivor;

void GameInit()
{
	ZombieWorld::Get().Load();
	survivor.Load();
}




bool GameLoop(float deltaTime)
{

	survivor.Update(deltaTime);

	ZombieWorld::Get().Render();
	survivor.Render();
	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}



void GameCleanup()
{
	ZombieWorld::Get().Unload();
	survivor.Unload();
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}