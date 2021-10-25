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
	circle = box = rick = map = NULL;
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

	
	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/icons8-golf-ball-96 (1).png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	ball_lost_fx = App->audio->LoadFx("pinball/ball_lost.wav"); // loose a ball audio
	win_fx = App->audio->LoadFx("pinball/win.wav"); // win audio

	map = App->textures->Load("pinball/map.png");

	

	sensor_loss = App->physics->CreateRectangleSensor(300,1090, 220, 10);
	sensor_loss->id = 1;

	sensor_win = App->physics->CreateRectangleSensor(90, 320, 20, 20);
	sensor_win->id = 2;

	ricochet01 = App->physics->CreateCircle(254,270,47); 
	ricochet01->id= 3;
	ricochet01->body->SetType(b2_staticBody);

	ricochet01 = App->physics->CreateCircle(368,367, 47); 
	ricochet01->id = 3;
	ricochet01->body->SetType(b2_staticBody);


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
	{93, 723  },
	{108, 722 },
	{155, 836 },
	{153, 848 },
	{92, 831  }
	};

	b2Vec2 Obj02[5] = {
	{486, 724 },
	{439, 838 },
	{447, 848 },
	{502, 831 },
	{503, 724 }
	};

	b2Vec2 Obj03[6] = {
	{51, 748   },
	{55, 864   },
	{174, 907  },
	{162, 926  },
	{53, 873   },
	{45, 861   }
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
	{293, 118  },
	{307, 118  },
	{315, 125  },
	{315, 166  },
	{307, 173  },
	{294, 173  },
	{284, 166  },
	{284, 125  }
	};

	b2Vec2 Obj06[8] = {
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
	{430, 118 },
	{443, 118 },
	{451, 126 },
	{451, 165 },
	{444, 172 },
	{430, 172 },
	{420, 166 },
	{420, 126 }
	};

	b2Vec2 Obj08[27] = {
	{226, 103  },
	{90, 240   },
	{68, 272   },
	{57, 304   },
	{60, 322   },
	{121, 445  },
	{126, 441  },
	{67, 324   },
	{70, 306   },
	{89, 297   },
	{105, 302  },
	{154, 401  },
	{159, 396  },
	{101, 282  },
	{92, 279   },
	{91, 251   },
	{102, 233  },
	{114, 240  },
	{187, 166  },
	{181, 155  },
	{193, 141  },
	{205, 142  },
	{229, 153  },
	{242, 153  },
	{248, 146  },
	{248, 105  },
	{242, 102  }
	};

	b2Vec2 Obj09[4] = {
	{532, 457 },
	{491, 535 },
	{509, 543 },
	{550, 462 }
	};

	//b2Vec2 Obj07

	// Creation of the map ///////////////////////////////////////////////////////////////////////////////
	// main static object

	//b2BodyDef bd;
	//ground = world->CreateBody(&bd);

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

	b2BodyDef intern01;
	Object01 = App->physics->AddToWorld(&intern01);

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

	b2BodyDef intern02;
	Object02 = App->physics->AddToWorld(&intern02);


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

	b2BodyDef intern03;
	Object02 = App->physics->AddToWorld(&intern03);


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

	b2BodyDef intern04;
	Object04 = App->physics->AddToWorld(&intern04);


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

	b2BodyDef intern05;
	Object05 = App->physics->AddToWorld(&intern05);


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

	b2BodyDef intern06;
	Object06 = App->physics->AddToWorld(&intern06);


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

	b2BodyDef intern07;
	Object07 = App->physics->AddToWorld(&intern07);


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

	b2BodyDef intern08;
	Object08 = App->physics->AddToWorld(&intern08);


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

	// Static intern object
	// 9
	b2BodyDef intern09;
	Object01 = App->physics->AddToWorld(&intern09);

	b2BodyDef body09;
	body09.type = b2_staticBody;
	body09.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj09 = App->physics->AddToWorld(&body09);

	b2ChainShape shape09;
	b2Vec2 Vertices09[4];

	for (int i = 0; i < 4; i++)
	{
		Vertices09[i] = PIXEL_TO_METERS(Obj09[i]);
	}

	shape09.CreateChain(Vertices09, 4);


	b2FixtureDef fixture09;
	fixture09.shape = &shape09;
	obj09->CreateFixture(&fixture09);


	return ret;
}

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



	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) // Spawn a ball where it should be ath the start
	{
		circles.add(App->physics->CreateCircle(616, 940, 16));
		circles.getLast()->data->listener = this;
		
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) // Spawn a ball on the mouse
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 16));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		//if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	/*
	b2_staticBody = 0,
		b2_kinematicBody,
		b2_dynamicBody
	*/
	
	if (bodyB==nullptr)
	{
		
	}
	else
	{
		if ((bodyA->id == 0) && (bodyB->id == 1))
		{
			
			App->audio->PlayFx(ball_lost_fx);
			bodyA->body->SetAwake(false); //TODO delete the ball and Loose a life
			//bodyA->body.

		}
		if ((bodyA->id == 0) && (bodyB->id == 2))
		{
			App->audio->PlayFx(win_fx);
			bodyA->body->SetAwake(false); //TODO delete the ball and send to win screen
		}
		if ((bodyA->id == 0) && (bodyB->id == 3))
		{
			//App->audio->PlayFx(bonus_fx);
			int multi = 20;
			b2Vec2 direction;
			direction = (bodyA->body->GetWorldCenter()) - (bodyB->body->GetWorldCenter()) ; // World or local
			direction = { direction.x * multi,direction.y * multi };
			bodyA->body->SetLinearVelocity(direction);
			App->audio->PlayFx(bonus_fx);
			//ApplyForce(direction, bodyA->body->GetWorldCenter(), true);

			//TODO sum points

		}
	}
	
}
