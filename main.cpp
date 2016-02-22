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
#include <ItemList.h>
#include <menu/IngameState.h>
#include <chrono>
#include <ai/AStarPath.h>

int main()
{
    ItemList::instance();

    sf::RenderWindow window(sf::VideoMode(1700, 900, 32), "Test");
    //window.setFramerateLimit(120);
    //window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    GameState* currentState = new IngameState(window);


    double seconds = 0;
    unsigned updates = 0;

    sf::Clock clock;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event:: JoystickConnected) {
                std::cout << "joystick connected: " << event.joystickConnect.joystickId << std::endl;
            } else if (event.type == sf::Event::JoystickDisconnected) {
                std::cout << "joystick disconnected: " << event.joystickConnect.joystickId << std::endl;
            } else if (event.type == sf::Event::Closed) {
                window.close();
            } else {
                currentState->handleEvent(event);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            break;
        }

        window.clear(sf::Color::Black);

        double deltaT = clock.restart().asSeconds();
        seconds += deltaT;

        currentState->update(deltaT);
        currentState->draw(window);

        window.display();

        AStarPath::processGlobal(std::chrono::steady_clock::now() + std::chrono::milliseconds(4));

        updates++;
        if (seconds > 1) {
            std::cout << "FPS " << (updates / seconds) << std::endl;
            seconds = 0;
            updates = 0;
        }
    }

    return 0;
}

