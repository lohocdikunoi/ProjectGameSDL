#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "Common_Function.h"
#include "BaseObject.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class ExplosionObject : public BaseObject{
private:
	int frame_;
	SDL_Rect clip_[4];
public:
	ExplosionObject();
	~ExplosionObject();
	void set_clip();
	void set_frame(const int& fr) {frame_ = fr;}
	void ShowEx(SDL_Surface* des);
};

#endif