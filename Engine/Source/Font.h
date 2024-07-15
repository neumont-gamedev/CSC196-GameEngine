#pragma once
#include <SDL_ttf.h>
#include <string>

class Font
{
public:
	Font() = default;
	~Font();

	bool Load(const std::string& filename, int fontSize);

	// allow class access to private members
	friend class Text;

private:
	_TTF_Font* m_ttfFont{ nullptr };
};