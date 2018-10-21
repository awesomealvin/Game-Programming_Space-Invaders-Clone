#include "SpaceMissile.h"



SpaceMissile::SpaceMissile() :
	TIME_TO_HIT(3.0f)
{

}


SpaceMissile::~SpaceMissile()
{
}

void SpaceMissile::SetTarget(float x, float y)
{
	m_target.SetX(x);
	m_target.SetY(y);


}

void SpaceMissile::Process(float deltaTime)
{
		
}
