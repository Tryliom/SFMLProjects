#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>

enum class Asset
{
    BACKGROUND, BAR, BALL
};

enum class Audio
{
	BOUNCE, HIT, LOSE, WIN
};

class Assets
{
private:
    Assets();

    std::vector<sf::Texture> _textures;
    std::vector<sf::SoundBuffer> _fx;
public:

    Assets(const Assets&) = delete;
    Assets& operator=(const Assets&) = delete;
    Assets(Assets&&) = delete;
    Assets& operator=(Assets&&) = delete;

	sf::Texture& GetTexture(Asset asset);
	sf::SoundBuffer& GetSound(Audio audio);

    static auto& GetInstance() {
        static Assets instance;
        return instance;
    }
};