//
// Created by Malik Redwood on 7/12/26.
//

#include "Bat.h"

// This is the constructor, and it is called when we create an object
// m_Position(var1, var2) initialize the Vector2f mPosition with the values passed into the function as parameters.
Bat::Bat(float startX, float startY) : m_Position(startX, startY) {
    m_Shape.setSize(sf::Vector2f(50, 5));
    m_Shape.setPosition(m_Position);
}

// Return a FloatRect
FloatRect Bat::getPosition() {
    // Return a FloatRect that is initialized with the coordinates of the four corners of the RectangleShape = m_Shape.
    return m_Shape.getGlobalBounds();
}

// Pass a copy of m_Shape to the calling code
// Necessary to we can draw the bat in the main function
RectangleShape Bat::getShape() {
    return m_Shape;
}

// Boolean variables to keep track of the player's current movement intentions.
void Bat::moveLeft() {
    m_MovingLeft = true;
}

// Boolean variables to keep track of the player's current movement intentions.
void Bat::moveRight() {
    m_MovingRight = true;
}

// Boolean variables to keep track of the player's current movement intentions.
void Bat::stopLeft()
{
    m_MovingLeft = false;
}

// Boolean variables to keep track of the player's current movement intentions.
void Bat::stopRight()
{
    m_MovingRight = false;
}

void Bat::update(Time dt)
{
    if (m_MovingLeft) {
        m_Position.x -= m_Speed * dt.asSeconds();
    }
    if (m_MovingRight) {
        m_Position.x += m_Speed * dt.asSeconds();
    }
    m_Shape.setPosition(m_Position);
}