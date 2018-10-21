#include "MyUtility.h"

#include <cstdlib>

MyUtility* MyUtility::sm_pInstance = 0;

MyUtility::MyUtility() :
	PI(3.1415926535897f)
{

}


MyUtility::~MyUtility()
{

}

MyUtility & MyUtility::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new MyUtility();
	}

	return (*sm_pInstance);
}

void MyUtility::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

int MyUtility::RandomInt(int min, int max)
{
	int randomNumber = rand() % (max - min + 1) + min;
	return randomNumber;
}

float MyUtility::RandomFloat(float min, float max)
{
	float random = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	float range = max - min;

	float randomNumber = (random * range) + min;

	return randomNumber;
}

float MyUtility::ToRadians(float degrees)
{
	return ((degrees * PI) / 180.0f);
}
