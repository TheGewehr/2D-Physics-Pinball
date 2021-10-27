#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleLoadingScreen : public Module
{
public:
	ModuleLoadingScreen(Application* app, bool start_enabled = true);
	~ModuleLoadingScreen();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	SDL_Texture* map = nullptr;
	bool fade;
};
