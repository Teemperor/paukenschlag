#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <PlayerViewport.h>
#include <Level.h>
#include <Ground.h>
#include <Crate.h>
#include <Character.h>
#include <Guard.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    PlayerViewport viewport(window);

    Level level;
    new Ground(level, 300, 600);
    new Crate(level, 100, 100);
    new Character(level, 250, 250);

    new Guard(level, 400, 800);
    level.setViewport(viewport);

    while (window.isOpen())
    {
        viewport.apply();

        window.clear(sf::Color::Black);

        level.render(viewport);
        viewport.renderEffects(level);
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

