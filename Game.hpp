#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<std::unique_ptr<Entity>>> grid; // 2D grid of entities
    sf::Vector2i cursorPos;
    float stability; // Grid stability (0 to 100)
    bool isActive;
    std::vector<sf::Vector2i> nodePositions;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
