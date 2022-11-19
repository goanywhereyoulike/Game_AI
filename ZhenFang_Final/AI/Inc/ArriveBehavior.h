#pragma once
#include "Agent.h"
#include "SteeringBehavior.h"

namespace AI
{
	class ArriveBehavior :public AI::SteeringBehavior
	{
	public:
		enum class Decleration
		{
			slow = 3,
			normal = 2,
			fast = 1
		};

	public:
		Decleration decel = Decleration::normal;
		X::Math::Vector2 Calculate(AI::Agent& agent) override;

		void SetDecel(Decleration newdecel) { decel = newdecel; }
	};
}


