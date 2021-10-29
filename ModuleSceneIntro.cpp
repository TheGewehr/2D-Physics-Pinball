#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = mapStaticBodies = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Vectors for the kinematic chains of the flippers
	int flipers01[16] = {
	6 - 16, 10-17,
	15 - 16, 3 - 17,
	24 - 16, 4 - 17,
	98 - 16, 43 - 17,
	98 - 16, 52 - 17,
	90 - 16, 53 - 17,
	8 - 16, 27 - 17,
	4 - 16, 19 - 17
	};

	int flipers02[14] = {
	82-86, 4 -16,
	5 - 86, 44 - 16,
	3 - 86, 51 - 16,
	13 - 86, 54 - 16,
	95 - 86, 26 - 16,
	99 - 86, 16 - 16,
	94 - 86, 7 - 16
	};



	int map_[100] = {
	344, 5	   ,
	279, 17	   ,
	213, 49	   ,
	197, 64	   ,
	81, 181	   ,
	46, 217	   ,
	12, 280	   ,
	8, 302	   ,
	8, 419	   ,
	24, 426	   ,
	24, 445	   ,
	16, 451	   ,
	15, 644	   ,
	47, 676	   ,
	47, 696	   ,
	8, 735	   ,
	8, 897	   ,
	18, 908	   ,
	180, 986   ,
	193, 999   ,
	193, 1088  ,
	399, 1088  ,
	399, 1003  ,
	410, 989   ,
	575, 906   ,
	588, 893   ,
	588, 721   ,
	526, 659   ,
	526, 598   ,
	543, 574   ,
	589, 485   ,
	589, 389   ,
	573, 372   ,
	524, 186   ,
	522, 157   ,
	489, 154   ,
	487, 102   ,
	503, 104   ,
	538, 133   ,
	574, 188   ,
	596, 268   ,
	595, 975   ,
	636, 975   ,
	635, 252   ,
	621, 182   ,
	598, 138   ,
	571, 104   ,
	515, 49	   ,
	454, 19	   ,
	384, 5	   
	};

	int Obj01[5+5] = {
	93, 723  ,
	108, 722 ,
	155, 836 ,
	153, 848 ,
	92, 831  
	};

	int Obj02[5+5] = {
	486, 724 ,
	439, 838 ,
	447, 848 ,
	502, 831 ,
	503, 724 
	};

	int Obj03[6+6] = {
	51, 748   ,
	55, 864   ,
	174, 907  ,
	162, 926  ,
	53, 873   ,
	45, 861   
	};

	int Obj04[7+7] = {
	546, 746,
	540, 862,
	530, 869,
	420, 906,
	434, 928,
	542, 873,
	551, 862
	};

	int Obj05[8+8] = {
	293, 118  ,
	307, 118  ,
	315, 125  ,
	315, 166  ,
	307, 173  ,
	294, 173  ,
	284, 166  ,
	284, 125  
	};

	int Obj06[8+8] = {
	363, 128,
	374, 128,
	383, 135,
	383, 175,
	374, 182,
	363, 182,
	352, 175,
	352, 135
	};

	int Obj07[8+8] = {
	430, 118 ,
	443, 118 ,
	451, 126 ,
	451, 165 ,
	444, 172 ,
	430, 172 ,
	420, 166 ,
	420, 126 
	};

	int Obj08[27+27] = {
	226, 103 ,
	90, 240  ,
	68, 272  ,
	57, 304  ,
	60, 322  ,
	121, 445 ,
	126, 441 ,
	67, 324  ,
	70, 306  ,
	89, 297  ,
	105, 302 ,
	154, 401 ,
	159, 396 ,
	101, 282 ,
	92, 279  ,
	91, 251  ,
	102, 233 ,
	114, 240 ,
	187, 166 ,
	181, 155 ,
	193, 141 ,
	205, 142 ,
	229, 153 ,
	242, 153 ,
	248, 146 ,
	248, 105 ,
	242, 102 
	};

	int Obj09[8] = {
	532, 457,
	491, 535,
	509, 543,
	550, 462
	};

	int Bug01[6] = {
	93, 820  ,
	93, 735  ,
	117, 791 
	};

	int Bug02[6] = {
	540, 458,
	495, 536,
	507, 538
	};

	int Bug03[6] = {
	495, 723,
	475, 783,
	498, 786
	};

	

	App->renderer->camera.x = App->renderer->camera.y = 0;

	minAngleLeft = 0.0f;
	maxAngleLeft = 65.0f;
	angleMarginLeft = 10.0f;
	angularSpeedLeft = 14.0f;

	minAngleRight = 0.0f;
	maxAngleRight = 65.0f;
	angleMarginRight = 10.0f;
	angularSpeedRight = 14.0f;


	// Textures
	circle = App->textures->Load("pinball/icons8-golf-ball-96 (1).png"); // Ball sprite that does not work
	
	fliper_left = App->textures->Load("pinball/leftFliper.png");
	fliper_right = App->textures->Load("pinball/flipers02.png");
	map = App->textures->Load("pinball/map.png");

	// fx
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	ball_lost_fx = App->audio->LoadFx("pinball/ball_lost.wav");
	win_fx = App->audio->LoadFx("pinball/win.wav");
	hitmarker_fx = App->audio->LoadFx("pinball/HITMARKER.wav");
	sonic_fx= App->audio->LoadFx("pinball/SonicEarrape.wav");
	wasted_fx= App->audio->LoadFx("pinball/GTA-V-WastedBusted-Sound-Effect.wav");
	sadforloosing_fx= App->audio->LoadFx("pinball/2SAD4ME.wav");
	surprisem_fx= App->audio->LoadFx("pinball/Suprise-Motherfcker-Sound-Effect.wav");

	// -1 Neutral
	// 0 Ball
	// 1 Loose Ball
	// 2 Win
	// 3 ricochet
	// 4 Map, static objects 
	// 5 flippers

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0,map_, 100));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj01, 10));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj02, 10));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj03, 12));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj04, 14));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj05, 16));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj06, 16));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj07, 16));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj08, 27+27));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Obj09, 8));
	mapStaticBodies.getLast()->data->id = 4;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Bug01, 6));
	mapStaticBodies.getLast()->data->id = -1;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Bug02, 6));
	mapStaticBodies.getLast()->data->id = -1;
	mapStaticBodies.getLast()->data->listener = this;

	mapStaticBodies.add(App->physics->CreateStaticChain(0, 0, Bug03, 6));
	mapStaticBodies.getLast()->data->id = -1;
	mapStaticBodies.getLast()->data->listener = this;



	lives = 3;
	win_con = false;
	game_end = false;
	spawn_ball = false;
	end_rect = { 135, 412, 320, 200 };

	sensor_loss = App->physics->CreateRectangleSensor(300, 1090, 220, 10);
	sensor_loss->id = 1;

	sensor_win = App->physics->CreateRectangleSensor(90, 320, 20, 20);
	sensor_win->id = 2;

	ricochet01 = App->physics->CreateCircle(254, 270, 47);
	ricochet01->id = 3;
	ricochet01->body->SetType(b2_staticBody);

	ricochet02 = App->physics->CreateCircle(368, 367, 47);
	ricochet02->id = 3;
	ricochet02->body->SetType(b2_staticBody);


	fliperLeft = App->physics->CreateChain(180, 922, flipers01, 16);
	fliperLeft->body->SetType(b2_kinematicBody);
	fliperLeft->id = 5;

	fliperRight = App->physics->CreateChain(413, 921, flipers02, 14);
	fliperRight->body->SetType(b2_kinematicBody);
	fliperRight->id = 5;



	return ret;
}

