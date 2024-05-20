#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "TextObject.h"

bool Init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1 ){
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if(g_screen == NULL){
		return false;
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		return false;
	}
	//Read file wav audio
	g_sound_exp[0] = Mix_LoadWAV("Explosion+1.wav");
	g_sound_exp[1] = Mix_LoadWAV("Explosion+2.wav");
	g_sound_bullet[0] = Mix_LoadWAV("Laser.wav");
	g_sound_bullet[1] = Mix_LoadWAV("Fire1.wav");
	if(g_sound_exp[0] == NULL, g_sound_bullet[0] == NULL, g_sound_bullet[1] == NULL, g_sound_exp[1] == NULL){
		return false;
	}

	if(TTF_Init() == -1){
		return false;
	}
	g_font_text = TTF_OpenFont("comicate.ttf", 20);
	if(g_font_text == NULL){
		return false;
	}
	g_font_text2 = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf", 20);
	if(g_font_text == NULL){
		return false;
	}

	return true;
}

int main(int arc, char* argv[]){

	bool is_run_screen = true;
	int bkgn_x = 0;

	bool is_quit = false;
	if(Init() == false){
		return 0;
	}

	g_bkground = SDLCommonFunc::LoadImage("bg4800.png");
	if(g_bkground == NULL){
		return 0;
	}

	//Make Player Power
	PlayerPower player_power;
	player_power.Init();

	//Make Text Mark
	TextObject mark_game;
	mark_game.SetColor(TextObject::BLACK_TEXT);

	//Make Text Time
	TextObject time_game;
	time_game.SetColor(TextObject::RED_TEXT);

	//make MainObject
	MainObject plane_object;
	plane_object.SetRect(100, 200);
	bool ret = plane_object.LoadImg("plane_fly.png");
	if(!ret){
		return 0;
	}

	//Init Explosion Object - Main
	ExplosionObject exp_main;
	ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clip();
	if(ret == false){
		return 0;
	}

	//Init Explosion Object - Threats
	ExplosionObject exp_threats;
	ret = exp_threats.LoadImg("exp.png");
	exp_threats.set_clip();
	if(ret == false){
		return 0;
	}

	//Make ThreatObject
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
	for(int t = 0; t < NUM_THREATS; t++){
		ThreatObject* p_threat = (p_threats + t);
		if(p_threat){
			ret = p_threat->LoadImg("af1.png");
			if(ret == false){
				return 0;
			}
			int rand_y = rand() % 400;
			if(rand_y > SCREEN_HEIGHT - 200){
				rand_y = SCREEN_HEIGHT * 0.3;
			}
			p_threat->SetRect(SCREEN_WIDTH + t * 400, rand_y);
			p_threat->set_x_val(2.5);
			BulletObject* p_amo = new BulletObject();
			p_threat->InitAmo(p_amo);
		}
	}

	unsigned int die_number = 0;
	unsigned int mark_value = 0;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text2);
	if(ret_menu == 1)
		is_quit = true;

	while(!is_quit){
		while(SDL_PollEvent(&g_even)){
			if(g_even.type == SDL_QUIT){
				is_quit = true;
				break;
			}
			plane_object.HandleInputAction(g_even, g_sound_bullet);
		}

		//Apply Background
		/*bkgn_x -= 2;
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH, 0);
		if(bkgn_x <= - SCREEN_WIDTH){
			bkgn_x = 0;
		}*/
		if(is_run_screen){
			bkgn_x -= 1.5;
			if(bkgn_x <= - (WIDTH_BACKGROUND - SCREEN_WIDTH)){
				is_run_screen = false;
			}
			else{
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
			}
		}
		else{
			SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		}

		//Show player power
		player_power.Render(g_screen);


		//Implement main object
		plane_object.HandleMove();
		plane_object.Show(g_screen);
		plane_object.MakeAmo(g_screen);

		//Implement threats object
		for(int tt = 0; tt < NUM_THREATS; tt++){
			ThreatObject* p_threat = (p_threats + tt);
			if(p_threat){
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);	

				//Collision Threat Bullet -> Main object
				bool is_col1 = false;
				std::vector<BulletObject*> amo_arr = p_threat->GetAmoList();
				for(int am = 0; am < amo_arr.size(); am++){
					BulletObject* p_amo = amo_arr.at(am);
					if(p_amo){
						is_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(), plane_object.GetRect());
						if(is_col1 == true){
							p_threat->ResetAmo(p_amo);
							break;
						}
					}
				}

				//check collision main and threat
				bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
				if(is_col || is_col1){

					for(int ex = 0; ex < 4; ex++){
						int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5 ) - EXP_WIDTH * 0.5;
						int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5 ) - EXP_HEIGHT * 0.5;

						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.ShowEx(g_screen);

						//update screen
						if(SDL_Flip(g_screen) == -1){
							delete [] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
					}
					Mix_PlayChannel(-1, g_sound_exp[1], 0);

					die_number++;
					if(die_number <= 2){
						SDL_Delay(1000);
						plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
						player_power.Decrease();
						player_power.Render(g_screen);

						//update screen
						if(SDL_Flip(g_screen) == -1){
							delete [] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
					}
					else{
						if(MessageBox(NULL, L"GAME OVER!", L"info", MB_OK) == IDOK){
							delete [] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;
						}
					}
				}

				//Check collison main bullet with threats
				std::vector<BulletObject*> amo_list = plane_object.GetAmoList();
				for(int im = 0; im < amo_list.size(); im++){
					BulletObject* p_amo = amo_list.at(im);
					if(p_amo != NULL){
						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if(ret_col){
							mark_value++;
							for(int tx = 0; tx < 4; tx++){
								int x_pos = p_amo->GetRect().x - EXP_WIDTH * 0.5;
								int y_pos = p_amo->GetRect().y - EXP_HEIGHT * 0.5;

								exp_threats.set_frame(tx);
								exp_threats.SetRect(x_pos, y_pos);
								exp_threats.ShowEx(g_screen);

								//update screen
								if(SDL_Flip(g_screen) == -1){
									delete [] p_threats;
									SDLCommonFunc::CleanUp();
									SDL_Quit();
									return 0;
								}
								Mix_PlayChannel(-1, g_sound_exp[0], 0);
							}
							p_threat->Reset(SCREEN_WIDTH + tt * 400);
							plane_object.RemoveAmo(im);
						}
					}
				}
			}
		}

		//Show time for game
		std::string str_time = "Time : ";
		UINT32 time_val = SDL_GetTicks() / 1000;
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.SetRect(SCREEN_WIDTH - 200, 20);
		time_game.CreateGameText(g_font_text2, g_screen);

		//show mark	value to screen
		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark : ");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		mark_game.CreateGameText(g_font_text, g_screen);

		//update screen
		if(SDL_Flip(g_screen) == -1){
			delete [] p_threats;
			SDLCommonFunc::CleanUp();
			SDL_Quit();
			return 0;
		}
	}

	delete [] p_threats;
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 0;
}