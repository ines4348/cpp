#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;
    sf::Vector2f position = {10, 350};
    int startPositionY = position.y;
    float time = clock.getElapsedTime().asSeconds();
    float speedX = 100.f;
    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        time += dt;

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;
        const float wavePhase = time * float(2 * M_PI);
        float x = speedX * dt;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        position.x += speedX * dt;
        position.y = startPositionY + amplitudeY * std::sin(wavePhase / periodY);
        ball.setPosition(position);

        window.clear();
        window.draw(ball);
        window.display();
    }
}