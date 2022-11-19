#pragma once
#include "Agent.h"
#include "SteeringBehavior.h"

namespace AI
{
	class WanderBehavior:public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		X::Math::Vector2 localWanderTarget;
		float wanderDistance = 100.0f;
		float wanderRadius = 10.0f;
		float wanderJitter = 1.0f;
	
	
	};

}