#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
class InputManagerC
{
public:
	static InputManagerC	*CreateInstance();
	static InputManagerC	*GetInstance() {return sInstance;};
	void					init(){};
	void					update();
//checkout gameframework.cpp
	Vector2D*					getCurrentMousePosition(){};
	//keyboard interface?

private:
	InputManagerC(){};

	static InputManagerC *sInstance;
	
};
#endif