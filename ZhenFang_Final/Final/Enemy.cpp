#include "Enemy.h"
#include "EnemyStates.h"

void Enemy::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<Enemy>>(*this);
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mStateMachine->AddState<WanderState>();
	mStateMachine->AddState<ChaseState>();
	mStateMachine->AddState<ShootState>();
	mStateMachine->AddState<GameOverState>();

	mSeekBehavior = mSteeringModule->AddBehvior<AI::SeekBehavior>();
	mFleeBehavior = mSteeringModule->AddBehvior<AI::FleeBehavior>();
	mArriveBehavior = mSteeringModule->AddBehvior<AI::ArriveBehavior>();
	mWanderBehavior = mSteeringModule->AddBehvior<AI::WanderBehavior>();

	ChangeState(EnemyState::Wander);

	mTextureId = X::LoadTexture("Enemy.png");
	X::Math::Vector2 pos{1000.0f,1000.0f};
	position = pos;

}

void Enemy::Unload()
{
	mTextureId = 0;
	mStateMachine.reset();
	mSteeringModule.reset();
}

void Enemy::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
	auto force = mSteeringModule->Calculate();
	auto acceleration = force / mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;

	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
	{
		heading = X::Math::Normalize(velocity);
	}
	

	const float screenWidth = static_cast<float>(X::GetScreenWidth());
	const float screenHeight = static_cast<float>(X::GetScreenHeight());

	if (position.x < 0.0f)
		position.x += screenWidth;
	if (position.x > screenWidth)
		position.x -= screenWidth;
	if (position.y < 0.0f)
		position.y += screenHeight;
	if (position.y > screenHeight)
		position.y -= screenHeight;

}

void Enemy::Render()
{
	float angle = atan2(-heading.x, heading.y) + X::Math::kPi / 2;
	X::DrawSprite(mTextureId, position, angle);

}

void Enemy::ChangeState(EnemyState nextState)
{
	mStateMachine->ChangeState((size_t)nextState);
}

void Enemy::SetActive(int select)
{
	if (select == 0)
	{
		mSeekBehavior->SetActive(true);
		mFleeBehavior->SetActive(false);
		mArriveBehavior->SetActive(false);
		mWanderBehavior->SetActive(false);
	}
	else if (select == 1)
	{
		mSeekBehavior->SetActive(false);
		mFleeBehavior->SetActive(true);
		mArriveBehavior->SetActive(false);
		mWanderBehavior->SetActive(false);
	}
	else if (select == 2)
	{
		mSeekBehavior->SetActive(false);
		mFleeBehavior->SetActive(false);
		mArriveBehavior->SetActive(true);
		mWanderBehavior->SetActive(false);

	}
	else if (select == 3)
	{
		mSeekBehavior->SetActive(false);
		mFleeBehavior->SetActive(false);
		mArriveBehavior->SetActive(false);
		mWanderBehavior->SetActive(true);
		mWanderBehavior->wanderDistance = 100.0f;
		mWanderBehavior->wanderRadius = 40.0f;
		mWanderBehavior->wanderJitter = 10.0f;
	}


}
