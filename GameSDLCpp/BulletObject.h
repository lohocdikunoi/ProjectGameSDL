#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"

#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

class BulletObject : public BaseObject{
private:
	int x_val;
	int y_val;
	bool is_move_;
	int bullet_type_;
public:
	enum BulletType
	{
		NONE = 0,
		LASER = 1,
		SPHERE = 2
	};
	BulletObject();
	~BulletObject();
	void HandleInputAction(SDL_Event events);
	void HandleMove(const int& x_boder, const int& y_boder);
	void HandleMoveRightToLeft();
	int get_type() const {return bullet_type_;}
	void set_type(const int& type) {bullet_type_ = type;}
	bool get_is_move() const {return is_move_;}
	void set_is_move(const bool is_move) {is_move_ = is_move;}
	void SetWidthHeight(const int& width, const int& height) {rect_.w = width; rect_.h = height;}
	void set_x_val(const int& val) {x_val = val;}
	void set_y_val(const int& val) {y_val = val;}
	int get_x_val() const {return x_val;}
	int get_y_val() const {return y_val;}
};

#endif