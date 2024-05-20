#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46


class MainObject : public BaseObject{
public:
	MainObject();
	~MainObject();
	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleMove();
	void SetAmoList(std::vector<BulletObject*> amo_list) {p_amo_list_ = amo_list;}
	std::vector<BulletObject*> GetAmoList() const {return p_amo_list_;}
	void MakeAmo(SDL_Surface* des);
	void RemoveAmo(const int& idx);
private:
	int x_val;
	int y_val;
	std::vector<BulletObject*> p_amo_list_;
};

#endif //MAIN OBJECT