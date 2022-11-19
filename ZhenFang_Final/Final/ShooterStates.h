#pragma once

#include "Shooter.h"
#include <AI.h>
#include <XEngine.h>

class MoveToMushroomState : public AI::State<Shooter>
{
public:
	void Enter(Shooter& survivor) override;
	void Update(Shooter& survivor, float deltaTime) override;
	void Exit(Shooter& survivor) override;
};

class CollectMushroomState : public AI::State<Shooter>
{
public:
	void Enter(Shooter& survivor) override;
	void Update(Shooter& survivor, float deltaTime) override;
	void Exit(Shooter& survivor) override;
};

class FleeState : public AI::State<Shooter>
{
public:
	void Enter(Shooter& survivor) override;
	void Update(Shooter& survivor, float deltaTime) override;
	void Exit(Shooter& survivor) override;
};


class WinState : public AI::State<Shooter>
{
public:
	void Enter(Shooter& survivor) override;
	void Update(Shooter& survivor, float deltaTime) override;
	void Exit(Shooter& survivor) override;
};

class LoseState : public AI::State<Shooter>
{
public:
	void Enter(Shooter& survivor) override;
	void Update(Shooter& survivor, float deltaTime) override;
	void Exit(Shooter& survivor) override;
};
