#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape pupil;
    sf::ConvexShape eye;
    float rotation = 90;
    float angle = 0;
};

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
const  sf::Vector2f EYE_LEFT_POSITION = {300, 300};
const  sf::Vector2f EYE_RIGHT_POSITION = {550, 300};

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

sf::Vector2f toEuclidean(sf::Vector2f radius, float angle)
{
    return {
        radius.x * std::cos(angle),
        radius.y * std::sin(angle)
    };
}

void initEllips(sf::ConvexShape &ellips, const sf::Vector2f &radius)
{
    constexpr int pointCount = 200;
    ellips.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            radius.x * std::sin(angle),
            radius.y * std::cos(angle)
        };
        ellips.setPoint(pointNo, point);
    }
}

void initEye(Eye &eye, const sf::Vector2f &position)
{
    const  sf::Vector2f eyeRaius = {150.f, 80.f};
    const  sf::Vector2f pupilRadius = {30.f, 20.f};

    const sf::Color eyeColor = {255, 255, 255};
    const sf::Color pupilColor = {0, 0, 0};

    eye.eye.setFillColor(sf::Color(eyeColor));
    eye.eye.setRotation(eye.rotation);
    eye.eye.setPosition(position);

    eye.pupil.setFillColor(sf::Color(pupilColor));
    eye.pupil.setRotation(eye.rotation);
    eye.pupil.setPosition(position);
    
    initEllips(eye.eye, eyeRaius);
    initEllips(eye.pupil, pupilRadius);
}

void updatePupil(Eye &eye)
{
    const sf::Vector2f radiusMove = {45.f, 80.f};
    const sf::Vector2f eyeOffset = toEuclidean(radiusMove, eye.rotation);
    eye.pupil.setPosition(eye.eye.getPosition() + eyeOffset);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, Eye &eye)
{
    const sf::Vector2f delta = mousePosition - eye.eye.getPosition();
    eye.rotation = atan2(delta.y, delta.x);
    updatePupil(eye);
}

void redrawFrame(sf::RenderWindow &window, Eye &eye)
{
    window.setFramerateLimit(120);
    window.draw(eye.eye);
    window.draw(eye.pupil);
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "sfml3.2", sf::Style::Default, settings);

    Eye eyeLeft;
    Eye eyeRight;
    sf::Vector2f mousePosition;
    initEye(eyeLeft, EYE_LEFT_POSITION);
    initEye(eyeRight, EYE_RIGHT_POSITION);

    while (window.isOpen())
    {
        
        pollEvents(window, mousePosition);
        update(mousePosition, eyeLeft);
        update(mousePosition, eyeRight);
        redrawFrame(window, eyeLeft);
        redrawFrame(window, eyeRight);
        window.display();
    }
}

