#ifndef BaseHeader_hpp
#define BaseHeader_hpp

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <Resource.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <string>
#include <array>
#include <string.h>
#include <memory>

enum Direction{
        TOP,
        RIGHT,
        BOT,
        LEFT
    };

static float CircleRad = 19;
static float nodeDistance = 60;
static sf::Color textColorStart = sf::Color::Black;
static sf::Color textColorEnd = sf::Color::White;
static sf::Color backgroundColor(238,238,238);
static sf::Color endStateColor(255, 138, 39);

//static float M_PI = 3.14159;

#endif // BaseHeader_hpp