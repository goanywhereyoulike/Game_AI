#include "EnemyStates.h"
#include "Shooter.h"
#include "Bullet.h"

extern Bullet bullet;

const float detectionDistance = 400.0f;

bool Isinsector(const X::Math::Vector2 v1, const X::Math::Vector2 v2, const X::Math::Vector2 v3)
{
	float r1 = v1.x * v2.y - v2.x * v1.y;
	float r2 = v1.x * v3.y - v3.x * v1.y;
	float result = r1 * r2;
	return result < 0;

}
void DrawEnemydetectionScale(Enemy& enemy, X::Math::Vector2& pos1, X::Math::Vector2& pos2, X::Math::Vector2& targetPos)
{
	float headingAngle = atan2(-enemy.heading.x, enemy.heading.y);
	float shootSpan = 20 * X::Math::kDegToRad;
	float shootAngleFrom = headingAngle - shootSpan;
	float shootAngleTo = headingAngle + shootSpan;
	pos1 = enemy.position + X::Math::TransformCoord(X::Math::Vector2::YAxis() * detectionDistance, X::Math::Matrix3::Rotation(shootAngleFrom));
	pos2 = enemy.position + X::Math::TransformCoord(X::Math::Vector2::YAxis() * detectionDistance, X::Math::Matrix3::Rotation(shootAngleTo));

	X::DrawScreenCircle(enemy.position, detectionDistance, X::Colors::Red);
	X::DrawScreenLine(enemy.position, pos1, X::Colors::Magenta);
	X::DrawScreenLine(enemy.position, pos2, X::Colors::Magenta);
	X::DrawScreenLine(enemy.position, targetPos, X::Colors::Magenta);
	X::DrawScreenArc(enemy.position, detectionDistance, shootAngleFrom + X::Math::kPi / 2, shootAngleTo + X::Math::kPi / 2, X::Colors::Magenta);

}


void WanderState::Enter(Enemy& enemy)
{
}

void WanderState::Update(Enemy& enemy, float deltaTime)
{
	if (enemy.GetGameOver())
	{
		enemy.ChangeState(EnemyState::GameOver);
	}
	auto targetPos = enemy.GetTargetposition();
	if (X::Math::Distance(enemy.position, targetPos) < detectionDistance)
	{

		enemy.ChangeState(EnemyState::Chase);
	}
	else
	{
		enemy.SetActive(3);
	}

	X::DrawScreenCircle(enemy.position, detectionDistance, X::Colors::Red);
	X::DrawScreenText("Wander", enemy.position.x, enemy.position.y, 18.0f, X::Colors::Cyan);

}

void WanderState::Exit(Enemy& enemy)
{
}


void ShootState::Enter(Enemy& enemy)
{
}

void ShootState::Update(Enemy& enemy, float deltaTime)
{
	auto targetPos = enemy.GetTargetposition();
	enemy.destination = targetPos;
	enemy.SetActive(0);

	X::Math::Vector2 pos1 = 0;
	X::Math::Vector2 pos2 = 0;
	DrawEnemydetectionScale(enemy, pos1, pos2, targetPos);


	X::Math::Vector2 Viewline1{ pos1 - enemy.position };
	X::Math::Vector2 Viewline2{ pos2 - enemy.position };
	X::Math::Vector2 targetline{ targetPos - enemy.position };


	X::DrawScreenText("Shoot", enemy.position.x, enemy.position.y, 18.0f, X::Colors::Blue);


	if (!bullet.IsActive())
	{
		bullet.Fire(enemy.position, X::Math::Normalize(targetline) * 300.0f);

	}


	if (X::Math::Distance(enemy.position, targetPos) > detectionDistance)
	{

		enemy.ChangeState(EnemyState::Wander);
	}
	else if (!Isinsector(targetline, Viewline1, Viewline2))
	{
		enemy.ChangeState(EnemyState::Chase);
	}
	if (enemy.GetGameOver())
	{
		enemy.ChangeState(EnemyState::GameOver);
	}


}

void ShootState::Exit(Enemy& enemy)
{
}


void ChaseState::Enter(Enemy& enemy)
{
}

void ChaseState::Update(Enemy& enemy, float deltaTime)
{

	auto targetPos = enemy.GetTargetposition();
	enemy.destination = targetPos;
	enemy.SetActive(0);

	X::Math::Vector2 pos1 = 0;
	X::Math::Vector2 pos2 = 0;
	DrawEnemydetectionScale(enemy, pos1, pos2, targetPos);


	X::Math::Vector2 Viewline1{ pos1 - enemy.position };
	X::Math::Vector2 Viewline2{ pos2 - enemy.position };
	X::Math::Vector2 targetline{ targetPos - enemy.position };

	X::DrawScreenText("Chase", enemy.position.x, enemy.position.y, 18.0f, X::Colors::Red);

	if (Isinsector(targetline, Viewline1, Viewline2))
	{
		enemy.ChangeState(EnemyState::Shoot);
	}
	else if (X::Math::Distance(enemy.position, targetPos) > detectionDistance)
	{

		enemy.ChangeState(EnemyState::Wander);
	}

	if (enemy.GetGameOver())
	{
		enemy.ChangeState(EnemyState::GameOver);
	}



}

void ChaseState::Exit(Enemy& enemy)
{
}



void GameOverState::Enter(Enemy& enemy)
{
}

void GameOverState::Update(Enemy& enemy, float deltaTime)
{
	enemy.velocity = 0;
}

void GameOverState::Exit(Enemy& enemy)
{
}
