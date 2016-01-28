#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <PlayerViewport.h>
#include <Level.h>
#include "Wall.h"
#include <Crate.h>
#include <Character.h>
#include <guard/Guard.h>
#include <Hideaway.h>
#include <goals/EscapeArea.h>
#include <Cover.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1700, 900, 32), "Test");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Level level;

    PlayerViewport viewport(&level, window);

    new Wall(level, 600, 600);
    new Cover(level, 300, 600);
    new Crate(level, 100, 100);
    new Character(level, 250, 250);
    new Hideaway(level, 150, 150);
    new EscapeArea(level, 350, 150);

    new Guard(level, 400, 800);
    level.setViewport(viewport);

    while (window.isOpen())
    {
        viewport.apply();

        window.clear(sf::Color::Black);

        level.render(viewport);
        viewport.renderEffects(level);
        viewport.renderUI();
        viewport.updateUI(1 / 60.0f);
        level.update();

        window.display();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event:: JoystickConnected)
            {
                std::cout << "joystick connected: " << event.joystickConnect.joystickId << std::endl;
            }
            else if (event.type == sf::Event::JoystickDisconnected)
            {
                std::cout << "joystick disconnected: " << event.joystickConnect.joystickId << std::endl;
            }
            else if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            break;
        }
    }

    return 0;
}

