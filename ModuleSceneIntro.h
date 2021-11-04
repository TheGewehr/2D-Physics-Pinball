#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;	
	//p2List<PhysBody*> mapStaticBodies;

	PhysBody* sensor_loss;
	PhysBody* sensor_win;
	PhysBody* sensor_out;
	PhysBody* ricochet01;
	PhysBody* ricochet02;
	PhysBody* fliperLeft;
	PhysBody* fliperRight;

	PhysBody* spring;

	//PhysBody* ricochet03;
	bool sensed;


	float angularSpeedLeft;
	float maxAngleLeft;
	float minAngleLeft;
	float angleMarginLeft;

	float angularSpeedRight;
	float maxAngleRight;
	float minAngleRight;
	float angleMarginRight;

	// Map Objects of Scene Intro


	SDL_Texture* circle;
	SDL_Texture* Map;
	SDL_Texture* fliper_left;
	SDL_Texture* fliper_right;
	SDL_Texture* spring_;
	SDL_Texture* win_lose;

	SDL_Rect win_screen;
	SDL_Rect lose_screen;

	uint bonus_fx;
	uint ball_lost_fx;
	uint win_fx;
	uint hitmarker_fx;
	uint sonic_fx;
	uint wasted_fx;
	uint sadforloosing_fx;
	uint surprisem_fx;

	bool music_played;

	p2Point<int> ray;
	bool ray_on;

	int lives;
	bool win_con;
	bool game_end;

	SDL_Rect end_rect;
	bool spawn_ball;

	int spring_x;
	int spring_y;

	bool spring_calc;
};
