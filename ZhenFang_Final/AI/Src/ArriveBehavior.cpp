#include "Precompiled.h"
#include "ArriveBehavior.h"


using namespace AI;
X::Math::Vector2 ArriveBehavior::Calculate(AI::Agent& agent)
{
	auto agentToDestination = agent.destination - agent.position;
	double dist = X::Math::Magnitude(agentToDestination);
	if (dist > 0)
	{
		const double DecelTweaker = 0.3;
		double speed = dist / (static_cast<double>(decel) * DecelTweaker);
		speed = X::Math::Min(speed, static_cast<double>(agent.maxSpeed));
		auto DesiredVelocity = agentToDestination * speed / dist;
		return DesiredVelocity - agent.velocity;

	}
	return X::Math::Vector2::Zero();
}
