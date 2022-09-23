#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <random>
#include "Globals.h"
#include "FractalGenerator.h"

int main() {
  std::srand(time(NULL));
  sf::RenderWindow window({kResolution.x, kResolution.y}, "Plasma Fractal", sf::Style::Close);
//  window.setPosition({1920 / 2 - (int) kResolution.x / 2, 1080 / 2 - (int) kResolution.y / 2});
  window.setPosition({1920 / 2 - (int) kResolution.x / 2, 0});

  FractalGenerator fractal_generator;
  fractal_generator.GenerateFractal();

  sf::Texture fractal_texture;
  fractal_texture.loadFromImage(fractal_generator.GetImage());
  sf::Sprite fractal;
  fractal.setTexture(fractal_texture);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased) {
        fractal_generator.GenerateFractal();
        fractal_texture.loadFromImage(fractal_generator.GetImage());
        fractal.setTexture(fractal_texture);
      }
    }

    window.clear();

    window.draw(fractal);

    window.display();
  }

  return 0;
}