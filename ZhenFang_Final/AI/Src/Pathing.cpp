#include "Precompiled.h"
#include "Pathing.h"
using namespace AI::Pathing;

bool comparecost(const AI::GridBasedGraph::Node* node1, const AI::GridBasedGraph::Node* node2)
{

	return node1->g < node2->g;

}
bool compareAllcost(const AI::GridBasedGraph::Node* node1, const AI::GridBasedGraph::Node* node2)
{

	return ((node1->h + node1->g) < (node2->g + node2->h));

}


bool AI::Pathing::RunBFS(GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable)
{
	bool found = false;
	auto node = graph.GetNode(context.startX, context.startY);
	auto endnode = graph.GetNode(context.endX, context.endY);
	context.openList.push_back(node);
	node->opened = true;
	while (!found && !context.openList.empty())
	{
		auto catchnode = context.openList.front();
		context.openList.pop_front();
		//openList.erase(openList.begin());

		if (catchnode == endnode)
		{
			found = true;
		}
		else
		{
			for (int n = 0; n < 8; n++)
			{

				if (catchnode->neighbors[n] == nullptr)
				{
					continue;
				}

				auto column = catchnode->neighbors[n]->column;
				auto row = catchnode->neighbors[n]->row;
				if (IsNotWalkable(column, row))
				{
					continue;
				}
				auto newnode = catchnode->neighbors[n];

				if (!newnode->opened && !newnode->closed)
				{
					context.openList.push_back(newnode);
					newnode->opened = true;
					newnode->parent = catchnode;

				}

			}
		}
		context.closedList.push_back(catchnode);
		catchnode->opened = false;
		catchnode->closed = true;


	}
	return found;
}

bool AI::Pathing::RunDFS(GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable)
{
	bool found = false;
	auto node = graph.GetNode(context.startX, context.startY);
	auto endnode = graph.GetNode(context.endX, context.endY);
	context.openList.push_back(node);
	node->opened = true;

	while (!found && !context.openList.empty())
	{
		auto catchnode = context.openList.front();
		context.openList.pop_front();
		//openList.erase(openList.begin());

		if (catchnode == endnode)
		{
			found = true;
		}
		else
		{
			for (int n = 0; n < 8; n++)
			{

				if (catchnode->neighbors[n] == nullptr)
				{
					continue;
				}

				auto column = catchnode->neighbors[n]->column;
				auto row = catchnode->neighbors[n]->row;
				if (IsNotWalkable(column, row))
				{
					continue;
				}
				auto newnode = catchnode->neighbors[n];

				if (!newnode->opened && !newnode->closed)
				{
					context.openList.push_front(newnode);
					//openList.push_back(newnode);
					newnode->opened = true;
					newnode->parent = catchnode;

				}

			}
		}
		context.closedList.push_back(catchnode);

		catchnode->opened = false;
		catchnode->closed = true;
	}

	return found;
}

bool AI::Pathing::RunDijkstra(GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable, GetCostFunc GetCost)
{
	bool found = false;
	auto node = graph.GetNode(context.startX, context.startY);
	auto endnode = graph.GetNode(context.endX, context.endY);
	context.openList.push_back(node);
	node->opened = true;

	while (!found && !context.openList.empty())
	{
		auto catchnode = context.openList.front();
		context.openList.pop_front();
		//openList.erase(openList.begin());

		if (catchnode == endnode)
		{
			found = true;
		}
		else
		{
			for (int n = 0; n < 8; n++)
			{
				auto newnode = catchnode->neighbors[n];
				if (newnode == nullptr || newnode->closed)
				{
					continue;
				}

				auto column = newnode->column;
				auto row = newnode->row;
				if (IsNotWalkable(column, row))
				{
					continue;
				}

				if (!newnode->opened)
				{
					context.openList.push_front(newnode);
					//openList.push_back(newnode);
					newnode->opened = true;
					newnode->g = catchnode->g + GetCost(catchnode->column, catchnode->row, newnode->column, newnode->row);
					newnode->parent = catchnode;
					context.openList.sort(comparecost);
				}
				else
				{
					float newcost = catchnode->g + GetCost(catchnode->column, catchnode->row, newnode->column, newnode->row);
					if (newcost < newnode->g)
					{
						newnode->g = newcost;
						newnode->parent = catchnode;
						context.openList.sort(comparecost);
					}

				}

			}
		}
		context.closedList.push_back(catchnode);

		catchnode->opened = false;
		catchnode->closed = true;
	}

	return found;
}

bool AI::Pathing::RunAstar(int select, GridBasedGraph& graph, Context& context, IsNotWalkableFunc IsNotWalkable, GetCostFunc GetCost,GetDistanceFunc GetDistance)
{
	bool found = false;
	auto node = graph.GetNode(context.startX, context.startY);
	auto endnode = graph.GetNode(context.endX, context.endY);
	context.openList.push_back(node);
	node->opened = true;

	while (!found && !context.openList.empty())
	{
		auto catchnode = context.openList.front();
		context.openList.pop_front();
		//openList.erase(openList.begin());

		if (catchnode == endnode)
		{
			found = true;
		}
		else
		{
			for (int n = 0; n < 8; n++)
			{
				auto newnode = catchnode->neighbors[n];
				if (newnode == nullptr || newnode->closed)
				{
					continue;
				}

				auto column = newnode->column;
				auto row = newnode->row;
				if (IsNotWalkable(column, row))
				{
					continue;
				}

				if (!newnode->opened)
				{
					context.openList.push_front(newnode);
					//openList.push_back(newnode);
					newnode->opened = true;

					newnode->h = GetDistance(select, newnode->column, newnode->row, endnode->column, endnode->row);

					newnode->g = catchnode->g + GetCost(catchnode->column, catchnode->row, newnode->column, newnode->row);
					newnode->parent = catchnode;
					context.openList.sort(compareAllcost);
				}
				else
				{
					float newcost = catchnode->g + GetCost(catchnode->column, catchnode->row, newnode->column, newnode->row);
					//float allnewcost =newcost+ catchnode->h;
					if (newcost < newnode->g)
					{
						newnode->g = newcost;
						newnode->parent = catchnode;
						context.openList.sort(compareAllcost);
					}

				}

			}
		}
		context.closedList.push_back(catchnode);

		catchnode->opened = false;
		catchnode->closed = true;
	}


	return found;
}

NodePath AI::Pathing::GetPath(const GridBasedGraph& graph, Context& context)
{
	NodePath nodePath;
	//path.clear();
	auto node = graph.GetNode(context.endX, context.endY);
	while (node != nullptr)
	{
		nodePath.push_back(node);
		node = node->parent;

	}

	std::reverse(nodePath.begin(), nodePath.end());

	return nodePath;
}
