// COMP710 GP 2D Framework 2018
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;

class Entity
{
	//Member Methods:
public:
	Entity();
	Entity(int windowWidth);
	~Entity();

	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void DrawRotation(BackBuffer& backBuffer, float angle);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	void SetPositionCenter(float x, float y);

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	float GetPositionSpriteCenterX() const;

	float GetSpriteHeight() const;
	float GetSpriteWidth() const;

	float GetCenterPositionX() const;
	float GetCenterPositionY() const;

	float GetRadius() const;

	void Revive(float x, float y);

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;

	int m_windowWidth;

	float m_radius;

private:

};

#endif //__ENTITY_H__
