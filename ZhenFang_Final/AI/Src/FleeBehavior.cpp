#include "Precompiled.h"
#include "FleeBehavior.h"


using namespace AI;
X::Math::Vector2 FleeBehavior::Calculate(AI::Agent& agent)
{

	const double PanicDistanceSq = 100.0 * 100.0;
	auto agentToDestination = agent.position - agent.destination;
	//Vec2DDistanceSq(m_pVehicle->Pos(), target) > PanicDistanceSq
	//if (X::Math::DistanceSqr(agent.position, agent.destination) > PanicDistanceSq)
	//{
	//	return X::Math::Vector2::Zero();
	//}
	auto direction = X::Math::Normalize(agentToDestination);
	return direction * agent.maxSpeed;

}
