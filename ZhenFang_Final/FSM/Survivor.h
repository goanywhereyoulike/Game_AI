#pragma once
#include <AI.h>
#include <XEngine.h>

enum class SurvivorState
{
	MoveToZombie,
	ShootZombie,
	Pause
};

class Survivor
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ChangeState(SurvivorState nextState);

	void SetPosition(const X::Math::Vector2& pos) { mPosition = pos; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }

	void SetTargetZombie(size_t index) { mTargetZombie = index; }
	size_t GetTargetZombie() const { return mTargetZombie; }
	bool IsFacingLeft = false;
	bool IsShooting = false;
	bool IsGameOver = false;
	float mSpeed = 300.0f;
private:
	std::unique_ptr<AI::StateMachine<Survivor>> mStateMachine;
	X::Math::Vector2 mPosition;
	X::TextureId mTextureId;
	size_t mTargetZombie = 0;
	
	
};
