#include "SurvivorStates.h"

#include "ZombieWorld.h"

void MoveToZombieState::Enter(Survivor& survivor)
{
	survivor.mSpeed = 300.0f;
}

void MoveToZombieState::Update(Survivor& survivor, float deltaTime)
{
	size_t target = survivor.GetTargetZombie();
	auto targetPos = ZombieWorld::Get().GetZombiePosition(target);
	if (X::Math::Distance(survivor.GetPosition(), targetPos) < 10.0f)
	{
		survivor.ChangeState(SurvivorState::ShootZombie);
	}

	else
	{
		auto direction = X::Math::Normalize(targetPos - survivor.GetPosition());
		if (direction.x > 0)
		{
			survivor.IsFacingLeft = false;
		}
		else
		{
			survivor.IsFacingLeft = true;
		}
		auto velocity = direction * survivor.mSpeed;
		survivor.SetPosition(survivor.GetPosition() + (velocity * deltaTime));
	}

}

void MoveToZombieState::Exit(Survivor& survivor)
{

}


void ShootZombieState::Enter(Survivor& survivor)
{

}

void ShootZombieState::Update(Survivor& survivor, float deltaTime)
{
	size_t target = survivor.GetTargetZombie();

	size_t nextTarget = target + 1;
	if (nextTarget >= ZombieWorld::Get().GetZombiesLeft())
	{

		nextTarget = 0;
		survivor.IsGameOver = true;
		
		
	}
	survivor.SetTargetZombie(nextTarget);

	ZombieWorld::Get().KillZombie(target);

	if (!ZombieWorld::Get().IsZombieAlive(target))
	{
		survivor.ChangeState(SurvivorState::MoveToZombie);
	}
	if (survivor.IsGameOver)
	{
		survivor.ChangeState(SurvivorState::Pause);
	}

}

void ShootZombieState::Exit(Survivor& survivor)
{

}



void PauseState::Enter(Survivor& survivor)
{
	survivor.mSpeed = 0.0f;
}

void PauseState::Update(Survivor& survivor, float deltaTime)
{
	survivor.SetPosition({ 50,50 });
}

void PauseState::Exit(Survivor& survivor)
{
	
}
