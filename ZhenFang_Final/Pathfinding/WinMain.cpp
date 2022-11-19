#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>
#include "TileMap.h"


AI::GridBasedGraph graph;
TileMap tilemap;
X::Math::Vector2 GetPosition(int column, int row)
{
	return {
		(column + 0.5f) * tilemap.GetTileWidth(),
		(row + 0.5f) * tilemap.GetTileHeight()
	};
}

X::Math::Vector2 GetPosition(const AI::GridBasedGraph::Node* node)
{
	return GetPosition(node->column, node->row);
}

AI::Pathing::NodePath path;
AI::Pathing::Context context;


bool IsNotWalkable(int column, int row)
{
	return tilemap.IsBlocked(column, row);
}

float GetCost(int fromColumn, int fromRow, int toColumn, int toRow)
{
	return tilemap.GetTraversalCost(fromColumn, fromRow, toColumn, toRow);
}

float GetDistance(int select, int fromColumn, int fromRow, int endColumn, int endRow)
{
	if (select == 0)
	{
		return tilemap.GetEstimatedDistanceManhattan(fromColumn, fromRow, endColumn, endRow);
	}
	else if (select == 1)
	{
		return tilemap.GetEstimatedDistanceEuclidean(fromColumn, fromRow, endColumn, endRow);
	}
	else if (select == 2)
	{
		return tilemap.GetEstimatedDistanceDiagonal(fromColumn, fromRow, endColumn, endRow);
	}
	return 0;
}

void ShowPathingUI()
{
	ImGui::Begin("Pathfinding", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderInt("Start X", &context.startX, 0, tilemap.GetColumns());
	ImGui::SliderInt("Start Y", &context.startY, 0, tilemap.GetRows());



	ImGui::SliderInt("End X", &context.endX, 0, tilemap.GetColumns());
	ImGui::SliderInt("End Y", &context.endY, 0, tilemap.GetRows());

	if (ImGui::Button("Run BFS"))
	{
		graph.ResetSearchParams();
		graph.Initialize(tilemap.GetColumns(), tilemap.GetRows());
		context.openList.clear();
		path.clear();
		context.closedList.clear();

		if (AI::Pathing::RunBFS(graph, context, IsNotWalkable))
		{
			path = AI::Pathing::GetPath(graph, context);
		}


	}

	if (ImGui::Button("Run DFS"))
	{
		graph.ResetSearchParams();
		graph.Initialize(tilemap.GetColumns(), tilemap.GetRows());
		context.openList.clear();
		path.clear();
		context.closedList.clear();
		if (AI::Pathing::RunDFS(graph, context, IsNotWalkable))
		{
			path = AI::Pathing::GetPath(graph, context);
		}

	}
	if (ImGui::Button("Run Dijkstra"))
	{
		graph.ResetSearchParams();
		graph.Initialize(tilemap.GetColumns(), tilemap.GetRows());
		context.openList.clear();
		path.clear();
		context.closedList.clear();
		if (AI::Pathing::RunDijkstra(graph, context, IsNotWalkable,GetCost))
		{
			path = AI::Pathing::GetPath(graph, context);
		}

	}
	if (ImGui::CollapsingHeader("Run A star", true))
	{

		static int select = -1;
		ImGui::RadioButton("Manhattan", &select, 0);
		ImGui::RadioButton("Euclidean", &select, 1);
		ImGui::RadioButton("Diagonal", &select, 2);
		if (ImGui::Button("Run"))
		{
			graph.ResetSearchParams();
			graph.Initialize(tilemap.GetColumns(), tilemap.GetRows());
			context.openList.clear();
			path.clear();
			context.closedList.clear();
			if (AI::Pathing::RunAstar(select, graph, context, IsNotWalkable, GetCost, GetDistance))
			{
				path = AI::Pathing::GetPath(graph, context);
			}
		}


	}


	ImGui::End();
}


X::TextureId marioTextureId;
X::Math::Vector2 marioPosition{ 100.0f, 100.0f };

void MakeMap(int columns, int rows)
{
	int n = columns * rows;
	int* myInts = new int[n];
	delete[] myInts;
}


void GameInit()
{
	marioTextureId = X::LoadTexture("mario.png");

	tilemap.LoadMap("map.txt");
	tilemap.LoadTiles("tileset.txt");
}

void DrawClosedList()
{
	for (auto iter = context.closedList.begin(); iter != context.closedList.end(); ++iter)
	{
		AI::GridBasedGraph::Node* node = *iter;
		AI::GridBasedGraph::Node* parent = node->parent;
		if (parent != nullptr)
		{
			auto pos = GetPosition(node);
			auto parentpos = GetPosition(node->parent);
			X::DrawScreenLine(pos, parentpos, X::Colors::White);
		}

	}

}
void DrawPath()
{
	if (path.size() >= 2)
	{
		for (int i = 0; i < path.size() - 1; ++i)
		{
			auto node1 = GetPosition(path[i]);
			auto node2 = GetPosition(path[i + 1]);
			X::DrawScreenLine(node1, node2, X::Colors::Black);
		}

	}
}

bool GameLoop(float deltaTime)
{
	tilemap.Render();
	tilemap.Update();
	const float moveSpeed = 100.0f; // pixel per second
	tilemap.ShowDebugUI();
	ShowPathingUI();
	X::DrawScreenCircle(GetPosition(context.startX, context.startY), static_cast<float>(tilemap.GetTileWidth() / 2), X::Colors::Red);
	X::DrawScreenCircle(GetPosition(context.endX, context.endY), static_cast<float>(tilemap.GetTileWidth() / 2), X::Colors::Pink);

	DrawClosedList();
	DrawPath();




	//if (X::IsKeyDown(X::Keys::D))
	//	marioPosition.x += moveSpeed * deltaTime;

	//X::DrawScreenLine({ 100.0f, 300.0f }, { 500.0f, 700.0f }, X::Colors::GreenYellow);

	//X::DrawSprite(marioTextureId, marioPosition);

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}



void GameCleanup()
{
	marioTextureId = 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}