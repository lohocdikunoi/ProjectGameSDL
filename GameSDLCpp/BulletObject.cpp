#include "BulletObject.h"

BulletObject::BulletObject(){
	rect_.x = 0;
	rect_.y = 0;
	x_val = 0;
	y_val = 0;
	is_move_ = false;
	bullet_type_ = NONE;
}

BulletObject::~BulletObject(){

}

void BulletObject::HandleMove(const int& x_boder, const int& y_boder){
	rect_.x += x_val;
	if(rect_.x > x_boder){
		is_move_ = false;
	}
}

void BulletObject::HandleInputAction(SDL_Event events){
	;//TODO;
}

void BulletObject::HandleMoveRightToLeft(){
	rect_.x -= x_val;
	if(rect_.x < 0){
		is_move_ = false;
	}
}