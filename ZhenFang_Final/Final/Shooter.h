#pragma once
#include <AI.h>
#include <XEngine.h>

enum class ShooterState
{
	MoveToMushroom,
	CollectMushroom,
	FleeBullet,
	Win,
	Lose
};

class Shooter :public AI::Agent
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ChangeState(ShooterState nextState);

	//void SetPosition(const X::Math::Vector2& pos) { mPosition = pos; }
	//const X::Math::Vector2& GetPosition() const { return mPosition; }

	void SetTargetMushroom(size_t index) { mTargetMushroom = index; }
	size_t GetTargetMushroom() const { return mTargetMushroom; }
	bool IsGameOver = false;
	//float mSpeed = 300.0f;
	bool IsEnemy = false;
	void SetActive(int select);
	bool WinGame = false;
	bool LoseGame = false;
	int health = 100;
	bool IsDamageable = true;

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	std::unique_ptr<AI::StateMachine<Shooter>> mStateMachine;
	//X::Math::Vector2 mPosition;
	X::TextureId mTextureId{};
	size_t mTargetMushroom = 0;




};
