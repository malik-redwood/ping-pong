//
// Created by Malik Redwood on 7/12/26.
// Last updated by Malik Redwood on 7/13/26.
//

#include "Ball.h"
#include "Bat.h"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <vector>

// Make code easier to type with "using namespace" using namespace sf;
using namespace sf;
// Make code easier to type with "using namespace" using namespace std;
using namespace std;

int main() {
    // Create a video mode object
    constexpr unsigned WINDOW_WIDTH = 1920;
    constexpr unsigned WINDOW_HEIGHT = 1080;
    const VideoMode VM({WINDOW_WIDTH, WINDOW_HEIGHT});

    // Create and open a window for the game
    RenderWindow window(VM, "Pong",Style::Default);

    // Create a view
    View gameView(FloatRect({0.f, 0.f}, {1920.f, 1080.f}));

    // Adjusts the view's viewport to preserve aspect ratio (letterboxing)
    auto updateView = [&]() {
        float windowWidth  = static_cast<float>(window.getSize().x);
        float windowHeight = static_cast<float>(window.getSize().y);
        float windowRatio  = windowWidth / windowHeight;
        float viewRatio     = 1920.f / 1080.f;

        float sizeX = 1.f, sizeY = 1.f;
        float posX = 0.f, posY = 0.f;

        if (windowRatio > viewRatio) {
            // Window is wider than the game world -> pillarbox (bars on sides)
            sizeX = viewRatio / windowRatio;
            posX = (1.f - sizeX) / 2.f;
        } else {
            // Window is taller than the game world -> letterbox (bars top/bottom)
            sizeY = windowRatio / viewRatio;
            posY = (1.f - sizeY) / 2.f;
        }

        gameView.setViewport(FloatRect({posX, posY}, {sizeX, sizeY}));
    };

    updateView();

    // set the window to use this and SFML will automatically scale the axis coordinates
    window.setView(gameView);

    int score = 0;
    int lives = 3;

    // Create a bat at the bottom center of the screen
    Bat bat(1920 / 2, 1080 - 20);

    // Create a ball
    Ball ball(1920 / 2, 0);

    // A cool retro-style font
    Font font;

    if (!font.openFromFile("fonts/DS-DIGIT.ttf")) {
        // Handle the loading error here safely
        cerr << "Failed to load font: " << endl;
    }

    // Create a Text object called HUD
    Text hud(font, "Score: 0 Lives: 3", 75);

    // Set the font to our retro-style
    hud.setFont(font);

    // Make it nice and big
    hud.setCharacterSize(75);

    // Choose a color
    hud.setFillColor(Color::White);
    hud.setPosition({20, 20});

    // Here is our clock for timing everything
    Clock clock;

    while (window.isOpen()) {
        // MANDATORY FOR MACOS: Poll events so the OS allows the window to pop up!
        while (const std::optional EVENT = window.pollEvent()) {
            // If user triggers an OS close request
            // Quit the game when the window is closed
            if (EVENT->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* resized = EVENT->getIf<sf::Event::Resized>()) {
                updateView();
            }
        }

        // Handle the player quitting
        // Escape key
        if (Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        // Pressing of the left arrow key
        if (Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            bat.moveLeft();
        }
        // Releasing of the left arrow key
        else {
            bat.stopLeft();
        }
        // Pressing of the right arrow key
        if (Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            bat.moveRight();
        }
        // Releasing of the left arrow key
        else {
            bat.stopRight();
        }

        // Handle the player input

        // Update the bat, the ball and the HUD

        // Update the delta time
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);

        // Update the HUD text
        stringstream ss;
        ss << "Score: " << score << " Lives:" << lives;
        hud.setString(ss.str());

        // Handle ball hitting the bottom
        if (ball.getPosition().position.y > WINDOW_HEIGHT) {
            ball.reboundBottom();
            lives--;
            if (lives < 1) {
                score = 0;
                lives = 3;
            }
        }

        // Handle ball hitting top
        if (ball.getPosition().position.y < 0)
        {
            ball.reboundBatOrTop();
            // Add a point to the players score
            score++;
        }

        // Handle ball hitting sides
        if (ball.getPosition().position.x < 0.f ||
            ball.getPosition().position.x + ball.getPosition().size.x > WINDOW_WIDTH)
        {
            ball.reboundSides();
        }

        // Has the ball hit the bat?
        if (ball.getPosition().findIntersection(bat.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundBatOrTop();
        }

        // Draw the bat, the ball and the HUD
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();

        }
        return 0;
    }