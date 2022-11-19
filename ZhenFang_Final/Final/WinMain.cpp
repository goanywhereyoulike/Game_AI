#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>
#include "Bullet.h"
#include "Shooter.h"
#include "Enemy.h"
#include "MushroomWorld.h"

Shooter survivor;
Enemy enemy;

Bullet bullet;

void GameInit()
{
	MushroomWorld::Get().Load();
	survivor.Load();
	enemy.Load();

	bullet.Load("bullet2.png");

}




bool GameLoop(float deltaTime)
{

	survivor.Update(deltaTime);
	MushroomWorld::Get().Render();
	survivor.Render();
	enemy.SetTargetposition(survivor.position);
	enemy.Update(deltaTime);
	enemy.Render();

	bullet.Update(deltaTime);
	bullet.Render();
	if (survivor.IsGameOver)
	{
		enemy.SetGameOver(survivor.IsGameOver);
	}

	auto screenWidth = X::GetScreenWidth();
	auto screenHeight = X::GetScreenHeight();

	X::DrawScreenText(std::to_string(survivor.health).c_str(), screenWidth * 0.1f, screenHeight * 0.1f, 50, X::Colors::White);




	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}



void GameCleanup()
{
	MushroomWorld::Get().Unload();
	survivor.Unload();
	enemy.Unload();

	bullet.Unload();


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