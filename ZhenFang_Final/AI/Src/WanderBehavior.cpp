#include "Precompiled.h"
#include "WanderBehavior.h"


using namespace AI;

X::Math::Vector2 AI::WanderBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 localTarget = localWanderTarget;
	X::Math::Vector2 randomAmount = { wanderJitter,wanderJitter };

	X::Math::Vector2 newTarget = localTarget + X::RandomVector2(-randomAmount, randomAmount);

	localWanderTarget = X::Math::Normalize(newTarget) * wanderRadius;
	X::Math::Vector2 projectedTarget = localWanderTarget + X::Math::Vector2{ 0.0f,wanderDistance };

	X::Math::Matrix3 worldTransform = agent.GetWorldTransform();

	X::Math::Vector2 worldWanderTarget = X::Math::TransformCoord(projectedTarget, worldTransform);

	X::Math::Vector2 circleCenter = X::Math::TransformCoord({ 0.0f,wanderDistance }, worldTransform);

	X::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Green);
	X::DrawScreenCircle(circleCenter, wanderRadius, X::Colors::Cyan);
	X::DrawScreenCircle(worldWanderTarget, 2.0f, X::Colors::Red);


	auto agentToTarget = worldWanderTarget - agent.position;
	auto DesiredVelocity = X::Math::Normalize(agentToTarget) * agent.maxSpeed;
	return DesiredVelocity - agent.velocity;
}
