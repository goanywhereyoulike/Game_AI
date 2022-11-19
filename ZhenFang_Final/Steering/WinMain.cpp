#include "SCV.h"
#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

SCV scv;
void ShowPathingUI()
{
	ImGui::Begin("Steering", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Seek"))
	{
		scv.SetActive(0);
	}
	if (ImGui::Button("Flee"))
	{
		scv.SetActive(1);
	}

	if (ImGui::CollapsingHeader("Arrive", true))
	{
		
		if (ImGui::Button("slow"))
		{

			scv.SetDecel(AI::ArriveBehavior::Decleration::slow);
			scv.SetActive(2);

		}
		if (ImGui::Button("normal"))
		{
			scv.SetDecel(AI::ArriveBehavior::Decleration::normal);
			scv.SetActive(2);
		}
		if (ImGui::Button("fast"))
		{
			scv.SetDecel(AI::ArriveBehavior::Decleration::fast);
			scv.SetActive(2);
		}


		


	}
	if (ImGui::Button("Wander"))
	{
		scv.SetActive(3);
	}


	ImGui::End();
}

void GameInit()
{
	scv.Load();
}




bool GameLoop(float deltaTime)
{

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		scv.destination.x = static_cast<float>(X::GetMouseScreenX());
		scv.destination.y = static_cast<float>(X::GetMouseScreenY());
	}
	scv.Update(deltaTime);
	scv.Render();

	X::DrawScreenDiamond(scv.destination, 10.0f, X::Colors::Red);
	ShowPathingUI();
	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}



void GameCleanup()
{
	scv.Unload();
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