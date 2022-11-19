#include "Shooter.h"
#include "ShooterStates.h"

void Shooter::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<Shooter>>(*this);
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mStateMachine->AddState<MoveToMushroomState>();
	mStateMachine->AddState<CollectMushroomState>();
	mStateMachine->AddState<FleeState>();
	mStateMachine->AddState<WinState>();
	mStateMachine->AddState<LoseState>();

	mSeekBehavior = mSteeringModule->AddBehvior<AI::SeekBehavior>();
	mFleeBehavior = mSteeringModule->AddBehvior<AI::FleeBehavior>();
	mArriveBehavior = mSteeringModule->AddBehvior<AI::ArriveBehavior>();
	mWanderBehavior = mSteeringModule->AddBehvior<AI::WanderBehavior>();

	ChangeState(ShooterState::MoveToMushroom);
	X::Math::Vector2 pos{ 500.0f,1000.0f };
	position = pos;
	mTextureId = X::LoadTexture("Player.png");

}

void Shooter::Unload()
{
	mTextureId = 0;
	mStateMachine.reset();
	mSteeringModule.reset();
}

void Shooter::Update(float deltaTime)
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

void Shooter::Render()
{
	float angle = atan2(-heading.x, heading.y) + X::Math::kPi / 2;
	X::DrawSprite(mTextureId, position, angle);

}

void Shooter::ChangeState(ShooterState nextState)
{
	mStateMachine->ChangeState((size_t)nextState);
}

void Shooter::SetActive(int select)
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
