#include "SCV.h"


void SCV::Load()
{
	radius = 16.0f;
	mass = 1.0f;
	maxSpeed = 200.0f;

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	//mDumbBehaviour = mSteeringModule->AddBehvior<DumbBehavior>();
	//mDumbBehaviour->SetActive(true);
	mSeekBehavior = mSteeringModule->AddBehvior<AI::SeekBehavior>();
	//mSeekBehavior->SetActive(true);
	mFleeBehavior = mSteeringModule->AddBehvior<AI::FleeBehavior>();
	//mFleeBehavior->SetActive(true);
	mArriveBehavior = mSteeringModule->AddBehvior<AI::ArriveBehavior>();

	mWanderBehavior = mSteeringModule->AddBehvior<AI::WanderBehavior>();

	//mWanderBehavior->SetActive(true);

	mTextureIds[0] = X::LoadTexture("scv_01.png");
	mTextureIds[1] = X::LoadTexture("scv_02.png");
	mTextureIds[2] = X::LoadTexture("scv_03.png");
	mTextureIds[3] = X::LoadTexture("scv_04.png");
	mTextureIds[4] = X::LoadTexture("scv_05.png");
	mTextureIds[5] = X::LoadTexture("scv_06.png");
	mTextureIds[6] = X::LoadTexture("scv_07.png");
	mTextureIds[7] = X::LoadTexture("scv_08.png");
	mTextureIds[8] = X::LoadTexture("scv_09.png");
	mTextureIds[9] = X::LoadTexture("scv_10.png");
	mTextureIds[10] = X::LoadTexture("scv_11.png");
	mTextureIds[11] = X::LoadTexture("scv_12.png");
	mTextureIds[12] = X::LoadTexture("scv_13.png");
	mTextureIds[13] = X::LoadTexture("scv_14.png");
	mTextureIds[14] = X::LoadTexture("scv_15.png");
	mTextureIds[15] = X::LoadTexture("scv_16.png");

}

void SCV::Unload()
{
	mSteeringModule.reset();
}

void SCV::Update(float deltaTime)
{
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

void SCV::Render()
{
	float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	int frame = (int)(angle / X::Math::kTwoPi * 16.0f) % 16;
	X::DrawSprite(mTextureIds[frame], position);
}

void SCV::SetActive(int select)
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

void SCV::SetDecel(AI::ArriveBehavior::Decleration behavior)
{

	if (behavior == AI::ArriveBehavior::Decleration::slow)
	{
		mArriveBehavior->SetDecel(AI::ArriveBehavior::Decleration::slow);
	}
	else if (behavior == AI::ArriveBehavior::Decleration::normal)
	{
		mArriveBehavior->SetDecel(AI::ArriveBehavior::Decleration::normal);
	}
	else if (behavior == AI::ArriveBehavior::Decleration::fast)
	{

		mArriveBehavior->SetDecel(AI::ArriveBehavior::Decleration::fast);
	}

}
