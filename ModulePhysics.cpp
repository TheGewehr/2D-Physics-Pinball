#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// Definition of the arrays

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

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// Creation of the map ///////////////////////////////////////////////////////////////////////////////
	// main static object

	//b2BodyDef bd;
	//ground = world->CreateBody(&bd);

	int x = 0;
	int y = 0;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* map = world->CreateBody(&body);

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
	Object01 = world->CreateBody(&intern01);

	b2BodyDef body01;
	body01.type = b2_staticBody;
	body01.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj01 = world->CreateBody(&body01);

	b2ChainShape shape01;
	b2Vec2 Vertices01[5];

	for (int i = 0; i <5 ; i++)
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
	Object02 = world->CreateBody(&intern02);


	b2BodyDef body02;
	body02.type = b2_staticBody;
	body02.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj02 = world->CreateBody(&body02);

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
	Object02 = world->CreateBody(&intern03);


	b2BodyDef body03;
	body03.type = b2_staticBody;
	body03.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj03 = world->CreateBody(&body03);

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
	Object04 = world->CreateBody(&intern04);


	b2BodyDef body04;
	body04.type = b2_staticBody;
	body04.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj04 = world->CreateBody(&body04);

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
	Object05 = world->CreateBody(&intern05);


	b2BodyDef body05;
	body05.type = b2_staticBody;
	body05.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj05 = world->CreateBody(&body05);

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
	Object06 = world->CreateBody(&intern06);


	b2BodyDef body06;
	body06.type = b2_staticBody;
	body06.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj06 = world->CreateBody(&body06);

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
	Object07 = world->CreateBody(&intern07);


	b2BodyDef body07;
	body07.type = b2_staticBody;
	body07.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj07 = world->CreateBody(&body07);

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
	Object08 = world->CreateBody(&intern08);


	b2BodyDef body08;
	body08.type = b2_staticBody;
	body08.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* obj08 = world->CreateBody(&body08);

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
	

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property


	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points

	// TODO 4: If the player releases the mouse button, destroy the joint

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}