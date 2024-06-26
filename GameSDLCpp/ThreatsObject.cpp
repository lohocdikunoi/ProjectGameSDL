#include "ThreatsObject.h"

ThreatObject::ThreatObject(){
	x_val = 0;
	y_val = 0;
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT * 0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;
}

ThreatObject::~ThreatObject(){
	if(p_amo_list_.size() > 0){
		for(int i = 0; i < p_amo_list_.size(); i++){
			BulletObject* p_amo = p_amo_list_.at(i);
			if(p_amo != NULL){
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void ThreatObject::HandleInputAction(SDL_Event events){

}

void ThreatObject::HandleMove(const int& x_boder, const int& y_boder){
	rect_.x -= x_val;
	if(rect_.x < 0){
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if(rand_y > SCREEN_HEIGHT - 200){
			rand_y = SCREEN_HEIGHT * 0.3;
		}
		rect_.y = rand_y;
	}
}

void ThreatObject::InitAmo(BulletObject* p_amo){
	if(p_amo){
		bool ret = p_amo->LoadImg("sphere.png");
		if(ret){
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(BulletObject::SPHERE);
			p_amo->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			p_amo->set_x_val(3.5);
			p_amo_list_.push_back(p_amo);
		}
	}
}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit){
	for(int i = 0; i < p_amo_list_.size(); i++){
		BulletObject* p_amo = p_amo_list_.at(i);
		if(p_amo){
			if(p_amo->get_is_move()){
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			else{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			}
		}
	}
}

void ThreatObject::ResetAmo(BulletObject* p_amo){
	p_amo->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
}

void ThreatObject::Reset(const int& x_boder){
	rect_.x = x_boder;
	int rand_y = rand() % 400;
	if(rand_y > SCREEN_HEIGHT - 200){
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	rect_.y = rand_y;

	for(int i = 0; i < p_amo_list_.size(); i++){
		BulletObject* p_amo = p_amo_list_.at(i);
		if(p_amo){
			ResetAmo(p_amo);
		}
	}
}