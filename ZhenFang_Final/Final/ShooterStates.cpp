#include "ShooterStates.h"

#include "MushroomWorld.h"
#include "Bullet.h"


extern Bullet bullet;


void MoveToMushroomState::Enter(Shooter& survivor)
{
	survivor.IsDamageable = true;
}

void MoveToMushroomState::Update(Shooter& survivor, float deltaTime)
{
	size_t target = survivor.GetTargetMushroom();
	auto targetPos = MushroomWorld::Get().GetMushroomPosition(target);
	if (X::Math::Distance(survivor.position, targetPos) < 50.0f)
	{

		survivor.ChangeState(ShooterState::CollectMushroom);
	}

	else
	{

		survivor.destination = targetPos;
		survivor.SetActive(0);

	}
	X::DrawScreenCircle(survivor.position, 100.0f, X::Colors::Red);
	if (X::Math::Distance(bullet.position, survivor.position) < 100.0f)
	{
		survivor.destination = bullet.position;
		survivor.SetActive(1);
		survivor.ChangeState(ShooterState::FleeBullet);
	}
	if (survivor.health <= 0)
	{
		survivor.ChangeState(ShooterState::Lose);
		survivor.IsGameOver = true;
	}
	X::DrawScreenText("Move", survivor.position.x, survivor.position.y, 18.0f, X::Colors::Red);

}

void MoveToMushroomState::Exit(Shooter& survivor)
{

}


void CollectMushroomState::Enter(Shooter& survivor)
{
	survivor.IsDamageable = true;
}

void CollectMushroomState::Update(Shooter& survivor, float deltaTime)
{

	size_t target = survivor.GetTargetMushroom();

	size_t nextTarget = target + 1;
	if (nextTarget >= MushroomWorld::Get().GetMushroomsLeft())
	{

		nextTarget = 0;
		survivor.WinGame = true;


	}
	survivor.SetTargetMushroom(nextTarget);

	MushroomWorld::Get().KillMushroom(target);

	if (!MushroomWorld::Get().IsMushroomAlive(target))
	{
		survivor.ChangeState(ShooterState::MoveToMushroom);
	}

	if (survivor.WinGame)
	{
		survivor.ChangeState(ShooterState::Win);
		survivor.IsGameOver = true;
	}
	if (survivor.health <= 0)
	{
		survivor.ChangeState(ShooterState::Lose);
		survivor.IsGameOver = true;
	}

	X::DrawScreenText("Collect", survivor.position.x, survivor.position.y, 18.0f, X::Colors::Yellow);


}

void CollectMushroomState::Exit(Shooter& survivor)
{
	
}

void FleeState::Enter(Shooter& survivor)
{
}

void FleeState::Update(Shooter& survivor, float deltaTime)
{
	survivor.destination = bullet.position;
	survivor.SetActive(1);
	X::DrawScreenCircle(survivor.position, 100.0f, X::Colors::Red);
	if (X::Math::Distance(bullet.position, survivor.position) > 100.0f)
	{

		survivor.ChangeState(ShooterState::MoveToMushroom);
	}

	const X::Math::Circle bulletCircle = bullet.GetBoundingCircle();

	const float distance = X::Math::Distance(survivor.position, bulletCircle.center);
	const float radii = 16.0f + bulletCircle.radius;

	if (distance <= radii)
	{
		bullet.Kill();
		if (survivor.IsDamageable)
		{
			survivor.health -= 10;
			survivor.IsDamageable = false;
		}
		
		if (survivor.health < 0)
		{
			survivor.health = 0;
		}

	}
	X::DrawScreenText("Flee", survivor.position.x, survivor.position.y, 18.0f, X::Colors::White);
	if (survivor.health <= 0)
	{
		survivor.ChangeState(ShooterState::Lose);
		survivor.IsGameOver = true;
	}
}

void FleeState::Exit(Shooter& survivor)
{
}

void WinState::Enter(Shooter& survivor)
{
	//survivor.mSpeed = 0.0f;
}

void WinState::Update(Shooter& survivor, float deltaTime)
{
	//survivor.Unload();
	auto screenWidth = X::GetScreenWidth();
	auto screenHeight = X::GetScreenHeight();
	X::DrawScreenText("You Win!", screenWidth * 0.3f, screenHeight * 0.3f, 80, X::Colors::White);
	survivor.velocity = 0;

}

void WinState::Exit(Shooter& survivor)
{

}


void LoseState::Enter(Shooter& survivor)
{
}

void LoseState::Update(Shooter& survivor, float deltaTime)
{
	auto screenWidth = X::GetScreenWidth();
	auto screenHeight = X::GetScreenHeight();
	X::DrawScreenText("You Lose!", screenWidth * 0.3f, screenHeight * 0.3f, 80, X::Colors::White);
	survivor.velocity = 0;
}

void LoseState::Exit(Shooter& survivor)
{
}
