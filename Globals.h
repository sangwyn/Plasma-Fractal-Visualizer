#ifndef PLASMA_FRACTAL_GLOBALS_H
#define PLASMA_FRACTAL_GLOBALS_H

#include <SFML/Graphics.hpp>
#include <cmath>

const sf::Vector2<unsigned int> kResolution = {1025, 1025};

const int kStartRange = 196;
const float kSharpness = 90;

void Rgb2Lab(sf::Color color, float &l_s, float &a_s, float &b_s);

sf::Color Lab2Rgb(float l_s, float a_s, float b_s);

#endif
