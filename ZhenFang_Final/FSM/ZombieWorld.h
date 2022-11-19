#pragma once

#include <XEngine.h>

class ZombieWorld
{
public:
	static ZombieWorld& Get();

public:
	void Load();
	void Unload();

	void Render();

	void CollectZombie(size_t index);
	void KillZombie(size_t index);
	const X::Math::Vector2& GetZombiePosition(size_t index) const;
	bool IsZombieCollected(size_t index) const;
	size_t GetZombiesLeft() const;

	bool IsZombieAlive(size_t index) const;


private:
	std::vector<X::Math::Vector2> mZombiePositions;
	std::vector<bool> mZombieCollected;
	X::TextureId mTextureId;
	std::vector<bool> mZombieActive;
};
