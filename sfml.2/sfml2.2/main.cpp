#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    constexpr int pointCount = 200;
    constexpr int polarRoseTrajectoryRadius = 100;
    constexpr int polarRoseSpeed = 4;

    const sf::Vector2f polarRoseCenter = {400.f, 300.f};

    sf::Clock clock;
    float polarRoseAngleTrajectory = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Polar Rose",
        sf::Style::Default, settings);

    sf::ConvexShape polarRose;
    polarRose.setPosition(polarRoseCenter);
    polarRose.setFillColor(sf::Color(204, 153, 255));
    polarRose.setPointCount(pointCount);

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

        float deltaTime = clock.getElapsedTime().asSeconds();
        polarRoseAngleTrajectory = float(2 * (-M_PI) * deltaTime) / polarRoseSpeed;
        sf::Vector2f polarRosePosition = {
            polarRoseCenter.x + polarRoseTrajectoryRadius * std::sin(polarRoseAngleTrajectory),
            polarRoseCenter.y + polarRoseTrajectoryRadius * std::cos(polarRoseAngleTrajectory)};
        polarRose.setPosition(polarRosePosition);

        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            int polarRoseRadius = 200 * std::sin(6 * angle);
            sf::Vector2f point = {
                polarRoseRadius * std::sin(angle),
                polarRoseRadius * std::cos(angle)};
            polarRose.setPoint(pointNo, point);
        }

        window.clear();
        window.draw(polarRose);
        window.display();
    }
}