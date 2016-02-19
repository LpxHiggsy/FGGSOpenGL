#pragma once

class HelloGL; //Forward declare HelloGL

namespace GLUTCallbacks 
{ 
	void Init(HelloGL * gl); 
	void Display(); 
	//void Reshape(int width, int height);
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
};