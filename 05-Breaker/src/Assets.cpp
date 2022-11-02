#include "Assets.h"

Assets::Assets()
{
	_textures[static_cast<int>(Asset::BACKGROUND)].loadFromFile("data/textures/background.png");
	_textures[static_cast<int>(Asset::BAR)].loadFromFile("data/textures/bar.png");
	_textures[static_cast<int>(Asset::BALL)].loadFromFile("data/textures/ball.png");

	_fx[static_cast<int>(Audio::BOUNCE)].loadFromFile("data/sound/bounce.wav");
	_fx[static_cast<int>(Audio::HIT)].loadFromFile("data/sound/hit.wav");
	_fx[static_cast<int>(Audio::LOSE)].loadFromFile("data/sound/lose.wav");

	/*_fx.emplace_back();
	_fx.back().loadFromFile("data/sound/win.wav");*/
}

sf::Texture& Assets::GetTexture(Asset asset)
{
	return _textures[static_cast<int>(asset)];
}

sf::SoundBuffer& Assets::GetSound(Audio audio)
{
	return _fx[static_cast<int>(audio)];
}
