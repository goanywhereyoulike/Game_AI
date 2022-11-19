#include "ZombieWorld.h"

namespace
{
	constexpr size_t zombieCount = 10;
}

ZombieWorld& ZombieWorld::Get()
{
	static ZombieWorld instance;
	return instance;
}

void ZombieWorld::Load()
{
	mZombieCollected.resize(zombieCount, false);
	mZombieActive.resize(zombieCount, true);

	for (size_t i = 0; i < zombieCount; ++i)
		mZombiePositions.push_back(X::RandomVector2({ 100.0f, 100.0f }, { 1180.0f, 620.0f }));

	mTextureId = X::LoadTexture("zombie_idle.png");
}

void ZombieWorld::Unload()
{
	mTextureId = 0;
}

void ZombieWorld::Render()
{

		for (size_t i = 0; i < mZombiePositions.size(); ++i)
		{
			if (!mZombieCollected[i]&& mZombieActive[i])
				X::DrawSprite(mTextureId, mZombiePositions[i]);
			if (!mZombieActive[i])
			{
				auto mTextureId2 = X::LoadTexture("zombie_dead.png");
				X::DrawSprite(mTextureId2, mZombiePositions[i]);
			}

		}

}

void ZombieWorld::CollectZombie(size_t index)
{
	mZombieCollected[index] = true;
}

void ZombieWorld::KillZombie(size_t index)
{
	mZombieActive[index] = false;
}

const X::Math::Vector2& ZombieWorld::GetZombiePosition(size_t index) const
{
	return mZombiePositions[index];
}

bool ZombieWorld::IsZombieCollected(size_t index) const
{
	return mZombieCollected[index];
}

size_t ZombieWorld::GetZombiesLeft() const
{
	size_t left = 0;
	for (auto alive :mZombieActive)
	{
		//if (alive)
			left++;
	}
	return left;
}

bool ZombieWorld::IsZombieAlive(size_t index) const
{
	return mZombieActive[index];
}
