#pragma once

#include "Survivor.h"
#include <AI.h>
#include <XEngine.h>

class MoveToZombieState : public AI::State<Survivor>
{
public:
	void Enter(Survivor& survivor) override;
	void Update(Survivor& survivor, float deltaTime) override;
	void Exit(Survivor& survivor) override;
};

class ShootZombieState : public AI::State<Survivor>
{
public:
	void Enter(Survivor& survivor) override;
	void Update(Survivor& survivor, float deltaTime) override;
	void Exit(Survivor& survivor) override;
};

class PauseState : public AI::State<Survivor>
{
public:
	void Enter(Survivor& survivor) override;
	void Update(Survivor& survivor, float deltaTime) override;
	void Exit(Survivor& survivor) override;
};

