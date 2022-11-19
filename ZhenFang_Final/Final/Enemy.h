#pragma once
#include <AI.h>
#include <XEngine.h>
#include "Shooter.h"
enum class EnemyState
{
	Wander,
	Chase,
	Shoot,
	GameOver
};

class Enemy :public AI::Agent
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ChangeState(EnemyState nextState);

	//void SetPosition(const X::Math::Vector2& pos) { mPosition = pos; }
	//const X::Math::Vector2& GetPosition() const { return mPosition; }

	void SetTargetposition(X::Math::Vector2  target) { mTargetpos = target; }
	X::Math::Vector2 GetTargetposition() const { return mTargetpos; }

	void SetActive(int select);

	void SetGameOver(bool gameover) { IsGameOver = gameover; }
	bool GetGameOver() { return IsGameOver;}
private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	std::unique_ptr<AI::StateMachine<Enemy>> mStateMachine;
	//X::Math::Vector2 mPosition;
	X::TextureId mTextureId{};
	X::Math::Vector2 mTargetpos;
	bool IsGameOver = false;


};
