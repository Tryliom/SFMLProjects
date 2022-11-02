#include "GameController.h"

#include "Assets.h"
#include "Random.h"
#include "ShapeAnimation.h"
#include "TextAnimation.h"

GameController::GameController(sf::RenderWindow& window)
	: _player( sf::Vector2f( window.getSize().x / 2, window.getSize().y - 50 ) )
{
	_width = static_cast<float>(window.getSize().x);
	_height = static_cast<float>(window.getSize().y);
	_life = 3;
	_score = 0;
	_ballsLeft = 3;
	_balls.emplace_back();
	_animations = {};
	_ultimateCharge = 0.0f;

	const auto& backgroundTexture = Assets::GetInstance().GetTexture(Asset::BACKGROUND);
	_background.setSize(sf::Vector2f(_width, _height));
	_background.setTexture(&backgroundTexture);

	_font.loadFromFile("data/font/pixelmix.ttf");

	createBricks();
	createWalls(window);

	_music.openFromFile("data/sound/main_theme.wav");
	_music.setVolume(50);
	_music.play();
}

void GameController::Update(const sf::Time elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_player.MoveLeft(elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_player.MoveRight(elapsed);
	}
	else
	{
		_player.ResetDirection();
	}

	if (_life != 0)
	{
		_player.Update(elapsed);
	}

	if (_player.IsColliding(_leftWall))
	{
		_player.Stop(_leftWall);
	}
	else if (_player.IsColliding(_rightWall))
	{
		_player.Stop(_rightWall);
	}

	for (auto& ball : _balls)
	{
		ball.Update(elapsed);

		if (ball.IsMoving())
		{
			for (Bar& bar : _player.GetBars())
			{
				if (ball.IsColliding(bar.GetBar()))
				{
					createSparks(ball.GetPosition());
					ball.Bounce(bar);
					playSound(Audio::BOUNCE);
				}
			}

			if (ball.IsColliding(_topWall))
			{
				createSparks(ball.GetPosition());
				ball.Bounce(_topWall, Direction::UP);
				playSound(Audio::BOUNCE);
			}

			if (ball.IsColliding(_leftWall))
			{
				createSparks(ball.GetPosition());
				ball.Bounce(_leftWall, Direction::LEFT);
				playSound(Audio::BOUNCE);
			}

			if (ball.IsColliding(_rightWall))
			{
				createSparks(ball.GetPosition());
				ball.Bounce(_rightWall, Direction::RIGHT);
				playSound(Audio::BOUNCE);
			}

			for (auto& brick : _bricks)
			{
				if (ball.IsColliding(brick.GetShape()))
				{
					createSparks(brick.GetShape().getPosition());
					ball.Bounce(brick.GetShape());
					brick.Break();
					_score += 10;

					playSound(Audio::HIT);

					_animations.emplace_back(new ShapeAnimation(brick.GetShape(), sf::Time(sf::seconds(0.5f))));

					sf::Text text;
					text.setFont(_font);
					text.setString("+10");
					text.setCharacterSize(12);
					text.setFillColor(sf::Color::White);
					text.setOutlineColor(sf::Color::Black);
					text.setOutlineThickness(1.0f);
					text.setPosition(brick.GetShape().getPosition() + brick.GetShape().getSize() / 2.0f);
					text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

					_animations.emplace_back(new TextAnimation(text, sf::Time(sf::seconds(0.5f))));

					if (_ultimateCharge < 1.0f)
					{
						_ultimateCharge += 0.03f;
					}
				}
			}
		}
		else
		{
			ball.SetPosition(_player.GetBallPosition() + sf::Vector2f(0, -ball.GetRadius()));
		}
	}

	if (_balls.empty() && _life != 0)
	{
		_life--;

		if (_life != 0)
		{
			_ballsLeft = 3;
			_balls.emplace_back();
		}
		else
		{
			playSound(Audio::LOSE);
		}
	}

	if (_bricks.empty())
	{
		_life++;
		_ballsLeft = 3;
		_balls = {};
		_balls.emplace_back();
		createBricks();
	}

	for (auto& spark: _sparks)
	{
		spark.Update(elapsed);
	}

	for (const auto& animation : _animations)
	{
		animation->Update(elapsed);
	}

	// Delete all objects that have expired
	_animations.erase(std::remove_if(_animations.begin(), _animations.end(), [](const Animation* animation)
		{
			return !animation->IsAlive();
		}
	), _animations.end());

	_sparks.erase(std::remove_if(_sparks.begin(), _sparks.end(), [](const Spark& spark)
		{
			return !spark.IsAlive();
		}
	), _sparks.end());

	_bricks.erase(std::remove_if(_bricks.begin(), _bricks.end(), [](const Brick& brick)
		{
			return brick.IsDestroyed();
		}
	), _bricks.end());

	_balls.erase(std::remove_if(_balls.begin(), _balls.end(), [this](const Ball& ball)
		{
			return ball.GetPosition().y > _height + ball.GetRadius() * 3 || ball.GetPosition().y < 0 || ball.GetPosition().x < 0;
		}
	), _balls.end());
}

