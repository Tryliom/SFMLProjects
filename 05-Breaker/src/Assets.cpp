#include "Assets.h"

Assets::Assets()
{
	_textures.emplace_back();
	_textures.back().loadFromFile("data/textures/background.png");
	_textures.emplace_back();
	_textures.back().loadFromFile("data/textures/bar.png");
	_textures.emplace_back();
	_textures.back().loadFromFile("data/textures/ball.png");

	_fx.emplace_back();
	//_fx.back().loadFromFile("assets/main_theme.wav");
}

sf::Texture& Assets::GetTexture(Asset asset)
{
	return _textures[static_cast<int>(asset)];
}

sf::SoundBuffer& Assets::GetSound(Audio audio)
{
	return _fx[static_cast<int>(audio)];
}
