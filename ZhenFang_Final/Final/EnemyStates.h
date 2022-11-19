#pragma once
#include "Enemy.h"
#include <AI.h>
#include <XEngine.h>

class WanderState : public AI::State<Enemy>
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;
};

class ShootState : public AI::State<Enemy>
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;
};

class ChaseState : public AI::State<Enemy>
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;
};

class GameOverState : public AI::State<Enemy>
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy, float deltaTime) override;
	void Exit(Enemy& enemy) override;
};
