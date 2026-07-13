//
// Created by Malik Redwood on 7/12/26.
//

// prevents the file from being processed by the compiler more than once.
// as our games grows more complicated with dozens of classes, this will speed up compilation time.
#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bat {

private:

    // holds the horizontal and vertical position of the player's bat.
    Vector2f m_Position;

    // A RectangleShape object
    // visually represent the bat that appears on the screen
    // part of the SFML graphics module and used for rendering objects on the screen
    // 'RectangleShape' renders simple rectangles or squares
    RectangleShape m_Shape;

    // number of pixels per second at which the bat can move when the player decides to move it left or right
    float m_Speed = 1000.0f;
    bool m_MovingRight = false;
    bool m_MovingLeft = false;

public:
    // constructor
    // if we want the constructor to do anything other than simply create an instance,
    // then we must replace the default (unseen) constructor provided by the compiler.
    Bat(float startX, float startY);

    // getPosition() function returns a FloatRect, representing the four points that define a rectangle.
    FloatRect getPosition();
    // getShape() function returns a RectangleShape, used so that we can return to the main game loop m_shape
    RectangleShape getShape();

    // moveLeft(), moveRight(), stopLeft(), and stopRight() function are for controlling
    // if, when, and in which direction the bat will be in motion.
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    // update() function takes a Time parameter and is sued to calculate how to move the bat in each
    void update(Time dt);
};
