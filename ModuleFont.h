#ifndef __MODULEFONTS_H__
#define __MODULEFONTS_H__

#include "Module.h"

#include "SDL\include\SDL.h"

#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font
{
	// Lookup table. All characters displayed in the same order as the texture
	char* table;

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;
};

class ModuleFonts : public Module
{
public:

	// Constructor
	ModuleFonts(Application* app, bool start_enabled = true);

	// Destructor
	~ModuleFonts();

	bool Start() override;
	// Loads a font file from a texture
	// Returns a font index from the fonts array
	// Param texturePath	- The path to the texture file
	// Param characters		- The lookup table. All characters displayed in the same order as the texture
	// Param rows			- The amount of character rows in the texture
	int Load(const char* texturePath, const char* characters, uint rows = 1);

	// Removes a font by its index
	// Unloads the texture and removes it from the fonts array
	void UnLoad(int fontIndex);

	// Create a surface from text
	void DrawText(int x, int y, const char* text) const;

	char* TransformNumberToChar(int i);

public:
	// An array to keep track and store all loaded fonts
	Font fonts;



};


#endif // __MODULEFONTS_H__