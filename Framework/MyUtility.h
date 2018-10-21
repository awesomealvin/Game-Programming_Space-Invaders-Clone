#ifndef __MYUTILITY_H__
#define __MYUTILITY_H__

class MyUtility
{
public:
	MyUtility();
	~MyUtility();

	static MyUtility& GetInstance();
	static void DestroyInstance();

	int RandomInt(int min, int max);
	float RandomFloat(float min, float max);

	float ToRadians(float degrees);

	const float PI;

private:

	static MyUtility* sm_pInstance;


};

#endif // __MYUTILITY_H__
