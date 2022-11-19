#include "Bullet.h"

void Bullet::Load(std::string bulletname)
{
	mTextureId = X::LoadTexture(bulletname.c_str());
	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);
}
void Bullet::Unload()
{
	mTextureId = 0;
}
void Bullet::Update(float deltaTime)
{
	if (mActive)
	{
		position += velocity * deltaTime;

		const uint32_t screenWidth = X::GetScreenWidth();
		const uint32_t screenHeight = X::GetScreenHeight();

		if (position.x > screenWidth
			|| position.x < 0.0f
			|| position.y > screenHeight
			|| position.y < 0.0f)
		{
			Kill();
		}
	}
}
void Bullet::Render()
{
	if (mActive)
	{
		X::DrawSprite(mTextureId, position);
	}
}

void Bullet::Fire(const X::Math::Vector2& nposition, const X::Math::Vector2& nvelocity)
{
	position = nposition;
	velocity = nvelocity;
	mActive = true;
}

void Bullet::Kill()
{
	mActive = false;
}
