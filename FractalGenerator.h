#ifndef PLASMA_FRACTAL_FRACTALGENERATOR_H
#define PLASMA_FRACTAL_FRACTALGENERATOR_H

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Globals.h"

class FractalGenerator {
 public:
  FractalGenerator();

  void GenerateFractal();

  sf::Image GetImage() { return image_; };
 private:
  std::vector<std::vector<bool>> pixels_;

  sf::Color tl_, tr_, bl_, br_;
  sf::Image image_;
  std::mt19937 gen_;
  std::uniform_int_distribution<> dis_color_;
  std::uniform_int_distribution<> dis_;
  std::uniform_real_distribution<> dis_float_;

  int rand_range_ = kStartRange;

  float GetDisposition(float depth, float width);

  void PaintAverage(float depth, sf::Vector2i first, sf::Vector2i second);

  void PaintRect(float depth, sf::Vector2i top_left, sf::Vector2i bottom_right);

  void SquareStep(float depth, sf::Vector2i pos, int delta);
  void DiamondStep(float depth, sf::Vector2i top_left, sf::Vector2i bottom_right);
};

#endif
