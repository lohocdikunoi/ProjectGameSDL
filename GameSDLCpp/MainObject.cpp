#include "MainObject.h"

MainObject::MainObject(){
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val = 0;
	y_val = 0;
}

MainObject::~MainObject(){
	;
}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]){
	if(events.type == SDL_KEYDOWN){
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val -= HEIGHT_MAIN_OBJECT / 8;
			//todo
			break;
		case SDLK_DOWN:
			y_val += HEIGHT_MAIN_OBJECT / 8;
			//todo
			break;
		case SDLK_RIGHT:
			x_val += WIDTH_MAIN_OBJECT / 8;
			//todo
			break;
		case SDLK_LEFT:
			x_val -= WIDTH_MAIN_OBJECT / 8;
			//todo
			break;
		default:
			break;
		}
	}
	else if(events.type == SDL_KEYUP){
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: y_val += HEIGHT_MAIN_OBJECT / 8; break;
		case SDLK_DOWN : y_val -= HEIGHT_MAIN_OBJECT / 8; break;
		case SDLK_RIGHT : x_val -= WIDTH_MAIN_OBJECT / 8; break;
		case SDLK_LEFT : x_val += WIDTH_MAIN_OBJECT / 8; break;
		default:
			break;
		}
	}
	else if(events.type == SDL_MOUSEBUTTONDOWN){
		BulletObject* p_amo = new BulletObject();
		if(events.button.button == SDL_BUTTON_LEFT){
			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg("laser.png");
			p_amo->set_type(BulletObject::LASER);
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
		else if(events.button.button == SDL_BUTTON_RIGHT){
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg("sphere2.png");
			p_amo->set_type(BulletObject::SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}
		p_amo->SetRect(this->rect_.x + rect_.w - 40, this->rect_.y + rect_.h * 0.8);
		p_amo->set_is_move(true);
		p_amo->set_x_val(20);
		p_amo_list_.push_back(p_amo);
	}
	else if(events.type == SDL_MOUSEBUTTONUP){

	}
	else{
		;
	}
}

void MainObject::HandleMove(){
	rect_.x += x_val;
	if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH){
		rect_.x -= x_val;
	}

	rect_.y += y_val;
	if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200){
		rect_.y -= y_val;
	}
}

void MainObject::MakeAmo(SDL_Surface* des){
	for(int i = 0; i < p_amo_list_.size(); i++){
			BulletObject* p_amo = p_amo_list_.at(i);
			if(p_amo != NULL){
				if(p_amo->get_is_move()){
					p_amo->Show(des);
					p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				}
				else{
					if(p_amo != NULL){
						p_amo_list_.erase(p_amo_list_.begin() + i);
						delete p_amo;
						p_amo = NULL;
					}
				}
			}
		}
}

void MainObject::RemoveAmo(const int& idx){
	for(int i = 0; i < p_amo_list_.size(); i++){
		if(idx < p_amo_list_.size()){
			BulletObject* p_amo = p_amo_list_.at(idx);
			p_amo_list_.erase(p_amo_list_.begin() + idx);
			if(p_amo != NULL){
				delete p_amo;
				p_amo = NULL;
			}
		}
	}
}