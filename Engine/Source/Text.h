#pragma once
#include "Font.h"
#include "Renderer.h"
#include "Color.h"
#include <SDL.h>

class Text
{
public:
	Text() = default;
	Text(Font* font) : m_font{ font } {}
	~Text();

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);

	void SetFont(Font* font) { m_font = font; }

private:
	Font* m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
};