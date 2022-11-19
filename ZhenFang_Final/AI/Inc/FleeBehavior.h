#pragma once
#include "Agent.h"
#include "SteeringBehavior.h"
namespace AI
{
	class FleeBehavior :public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(AI::Agent& agent) override;


	};
}
