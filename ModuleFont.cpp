#include "Application.h"
#include "Globals.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFont.h"

#include<string.h>


ModuleFonts::ModuleFonts(Application* app, bool start_enabled) : Module(app, start_enabled)
{


}

ModuleFonts::~ModuleFonts()
{

}

bool ModuleFonts::Start()
{


	fonts.texture = App->textures->Load("pinball/score_font_01.png");

	fonts.columns = 9;
	fonts.rows = 4;

	uint tex_w, tex_h;
	tex_w = 991;
	tex_h = 481;
	fonts.char_w = tex_w / fonts.columns;
	fonts.char_h = tex_h / fonts.rows;
	fonts.totalLength = 10;
	fonts.table = { "0123456789" };


	return true;
}

// Load new texture from file path
int ModuleFonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}


	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleFonts::UnLoad(int font_id)
{
	App->textures->Unload(fonts.texture);
	fonts.texture = nullptr;
	LOG("Successfully Unloaded BMP font_id %d", font_id);

}

void ModuleFonts::DrawText(int x, int y, const char* text) const
{
	SDL_Rect spriteRect;
	uint len = 5;

	spriteRect.w = fonts.char_w;
	spriteRect.h = fonts.char_h;

	for (uint i = 0; i < len; ++i)
	{
		// L9: DONE 2: Find the character in the table and its position in the texture, then Blit
		uint charIndex = 0;

		// Find the location of the current character in the lookup table
		for (uint j = 0; j < fonts.totalLength; ++j)
		{
			if (fonts.table[j] == text[i] + 48)
			{
				charIndex = j;
				break;
			}


		}

		spriteRect.x = spriteRect.w * (charIndex % fonts.columns);
		spriteRect.y = spriteRect.h * (charIndex / fonts.columns);
		App->renderer->Blit(fonts.texture, x, y, &spriteRect);

		// Advance the position where we blit the next character
		x += spriteRect.w;
	}
}
