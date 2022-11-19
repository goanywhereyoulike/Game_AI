#pragma once
#include "GridBasedGraph.h"

namespace AI::Pathing
{
	using NodePath = std::vector<const AI::GridBasedGraph::Node*>;
	using OpenList = std::list<AI::GridBasedGraph::Node*>;
	using ClosedList = std::list<AI::GridBasedGraph::Node*>;

	using IsNotWalkableFunc = std::function<bool(int, int)>;
	using GetCostFunc = std::function<float(int, int, int, int)>;
	using GetDistanceFunc = std::function<float(int,int, int, int, int)>;

	struct Context
	{
		AI::Pathing::OpenList openList;
		AI::Pathing::ClosedList closedList;
		int startX = 0, startY = 0;
		int endX = 0, endY = 0;

	};


	bool RunBFS(GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable);

	bool RunDFS(GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable);

	bool RunDijkstra(GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable, GetCostFunc GetCost);

	bool RunAstar(int select, GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable, GetCostFunc GetCost, GetDistanceFunc GetDistance);


	NodePath GetPath(const GridBasedGraph& graph, Context& context);


}