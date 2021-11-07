#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFont.h"
#include "Box2D/Box2D/Box2D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = NULL;
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

	App->physics->world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	App->physics->world->SetContactListener(App->physics);

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

	// winning and losing screens
	win_screen = { 640, 50, 639, 1085 };
	lose_screen = { 0, 50, 639, 1085 };

	// spring 
	spring = App->physics->CreateRectangle(615, 989, 30, 30);
	spring->body->SetType(b2_kinematicBody);
	spring->id = 5;
	spring_calc = false;

	spring_x = 0;
	spring_y = 0;

	b2Vec2 map_[50] = {
	{344, 5	  },
	{279, 17  },
	{213, 49  },
	{197, 64  },
	{81, 181  },
	{46, 217  },
	{12, 280  },
	{8, 302	  },
	{8, 419	  },
	{24, 426  },
	{24, 445  },
	{16, 451  },
	{15, 644  },
	{47, 676  },
	{47, 696  },
	{8, 735	  },
	{8, 897	  },
	{18, 908  },
	{180, 986 },
	{193, 999 },
	{193, 1088},
	{399, 1088},
	{399, 1003},
	{410, 989 },
	{575, 906 },
	{588, 893 },
	{588, 721 },
	{526, 659 },
	{526, 598 },
	{543, 574 },
	{589, 485 },
	{589, 389 },
	{573, 372 },
	{524, 186 },
	{522, 157 },
	{489, 154 },
	{487, 102 },
	{503, 104 },
	{538, 133 },
	{574, 188 },
	{596, 268 },
	{595, 975 },
	{636, 975 },
	{635, 252 },
	{621, 182 },
	{598, 138 },
	{571, 104 },
	{515, 49  },
	{454, 19  },
	{384, 5	  }

	};

	b2Vec2 Obj01[5] = {
	{93, 723 } ,
	{108, 722} ,
	{155, 836} ,
	{153, 848} ,
	{92, 831 } 
	};

	b2Vec2 Obj02[5] = {
	{486, 724},
	{439, 838},
	{447, 848},
	{502, 831},
	{503, 724}
	};

	b2Vec2 Obj03[6] = {
	{51, 748  } ,
	{55, 864  } ,
	{174, 907 } ,
	{162, 926 } ,
	{53, 873  } ,
	{45, 861  } 
	};

	b2Vec2 Obj04[7] = {
	{546, 746},
	{540, 862},
	{530, 869},
	{420, 906},
	{434, 928},
	{542, 873},
	{551, 862}
	};

	b2Vec2 Obj05[8] = {
	{293, 118 } ,
	{307, 118 } ,
	{315, 125 } ,
	{315, 166 } ,
	{307, 173 } ,
	{294, 173 } ,
	{284, 166 } ,
	{284, 125 } 
	};

	b2Vec2 Obj06[8+8] = {
	{363, 128},
	{374, 128},
	{383, 135},
	{383, 175},
	{374, 182},
	{363, 182},
	{352, 175},
	{352, 135}
	};

	b2Vec2 Obj07[8] = {
	{430, 118} ,
	{443, 118} ,
	{451, 126} ,
	{451, 165} ,
	{444, 172} ,
	{430, 172} ,
	{420, 166} ,
	{420, 126} 
	};

	b2Vec2 Obj08[27] = {
	{226, 103} ,
	{90, 240 } ,
	{68, 272 } ,
	{57, 304 } ,
	{60, 322 } ,
	{121, 445} ,
	{126, 441} ,
	{67, 324 } ,
	{70, 306 } ,
	{89, 297 } ,
	{105, 302} ,
	{154, 401} ,
	{159, 396} ,
	{101, 282} ,
	{92, 279 } ,
	{91, 251 } ,
	{102, 233} ,
	{114, 240} ,
	{187, 166} ,
	{181, 155} ,
	{193, 141} ,
	{205, 142} ,
	{229, 153} ,
	{242, 153} ,
	{248, 146} ,
	{248, 105} ,
	{242, 102} 
	};

	b2Vec2 Obj09[4] = {
	{532, 457},
	{491, 535},
	{509, 543},
	{550, 462}
	};

	b2Vec2 Bug01[3] = {
	{93, 820  },
	{93, 735  },
	{117, 791 }
	};

	b2Vec2 Bug02[3] = {
	{540, 458},
	{495, 536},
	{507, 538}
	};

	b2Vec2 Bug03[3] = {
	{495, 723},
	{475, 783},
	{498, 786}
	};


	int x = 0;
	int y = 0;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* map = App->physics->AddToWorld(&body);
	//world->CreateBody(&body)

	b2ChainShape shape;
	b2Vec2 wVertices[50];

	for (int i = 0; i < 50; i++)
	{
		wVertices[i] = PIXEL_TO_METERS(map_[i]);
	}

	shape.CreateChain(wVertices, 50);


	b2FixtureDef fixture;
	fixture.shape = &shape;
	map->CreateFixture(&fixture);

	// Static intern objects
	/// 1

	//b2BodyDef intern01;
	//Object01 = App->physics->AddToWorld(&intern01);

	b2BodyDef body01;
	body01.type = b2_staticBody;
	body01.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj01 = App->physics->AddToWorld(&body01);

	b2ChainShape shape01;
	b2Vec2 Vertices01[5];

	for (int i = 0; i < 5; i++)
	{
		Vertices01[i] = PIXEL_TO_METERS(Obj01[i]);
	}

	shape01.CreateChain(Vertices01, 5);


	b2FixtureDef fixture01;
	fixture01.shape = &shape01;
	obj01->CreateFixture(&fixture01);
	///

	// Static intern objects
	/// 2

	//b2BodyDef intern02;
	//Object02 = App->physics->AddToWorld(&intern02);


	b2BodyDef body02;
	body02.type = b2_staticBody;
	body02.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj02 = App->physics->AddToWorld(&body02);

	b2ChainShape shape02;
	b2Vec2 Vertices02[5];

	for (int i = 0; i < 5; i++)
	{
		Vertices02[i] = PIXEL_TO_METERS(Obj02[i]); ///
	}

	shape02.CreateChain(Vertices02, 5);

	b2FixtureDef fixture02;
	fixture02.shape = &shape02;
	obj02->CreateFixture(&fixture02);
	///

	// Static intern objects
	/// 3

	//b2BodyDef intern03;
	//Object03 = App->physics->AddToWorld(&intern03);


	b2BodyDef body03;
	body03.type = b2_staticBody;
	body03.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj03 = App->physics->AddToWorld(&body03);

	b2ChainShape shape03;
	b2Vec2 Vertices03[6];

	for (int i = 0; i < 6; i++)
	{
		Vertices03[i] = PIXEL_TO_METERS(Obj03[i]); ///
	}

	shape03.CreateChain(Vertices03, 6);

	b2FixtureDef fixture03;
	fixture03.shape = &shape03;
	obj03->CreateFixture(&fixture03);
	///

	// Static intern objects
	/// 4

	//b2BodyDef intern04;
	//Object04 = App->physics->AddToWorld(&intern04);


	b2BodyDef body04;
	body04.type = b2_staticBody;
	body04.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj04 = App->physics->AddToWorld(&body04);

	b2ChainShape shape04;
	b2Vec2 Vertices04[7];

	for (int i = 0; i < 7; i++)
	{
		Vertices04[i] = PIXEL_TO_METERS(Obj04[i]); ///
	}

	shape04.CreateChain(Vertices04, 7);

	b2FixtureDef fixture04;
	fixture04.shape = &shape04;
	obj04->CreateFixture(&fixture04);
	///

	// Static intern objects
	/// 5

	//b2BodyDef intern05;
	//Object05 = App->physics->AddToWorld(&intern05);


	b2BodyDef body05;
	body05.type = b2_staticBody;
	body05.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj05 = App->physics->AddToWorld(&body05);

	b2ChainShape shape05;
	b2Vec2 Vertices05[8];

	for (int i = 0; i < 8; i++)
	{
		Vertices05[i] = PIXEL_TO_METERS(Obj05[i]); ///
	}

	shape05.CreateChain(Vertices05, 8);

	b2FixtureDef fixture05;
	fixture05.shape = &shape05;
	obj05->CreateFixture(&fixture05);
	///

	// Static intern objects
	/// 6

	//b2BodyDef intern06;
	//Object06 = App->physics->AddToWorld(&intern06);


	b2BodyDef body06;
	body06.type = b2_staticBody;
	body06.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj06 = App->physics->AddToWorld(&body06);

	b2ChainShape shape06;
	b2Vec2 Vertices06[8];

	for (int i = 0; i < 8; i++)
	{
		Vertices06[i] = PIXEL_TO_METERS(Obj06[i]); ///
	}

	shape06.CreateChain(Vertices06, 8);

	b2FixtureDef fixture06;
	fixture06.shape = &shape06;
	obj06->CreateFixture(&fixture06);
	///

	// Static intern objects
	/// 7

	//b2BodyDef intern07;
	//Object07 = App->physics->AddToWorld(&intern07);


	b2BodyDef body07;
	body07.type = b2_staticBody;
	body07.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj07 = App->physics->AddToWorld(&body07);

	b2ChainShape shape07;
	b2Vec2 Vertices07[8];

	for (int i = 0; i < 8; i++)
	{
		Vertices07[i] = PIXEL_TO_METERS(Obj07[i]); ///
	}

	shape07.CreateChain(Vertices07, 8);

	b2FixtureDef fixture07;
	fixture07.shape = &shape07;
	obj07->CreateFixture(&fixture07);
	///

	// Static intern objects
	/// 8


	b2BodyDef body08;
	body08.type = b2_staticBody;
	body08.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj08 = App->physics->AddToWorld(&body08);

	b2ChainShape shape08;
	b2Vec2 Vertices08[27];

	for (int i = 0; i < 27; i++)
	{
		Vertices08[i] = PIXEL_TO_METERS(Obj08[i]); ///
	}

	shape08.CreateChain(Vertices08, 27);

	b2FixtureDef fixture08;
	fixture08.shape = &shape08;
	obj08->CreateFixture(&fixture08);
	///

	// Static intern objects
	/// 9


	b2BodyDef body09;
	body09.type = b2_staticBody;
	body09.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj09 = App->physics->AddToWorld(&body09);

	b2ChainShape shape09;
	b2Vec2 Vertices09[27];

	for (int i = 0; i < 27; i++)
	{
		Vertices09[i] = PIXEL_TO_METERS(Obj09[i]); ///
	}

	shape09.CreateChain(Vertices09, 4);

	b2FixtureDef fixture09;
	fixture09.shape = &shape09;
	obj09->CreateFixture(&fixture09);
	///

	// Static intern object Bug 1

	b2BodyDef bug01;
	bug01.type = b2_staticBody;
	bug01.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* bugg01 = App->physics->AddToWorld(&bug01);

	b2ChainShape shape10;
	b2Vec2 Vertices10[3];

	for (int i = 0; i < 3; i++)
	{
		Vertices10[i] = PIXEL_TO_METERS(Bug01[i]); ///
	}

	shape10.CreateChain(Vertices10, 3);

	b2FixtureDef fixture10;
	fixture10.shape = &shape10;
	bugg01->CreateFixture(&fixture10);

	// Static intern object Bug 2

	b2BodyDef bug02;
	bug02.type = b2_staticBody;
	bug02.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* bugg02 = App->physics->AddToWorld(&bug02);

	b2ChainShape shape11;
	b2Vec2 Vertices11[3];

	for (int i = 0; i < 3; i++)
	{
		Vertices11[i] = PIXEL_TO_METERS(Bug02[i]); ///
	}

	shape11.CreateChain(Vertices11, 3);

	b2FixtureDef fixture11;
	fixture11.shape = &shape11;
	bugg02->CreateFixture(&fixture11);

	// Static intern object Bug 3

	b2BodyDef bug03;
	bug03.type = b2_staticBody;
	bug03.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* bugg03 = App->physics->AddToWorld(&bug03);

	b2ChainShape shape12;
	b2Vec2 Vertices12[3];

	for (int i = 0; i < 3; i++)
	{
		Vertices12[i] = PIXEL_TO_METERS(Bug03[i]); ///
	}

	shape12.CreateChain(Vertices12, 3);

	b2FixtureDef fixture12;
	fixture12.shape = &shape12;
	bugg03->CreateFixture(&fixture12);
	
	
	/// //////////////////////
	

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
	spring_ = App->textures->Load("pinball/spring.png");
	win_lose = App->textures->Load("pinball/win_lose.png");
	
	fliper_left = App->textures->Load("pinball/leftFliper.png");
	fliper_right = App->textures->Load("pinball/flipers02.png");
	Map = App->textures->Load("pinball/map.png");

	// fx
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	ball_lost_fx = App->audio->LoadFx("pinball/MMwhatyousay.wav");
	win_fx = App->audio->LoadFx("pinball/weed.wav");
	hitmarker_fx = App->audio->LoadFx("pinball/HITMARKER.wav");
	sonic_fx= App->audio->LoadFx("pinball/SonicEarrape.wav");
	wasted_fx= App->audio->LoadFx("pinball/GTA-V-WastedBusted-Sound-Effect.wav");
	sadforloosing_fx= App->audio->LoadFx("pinball/2SAD4ME.wav");
	surprisem_fx= App->audio->LoadFx("pinball/Suprise-Motherfcker-Sound-Effect.wav");


	// Physbody id's
	// -1 Neutral
	// 0 Ball
	// 1 Loose Ball
	// 2 Win
	// 3 ricochet
	// 4 Map, static objects 
	// 5 flippers
	// 6 sensor out
	


	score = 0;
	to_sum = 0;
	lives = 3;
	win_con = false;
	game_end = false;
	spawn_ball = true;
	end_rect = { 135, 412, 320, 200 };

	sensor_loss = App->physics->CreateRectangleSensor(300, 1090, 220, 10);
	sensor_loss->id = 1;

	sensor_win = App->physics->CreateRectangleSensor(90, 320, 20, 20);
	sensor_win->id = 2;

	sensor_out = App->physics->CreateRectangleSensor(530,90, 20, 20);
	sensor_out->id = 6;

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

	music_played=App->audio->PlayMusic("pinball/Wii Music - Gaming Background Music (HD).ogg",0.0f);

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

	App->renderer->Blit(Map, 0, 0, nullptr, 1.0f, 0, 0);
	App->renderer->Blit(fliper_left, 164, 908, nullptr, 1, fliperLeft->body->GetAngle() / DEGTORAD, 10, 17);
	App->renderer->Blit(fliper_right, 331, 905, nullptr, 1, fliperRight->body->GetAngle() / DEGTORAD, 82, 16);
	
	if (music_played == false)
	{
		music_played = App->audio->PlayMusic("pinball/Wii Music - Gaming Background Music (HD).ogg", 2.0f);
	}
	else{}
	
	
	App->font->DrawText(0, 0, score);

	if (!game_end)
	{
	
		//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		//{
		//	ray_on = !ray_on;
		//	ray.x = App->input->GetMouseX();
		//	ray.y = App->input->GetMouseY();
		//}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) // Spawn a ball where it should be ath the start
		{
			if (spawn_ball == true)
			{
				circles.add(App->physics->CreateCircle(616, 940, 16));
				circles.getLast()->data->id = 0;
				circles.getLast()->data->listener = this;

				spawn_ball = false;
			}
			
		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) // Spawn a ball on the mouse
		{
			circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 16));
			circles.getLast()->data->id = 0;
			circles.getLast()->data->listener = this;
		}

		// spring (starting to hate it)
		
		b2Vec2 pos = spring->body->GetPosition();


		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_STATE::KEY_REPEAT)
		{
			if (METERS_TO_PIXELS(pos.y) < 989 + 40)
			{
				spring->body->SetLinearVelocity(b2Vec2(0, 1));
			}
			else if (METERS_TO_PIXELS(pos.y) > 989 + 14)
			{
				spring->body->SetLinearVelocity(b2Vec2(0, 0));
			}
		}
		else
		{
			if (METERS_TO_PIXELS(pos.y) < 985)
			{
				spring->body->SetLinearVelocity(b2Vec2(0, 0));
			}
			else if (spring_calc)
			{
				spring->body->SetLinearVelocity(b2Vec2(0, 985 - METERS_TO_PIXELS(pos.y) - 5));
				spring_calc = false;
			}
			else if (!spring_calc)
			{
				spring->body->SetLinearVelocity(b2Vec2(0, 0));
				spring_calc = true;
			}

			/*if (METERS_TO_PIXELS(pos.y) > 989)
			{
				spring->body->SetLinearVelocity(b2Vec2(0, -25));
			}
			else
			{
				spring->body->SetLinearVelocity(b2Vec2(0, 0));
				spring_calc
			}*/
		}

		LOG("%i", 972 - METERS_TO_PIXELS(pos.y)); 
		LOG("%i", 972);
		LOG("%i", METERS_TO_PIXELS(pos.y));


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

			//c = mapStaticBodies.getFirst();

		
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
			
			// Drawing srping
			spring->GetPosition(spring_x, spring_y);
			App->renderer->Blit(spring_, spring_x, spring_y);
			
	}
	else if (game_end && win_con)
	{
		
		App->renderer->Blit(win_lose, 0, 0, &win_screen);
	
		
		circles.clear();

		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
		{
			win_con = false;
			game_end = false;
			lives = 3;
			Mix_HaltMusic();
			music_played = App->audio->PlayMusic("pinball/Wii Music - Gaming Background Music (HD).ogg", 2.0f);
			spawn_ball = true;

			for (b2Body* b = App->physics->world->GetBodyList(); b; b = b->GetNext())
			{
				if (b->GetType() == b2_dynamicBody)
				{
					App->physics->world->DestroyBody(b);
					break;
				}
			}

			score = 0;
			to_sum = 0;
		}
	}
	else if (game_end && !win_con)
	{
		App->renderer->Blit(win_lose, 0, 0, &lose_screen);

		//Delete balls 
		

		circles.clear();
		
		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN){
			win_con = false;
			game_end = false;
			lives = 3;
			Mix_HaltMusic();
			music_played = App->audio->PlayMusic("pinball/Wii Music - Gaming Background Music (HD).ogg", 2.0f);
			spawn_ball = true;

			for (b2Body* b = App->physics->world->GetBodyList(); b; b = b->GetNext())
			{
				if (b->GetType() == b2_dynamicBody)
				{
					App->physics->world->DestroyBody(b);
					break;
				}
			}

			score = 0;
			to_sum = 0;
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
			lives -= 1;
			spawn_ball = true;

			if (lives ==2)
			{
				App->audio->PlayFx(wasted_fx);
				bodyA->body->SetAwake(false);
			}
			else if(lives == 1)
			{
				App->audio->PlayFx(ball_lost_fx);
				bodyA->body->SetAwake(false);
			}
			else if (lives == 0)
			{
				Mix_HaltMusic();
				App->audio->PlayFx(sadforloosing_fx);
				bodyA->body->SetAwake(false);
				win_con = false;
				game_end = true;
			}
			
				//bodyA->body->SetActive(false);
			
			//TODO delete the ball still does not work, fatal error
			// 
			//App->physics->GetWorld()->DestroyBody(bodyA->body);
			//delete bodyA;
			

		}
		else if ((bodyA->id == 0) && (bodyB->id == 2))
		{
			Mix_HaltMusic();
			music_played = App->audio->PlayMusic("pinball/weed.ogg", 0.0f);
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
			App->audio->PlayFx(surprisem_fx);
			//ApplyForce(direction, bodyA->body->GetWorldCenter(), true);

			//TODO sum points
			score++;

			if (score >= 10)
			{
				score -= 10;
				to_sum++;
			}
		}
		else if ((bodyA->id == 0) && (bodyB->id == 5))
		{
			App->audio->PlayFx(hitmarker_fx);
			
		}
		else if ((bodyA->id == 0) && (bodyB->id == 6))
		{
			App->audio->PlayFx(sonic_fx);
		}
	}
	
}