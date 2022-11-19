#pragma once
#include <AI.h>
#include <XEngine.h>
class Bullet:public AI::Agent
{
public:
	void Load(std::string bulletname);
	void Unload();
	void Update(float deltaTime);
	void Render();
	void Fire(const X::Math::Vector2& position,
		const X::Math::Vector2& velocity);
	void Kill();


	bool IsActive()const { return mActive; }
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(position, 10.0f); }

	void SetTargetposition(X::Math::Vector2  target) { mTargetpos = target; }
	X::Math::Vector2 GetTargetposition() const { return mTargetpos; }

private:
	X::TextureId mTextureId = 0;
	X::Math::Vector2 mTargetpos;
	bool mActive = false;

	float mSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;


};
