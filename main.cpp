#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "UserInputManager.h"
#include "RenderingEngine.h"
#include "ICommand.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({440, 600}),  "Tetris");
    window.setFramerateLimit(60);

    sf::Clock clock;

    GameEngine gameEngine;
    UserInputManager inputManager(gameEngine);
    RenderingEngine renderingEngine(window, gameEngine);

    while (window.isOpen())
    {
        float deltaTimer = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event -> is<sf::Event::Closed>())
            {
                window.close();
            }

            if (ICommand* command = inputManager.ProcessInput(*event))
            {
                command -> Execute(gameEngine);
            }
        }

        gameEngine.Update(deltaTimer);

        renderingEngine.Render();
    }

    return 0;
}