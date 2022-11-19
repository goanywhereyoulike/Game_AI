#include "Precompiled.h"
#include "SeekBehavior.h"


using namespace AI;
X::Math::Vector2 SeekBehavior::Calculate(AI::Agent& agent)
{
	auto agentToDestination = agent.destination - agent.position;
	if (X::Math::MagnitudeSqr(agentToDestination) <= 0.0f)
	{
		return X::Math::Vector2::Zero();
	}
	auto direction = X::Math::Normalize(agentToDestination);
	auto DesiredVelocity = direction * agent.maxSpeed;
	return DesiredVelocity - agent.velocity;
}