void GameController::Draw(sf::RenderWindow& window) const
{
	window.draw(_background);
	window.draw(_player);

	for (const auto& spark : _sparks)
	{
		window.draw(spark);
	}

	for (const auto& brick : _bricks)
	{
		window.draw(brick);
	}

	for (const auto* animation : _animations)
	{
		window.draw(*animation);
	}

	for (const auto& ball : _balls)
	{
		window.draw(ball);
	}

	window.draw(_topWall);

	drawUltimateBar(window);

	sf::Text scoreText;
	scoreText.setFont(_font);
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 4);
	scoreText.setString(std::to_string(_score) + " pts");

	window.draw(scoreText);

	sf::Text lifeText;
	lifeText.setFont(_font);
	lifeText.setCharacterSize(16);
	lifeText.setFillColor(sf::Color::White);
	lifeText.setString("Life: " + std::to_string(_life));
	lifeText.setPosition(_width - lifeText.getGlobalBounds().width - 10, 4);

	window.draw(lifeText);

	if (_life == 0)
	{
		sf::Text gameOverText;
		gameOverText.setFont(_font);
		gameOverText.setCharacterSize(30);
		gameOverText.setFillColor(sf::Color::Black);
		gameOverText.setOutlineColor(sf::Color::White);
		gameOverText.setOutlineThickness(2);
		gameOverText.setString("GAME OVER");
		gameOverText.setPosition(_width / 2 - gameOverText.getGlobalBounds().width / 2, _height / 2 - gameOverText.getGlobalBounds().height / 2);

		window.draw(gameOverText);
	}
}

void GameController::CheckInput(const sf::Event event, sf::RenderWindow& window)
{
	if (!hasLost())
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				launchBall();
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				launchBall();
			}
			else if (event.mouseButton.button == sf::Mouse::Right && _ultimateCharge >= 1.0f)
			{
				useUltimate();
			}
		}

		if (event.type == sf::Event::MouseMoved)
		{
			// Update player with the mouse position
			const float size = _player.GetBars()[0].GetBar().getSize().x / 2;
			int x = event.mouseMove.x;

			if (x < 0)
			{
				x = 0;
			}
			else if (x + size > _width)
			{
				x = _width - size;
			}
		
			_player.SetPosition(x - size);
		}

		// if the mouse is inside the window, hide the cursor
		if (event.type == sf::Event::MouseEntered)
		{
			window.setMouseCursorVisible(false);
		}

		if (event.type == sf::Event::MouseLeft)
		{
			window.setMouseCursorVisible(true);
		}
	}
}

void GameController::launchBall()
{
	for (auto& ball : _balls)
	{
		if (!ball.IsMoving())
		{
			float velocity = _player.GetVelocity();

			if (velocity == 0.0f)
			{
				velocity = Random::GetFloat(200.0f, 400.0f);
			}

			ball.Launch(sf::Vector2f(velocity, -400.0f));
			_ballsLeft--;

			if (_ballsLeft > 0)
			{
				_balls.emplace_back();
			}

			break;
		}
	}
}

