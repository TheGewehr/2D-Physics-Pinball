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
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor_loss;
	PhysBody* sensor_win;
	PhysBody* ricochet01;
	PhysBody* ricochet02;
	PhysBody* fliperLeft;
	PhysBody* fliperRight;
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
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* map;
	SDL_Texture* fliper_left;
	SDL_Texture* fliper_right;

	uint bonus_fx;
	uint ball_lost_fx;
	uint win_fx;
	//uint loose_fx;

	p2Point<int> ray;
	bool ray_on;

	int lives;
	bool win_con;
	bool game_end;

	SDL_Rect end_rect;
	bool spawn_ball;
};
