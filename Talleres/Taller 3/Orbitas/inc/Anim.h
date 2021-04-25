#ifndef Anim_H
#define Anim_H

#include <iostream>
#include <string>

class Anim{

public:
	Anim();
	Anim(double lim_);
	~Anim();

	void SetLim(double lim_);
	void NewAnim();
	void StartLine();
	void EndLine();

private:

	double lim;

	std::string limits="";


};

#endif