void GameController::createBricks()
{
	const int nbBrickOnWidth = static_cast<int>((_width - 2 * 30) / BRICK_WIDTH);
	const int nbBrickOnHeight = static_cast<int>(_height / 3 / BRICK_HEIGHT);
	const float brickMargin = ((_width - 2 * 30) - nbBrickOnWidth * BRICK_WIDTH) / (nbBrickOnWidth - 1);

	// Create bricks
	for (int w = 0; w < nbBrickOnWidth; w++)
	{
		for (int h = 0; h < nbBrickOnHeight; h++)
		{
			_bricks.emplace_back(Brick(sf::Vector2f(
				30.0f + (BRICK_WIDTH + brickMargin) * w,
				80.0f + (BRICK_HEIGHT + brickMargin) * h
			)));
		}
	}
}

void GameController::createWalls(const sf::RenderWindow& window)
{
	const sf::Vector2u size = window.getSize();

	_topWall = sf::RectangleShape(sf::Vector2f(size.x + 100, 24 + 50));
	_topWall.setPosition(-50, -50);
	_topWall.setFillColor(sf::Color(0, 0, 0, 200));

	_leftWall = sf::RectangleShape(sf::Vector2f(20, size.y * 2));
	_leftWall.setPosition(-20, 24);
	_leftWall.setFillColor(sf::Color::Transparent);

	_rightWall = sf::RectangleShape(sf::Vector2f(20, size.y * 2));
	_rightWall.setPosition(size.x, 24);
	_rightWall.setFillColor(sf::Color::Transparent);
}

void GameController::createSparks(const sf::Vector2f& position)
{
	for (int i = 0; i < 15; i++)
	{
		_sparks.emplace_back(Spark(
			position, 
			sf::Vector2f(Random::GetFloat(-100.0f, 100.0f), Random::GetFloat(-100.0f, 100.0f)), 
			sf::Color::White, 
			sf::Time(sf::seconds(0.5f))
		));
	}
}

void GameController::playSound(const Audio audio)
{
	_sounds.setBuffer(Assets::GetInstance().GetSound(audio));
	_sounds.play();
}

void GameController::drawUltimateBar(sf::RenderWindow& window) const
{
	sf::RectangleShape ultimateBackgroundBar(sf::Vector2f(200, 20));
	ultimateBackgroundBar.setPosition(window.getSize().x / 2 - 100, 4);
	ultimateBackgroundBar.setFillColor(sf::Color::Black);
	ultimateBackgroundBar.setOutlineColor(sf::Color::White);
	ultimateBackgroundBar.setOutlineThickness(2);

	window.draw(ultimateBackgroundBar);

	sf::RectangleShape ultimateBar(sf::Vector2f(200.0f * _ultimateCharge, 20));
	ultimateBar.setPosition(window.getSize().x / 2 - 100, 4);
	ultimateBar.setFillColor(sf::Color(255, 255, 255, 100));

	window.draw(ultimateBar);

	if (_ultimateCharge >= 1.0f)
	{
		sf::Text ready;
		ready.setFont(_font);
		ready.setString("READY");
		ready.setCharacterSize(16);
		ready.setFillColor(sf::Color::White);
		ready.setOrigin(ready.getLocalBounds().width / 2, 0);
		ready.setPosition(window.getSize().x / 2, 6);

		window.draw(ready);
	}
}

void GameController::useUltimate()
{
	_ultimateCharge = 0.0f;

	// Create 3 balls for every balls going in random directions
	std::vector<Ball> ballsToAdd;
	
	for (auto& ball : _balls)
	{
		if (ball.IsMoving())
		{
			for (int i = 0; i < 2; i++)
			{
				ballsToAdd.emplace_back();
				ballsToAdd.back().SetPosition(ball.GetPosition());
				ballsToAdd.back().Launch(sf::Vector2f(Random::GetFloat(-500.0f, 500.0f), Random::GetFloat(-500.0f, -300.0f)));
			}
		}
	}

	_balls.insert(_balls.end(), ballsToAdd.begin(), ballsToAdd.end());
}
