#include "Survivor.h"
#include "SurvivorStates.h"

void Survivor::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<Survivor>>(*this);
	mStateMachine->AddState<MoveToZombieState>();
	mStateMachine->AddState<ShootZombieState>();
	mStateMachine->AddState<PauseState>();
	ChangeState(SurvivorState::MoveToZombie);

	mTextureId = X::LoadTexture("survivor_rifle.png");
}

void Survivor::Unload()
{
	mTextureId = 0;
	mStateMachine.reset();
}

void Survivor::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
	
}

void Survivor::Render()
{
	const X::Flip fliptype = IsFacingLeft ? X::Flip::Horizontal : X::Flip::None;
	X::DrawSprite(mTextureId, mPosition,X::Pivot::Center, fliptype);
}

void Survivor::ChangeState(SurvivorState nextState)
{
	mStateMachine->ChangeState((size_t)nextState);
}