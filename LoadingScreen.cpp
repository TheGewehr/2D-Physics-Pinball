#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "LoadingScreen.h"
#include "ModuleFadeToBlack.h"

ModuleLoadingScreen::ModuleLoadingScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleLoadingScreen::~ModuleLoadingScreen()
{}

bool ModuleLoadingScreen::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	map = App->textures->Load("pinball/map.png");

	App->renderer->camera.x = 0;
	App->renderer->camera.y = 0;

	return ret;
}

update_status ModuleLoadingScreen::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_intro, 90);

	}
	App->renderer->Blit(map, 0, 0, nullptr, 1.0f, 0, 0);

	return UPDATE_CONTINUE;
}

update_status ModuleLoadingScreen::PostUpdate()
{
	App->renderer->Blit(map, 0, 0, nullptr, 1.0f, 0, 0);

	return UPDATE_CONTINUE;
}

bool ModuleLoadingScreen::CleanUp()
{
	LOG("Unloading Intro scene");
	SDL_free(map);

	return true;
}

