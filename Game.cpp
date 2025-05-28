#include "Game.hpp"
#include <cmath>

class Node : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Node(float x, float y) : position(x, y), active(false) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        // Nodes are static unless activated
    }

    void render(sf::RenderWindow& window) const override {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void rotate() override {} // Nodes don't rotate
    bool isActive() const override { return active; }
    void setActive(bool state) { active = state; shape.setFillColor(state ? sf::Color::Green : sf::Color::Red); }
};

class Link : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    int rotation; // 0: horizontal, 1: vertical
    bool active;

public:
    Link(float x, float y) : position(x, y), rotation(0), active(true) {
        shape.setSize(sf::Vector2f(50.f, 10.f));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        // Update position based on rotation
        shape.setPosition(position);
        shape.setRotation(rotation * 90.f);
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void rotate() override { rotation = (rotation + 1) % 2; }
    bool isActive() const override { return active; }
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), stability(0.f), isActive(false) {
    grid.resize(5, std::vector<std::unique_ptr<Entity>>(5));
    // Place nodes
    grid[1][1] = std::make_unique<Node>(300.f, 200.f);
    nodePositions.push_back({1, 1});
    grid[3][3] = std::make_unique<Node>(400.f, 300.f);
    nodePositions.push_back({3, 3});
    grid[2][4] = std::make_unique<Node>(450.f, 250.f);
    nodePositions.push_back({2, 4});
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::LControl && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                grid.clear();
                grid.resize(5, std::vector<std::unique_ptr<Entity>>(5));
                grid[1][1] = std::make_unique<Node>(300.f, 200.f);
                nodePositions = {{1, 1}};
                grid[3][3] = std::make_unique<Node>(400.f, 300.f);
                nodePositions.push_back({3, 3});
                grid[2][4] = std::make_unique<Node>(450.f, 250.f);
                nodePositions.push_back({2, 4});
                stability = 0.f;
                isActive = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Enter) {
                isActive = !isActive;
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Space && !grid[cursorPos.y][cursorPos.x]) {
                grid[cursorPos.y][cursorPos.x] = std::make_unique<Link>(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
            } else if (event.key.code == sf::Keyboard::R && grid[cursorPos.y][cursorPos.x]) {
                grid[cursorPos.y][cursorPos.x]->rotate();
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (!isActive) return;

    // Update entities
    for (auto& row : grid) {
        for (auto& entity : row) {
            if (entity) entity->update(deltaTime);
        }
    }

    // Calculate stability
    stability = 0.f;
    for (const auto& pos : nodePositions) {
        if (!dynamic_cast<Node&>(*grid[pos.y][pos.x]).isActive()) {
            // Check connections
            bool connected = false;
            // Check adjacent cells for links
            if (pos.x > 0 && grid[pos.y][pos.x - 1] && dynamic_cast<Link&>(*grid[pos.y][pos.x - 1]).isActive()) {
                if (dynamic_cast<Link&>(*grid[pos.y][pos.x - 1]).getRotation() == 0) connected = true;
            }
            if (pos.x < 4 && grid[pos.y][pos.x + 1] && dynamic_cast<Link&>(*grid[pos.y][pos.x + 1]).isActive()) {
                if (dynamic_cast<Link&>(*grid[pos.y][pos.x + 1]).getRotation() == 0) connected = true;
            }
            if (pos.y > 0 && grid[pos.y - 1][pos.x] && dynamic_cast<Link&>(*grid[pos.y - 1][pos.x]).isActive()) {
                if (dynamic_cast<Link&>(*grid[pos.y - 1][pos.x]).getRotation() == 1) connected = true;
            }
            if (pos.y < 4 && grid[pos.y + 1][pos.x] && dynamic_cast<Link&>(*grid[pos.y + 1][pos.x]).isActive()) {
                if (dynamic_cast<Link&>(*grid[pos.y + 1][pos.x]).getRotation() == 1) connected = true;
            }
            if (connected) {
                dynamic_cast<Node&>(*grid[pos.y][pos.x]).setActive(true);
            } else {
                stability += 20.f; // Penalty for unconnected nodes
            }
        }
    }

    // Add stability penalty for excessive links
    int linkCount = 0;
    for (const auto& row : grid) {
        for (const auto& entity : row) {
            if (entity && dynamic_cast<Link*>(entity.get())) linkCount++;
        }
    }
    stability += linkCount * 5.f; // Penalty for each link
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Render entities
    for (const auto& row : grid) {
        for (const auto& entity : row) {
            if (entity) entity->render(window);
        }
    }

    // Draw stability meter
    sf::RectangleShape stabilityBar(sf::Vector2f(200.f * (stability / 100.f), 20.f));
    stabilityBar.setPosition(300.f, 50.f);
    stabilityBar.setFillColor(stability > 80.f ? sf::Color::Red : sf::Color::Green);
    window.draw(stabilityBar);

    window.display();
}
