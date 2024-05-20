#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_
#include "BaseObject.h"
#include <vector>

class PlayerPower : public BaseObject{
private:
	int number_;
	std::vector<int> pos_list_;
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num) {number_ = num;}
	void AddPos(const int& x_pos);
	void Render(SDL_Surface* des);
	void Init();
	void Decrease();
};

#endif