#include "Precompiled.h"
#include "SteeringModule.h"

using namespace AI;

SteeringModule::SteeringModule(Agent& agent) :
	mAgent(agent) {}

void AI::SteeringModule::Purge()
{
	mBehaviors.clear();
}

X::Math::Vector2 AI::SteeringModule::Calculate() const
{
	X::Math::Vector2 totalForce;
	for (auto& behavior : mBehaviors)
	{
		if (behavior->IsActive())
		{
			totalForce += behavior->Calculate(mAgent) * behavior->GetWeight();

		}

	}

	return totalForce;
}
