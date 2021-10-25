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
	PhysBody* ricochet03;
	bool sensed;

	// Map Objects of Scene Intro
	b2Body* Object01;
	b2Body* Object02;
	b2Body* Object03;
	b2Body* Object04;
	b2Body* Object05;
	b2Body* Object06;
	b2Body* Object07;
	b2Body* Object08;
	b2Body* Object09;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* map;

	uint bonus_fx;
	uint ball_lost_fx;
	uint win_fx;
	//uint loose_fx;

	p2Point<int> ray;
	bool ray_on;
};
