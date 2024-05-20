#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33

class ThreatObject : public BaseObject{
private:
	int x_val;
	int y_val;
	std::vector<BulletObject*> p_amo_list_;
public:
	ThreatObject();
	~ThreatObject();
	void HandleMove(const int& x_boder, const int& y_boder);
	void HandleInputAction(SDL_Event events);
	void set_x_val(const int& val) {x_val = val;}
	void set_y_val(const int& val) {y_val = val;}
	int get_x_val() const {return x_val;}
	int set_y_val() const {return y_val;}
	void SetAmoList(std::vector<BulletObject*> amo_list) {p_amo_list_ = amo_list;}
	std::vector<BulletObject*> GetAmoList() const {return p_amo_list_;}
	void InitAmo(BulletObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& x_boder);
	void ResetAmo(BulletObject* p_amo);
};

#endif