//Donde creas la definicion, en el start de la scene verdad?

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	App->renderer->Blit(map, 0, 0, nullptr, 1.0f, 0, 0);
	App->renderer->Blit(fliper_left, 164, 908, nullptr, 1, fliperLeft->body->GetAngle() / DEGTORAD, 10, 17);
	App->renderer->Blit(fliper_right, 331, 905, nullptr, 1, fliperRight->body->GetAngle() / DEGTORAD, 82, 16);
	

	if (lives == 0) {
		game_end = true;
		win_con = true;
	}

	if (!game_end)
	{

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			ray_on = !ray_on;
			ray.x = App->input->GetMouseX();
			ray.y = App->input->GetMouseY();
		}

		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN /*|| spawn_ball == true*/) // Spawn a ball where it should be ath the start
		{
			circles.add(App->physics->CreateCircle(616, 940, 16));
			circles.getLast()->data->id = 0;
			circles.getLast()->data->listener = this;
			

			//spawn_ball = false;

		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) // Spawn a ball on the mouse
		{
			circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 16));
			circles.getLast()->data->id = 0;
			circles.getLast()->data->listener = this;
		}

		// Left fliper 

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_STATE::KEY_REPEAT)
		{
			if (fliperLeft->body->GetAngle() - DEGTORAD * angularSpeedLeft > (-DEGTORAD) * maxAngleLeft)
			{
				fliperLeft->body->SetAngularVelocity(-angularSpeedLeft);
			}

			if (fliperLeft->body->GetAngle() - DEGTORAD * angularSpeedLeft < (-DEGTORAD) * maxAngleLeft)
			{
				fliperLeft->body->SetAngularVelocity(0.0f);
			}
		}
		else
		{

			if (fliperLeft->body->GetAngle() < 0.0f)
			{
				if (fliperLeft->body->GetAngle() < DEGTORAD * minAngleLeft + DEGTORAD * angleMarginLeft)
				{
					fliperLeft->body->SetAngularVelocity(angularSpeedLeft);
				}

			}

			if (fliperLeft->body->GetAngle() + DEGTORAD * angularSpeedLeft > DEGTORAD * minAngleLeft + DEGTORAD * angleMarginLeft)
			{
				fliperLeft->body->SetAngularVelocity(0.0f);
			}
		}

		// Right fliper 

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_STATE::KEY_REPEAT)
		{
			if (fliperRight->body->GetAngle() + DEGTORAD * angularSpeedRight < DEGTORAD * maxAngleRight)
			{
				fliperRight->body->SetAngularVelocity(angularSpeedRight);
			}

			if (fliperRight->body->GetAngle() + DEGTORAD * angularSpeedRight > DEGTORAD * maxAngleRight)
			{
				fliperRight->body->SetAngularVelocity(0.0f);
			}
		}
		else
		{

			if (fliperRight->body->GetAngle() > 0.0f)
			{
				if (fliperRight->body->GetAngle() > DEGTORAD * minAngleRight - DEGTORAD * angleMarginRight)
				{
					fliperRight->body->SetAngularVelocity(-angularSpeedRight);
				}
			}

			if (fliperRight->body->GetAngle() - DEGTORAD * angularSpeedRight < DEGTORAD * minAngleRight - DEGTORAD * angleMarginRight)
			{
				fliperRight->body->SetAngularVelocity(0.0f);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			App->physics->CreateSpring(App->input->GetMouseX(), App->input->GetMouseY());

		}
			// Prepare for raycast ------------------------------------------------------

			iPoint mouse;
			mouse.x = App->input->GetMouseX();
			mouse.y = App->input->GetMouseY();
			int ray_hit = ray.DistanceTo(mouse);

			fVector normal(0.0f, 0.0f);

			// All draw functions ------------------------------------------------------
			p2List_item<PhysBody*>* c = circles.getFirst();

			while (c != NULL)
			{
				int x, y;
				c->data->GetPosition(x, y);
				//if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
				App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
				c = c->next;
			}

			c = mapStaticBodies.getFirst();

		
			// ray -----------------
			if (ray_on == true)
			{
				fVector destination(mouse.x - ray.x, mouse.y - ray.y);
				destination.Normalize();
				destination *= ray_hit;

				App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

				if (normal.x != 0.0f)
					App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
			}
		
		
	}
	else if (game_end == true && win_con == true)
	{

		App->renderer->DrawQuad(end_rect, 0, 0, 0, 240);
		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
		{
			win_con = false;
			game_end = false;
			lives = 3;
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
	if (bodyB==nullptr)
	{
		
	}
	else
	{
		if ((bodyA->id == 0) && (bodyB->id == 1))
		{
			
			App->audio->PlayFx(ball_lost_fx);
			bodyA->body->SetAwake(false);
				//bodyA->body->SetActive(false);
			
			//TODO delete the ball still does not work, fatal error
			// 
			//App->physics->GetWorld()->DestroyBody(bodyA->body);
			//delete bodyA;
			

			lives -= 1;
			spawn_ball = true;
		}
		else if ((bodyA->id == 0) && (bodyB->id == 2))
		{
			App->audio->PlayFx(win_fx);
			bodyA->body->SetAwake(false); //TODO delete the ball and send to win screen
			win_con = true;
			game_end = true;
		}
		else if ((bodyA->id == 0) && (bodyB->id == 3))
		{
			//App->audio->PlayFx(bonus_fx);
			int multi = 15;
			b2Vec2 direction;
			direction = (bodyA->body->GetWorldCenter()) - (bodyB->body->GetWorldCenter()) ; 
			direction = { direction.x * multi,direction.y * multi };
			bodyA->body->SetLinearVelocity(direction);
			App->audio->PlayFx(bonus_fx);
			//ApplyForce(direction, bodyA->body->GetWorldCenter(), true);

			//TODO sum points

		}
		else if ((bodyA->id == 0) && (bodyB->id == 5))
		{
			App->audio->PlayFx(hitmarker_fx);
			
		}
	}
	
}
