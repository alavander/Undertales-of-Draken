#include "objects.h"

GameObject::GameObject()
{
	x = 0;
	y = 0;
	velX = 0;
	dirX = 0;
	velY = 0;
	dirY = 0;

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;
	int ANIMATION = 0;

	image = NULL;
	alive = true;
	movable = true;
	solid = true;
}

void GameObject::Destroy()
{
}

void GameObject::Init(float x, float y, float velX, int dirX, float velY, int dirY)
{
	GameObject::x = x;
	GameObject::y = y;
	GameObject::velX = velX;
	GameObject::dirX = dirX;
	GameObject::velY = velY;
	GameObject::dirY = dirY;
}

void GameObject::Update()
{
    if(CanMove())
    {
	x += velX * dirX;
	y += velY * dirY;
    }
}

void GameObject::Render()
{ //virtual
}

void GameObject::GotHit(int dam)
{ //virtual
}

int GameObject::CheckAttack()
{ //virtual
}

void GameObject::ChangeState(int newState)
{ //virtual
}

bool GameObject::CollisionCheck(GameObject *otherObject)
{
	float oX = otherObject->GetX();
	float oY = otherObject->GetY();

	if( x < oX && x + 60 > oX && y == oY && GetID() == PLAYER ) return true;
    else if (x > oX && x - 60 < oX && y == oY && GetID() == ENEMY) return true;
	else
		return false;
}

	bool GameObject::IsInRange(GameObject *otherObject, float attack_range)
{
	float oX = otherObject->GetX();
	float oY = otherObject->GetY();

	if( x < oX && x + attack_range > oX && y == oY && GetID() == PLAYER ) return true;
    else if (x > oX && x - attack_range < oX && y == oY && GetID() == ENEMY) return true;
	else
		return false;
}


	bool GameObject::IsOppositeTeam(GameObject *otherObject)
{
    if ( GetID() == PLAYER && otherObject->GetID() == ENEMY) return true;
    else if ( GetID() == ENEMY && otherObject->GetID() == PLAYER) return true;
    else return false;
}

    float GameObject::PositionY()
    {
    float PositionY;
    int Lane = GetY();
	switch(Lane)
	{
        case 0:
        PositionY = LANE[0] - frameHeight;
        return PositionY;
        break;
        case 1:
        PositionY = LANE[1] - frameHeight;
        return PositionY;
        break;
        case 2:
        PositionY = LANE[2] - frameHeight;
        return PositionY;
        break;
        case 3:
        PositionY = LANE[3] - frameHeight;
        return PositionY;
        break;
	}
    }
