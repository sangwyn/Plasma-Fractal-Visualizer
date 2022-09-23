#include "FractalGenerator.h"

FractalGenerator::FractalGenerator() {
//    image_.create(kResolution.x, kResolution.y);
  gen_ = std::mt19937(time(0));
  dis_color_ = std::uniform_int_distribution<>(0, 256);
  dis_ = std::uniform_int_distribution<>(-kStartRange, kStartRange);
  dis_float_ = std::uniform_real_distribution<>(1, 5);

//    tl_ = sf::Color(255, 153, 0);
//    bl_ = sf::Color(20, 255, 0);
//    tr_ = sf::Color(255, 65, 255);
//    br_ = sf::Color(20, 247, 255);
}

void FractalGenerator::PaintRect(float depth, sf::Vector2i top_left, sf::Vector2i bottom_right) {
  if (abs(top_left.x - bottom_right.x) <= 1 || abs(top_left.y - bottom_right.y) <= 1)
    return;

  DiamondStep(depth, top_left, bottom_right);

  PaintAverage(depth, top_left, {top_left.x, bottom_right.y});
  PaintAverage(depth, top_left, {bottom_right.x, top_left.y});
  PaintAverage(depth, bottom_right, {top_left.x, bottom_right.y});
  PaintAverage(depth, bottom_right, {bottom_right.x, top_left.y});

//    int delta = abs(bottom_right.x - top_left.x) / 2;
//    SquareStep(depth, {top_left.x, (top_left.y + bottom_right.y) / 2}, delta);
//    SquareStep(depth, {bottom_right.x, (top_left.y + bottom_right.y) / 2}, delta);
//    SquareStep(depth, {(top_left.x + bottom_right.x) / 2, bottom_right.y}, delta);
//    SquareStep(depth, {(top_left.x + bottom_right.x) / 2, top_left.y}, delta);

  sf::Vector2i center((top_left.x + bottom_right.x) / 2, (top_left.y + bottom_right.y) / 2);
  PaintRect(depth + 1, top_left, center);
  PaintRect(depth + 1, {center.x, top_left.y}, {bottom_right.x, center.y});
  PaintRect(depth + 1, {top_left.x, center.y}, {center.x, bottom_right.y});
  PaintRect(depth + 1, center, bottom_right);
}

void FractalGenerator::SquareStep(float depth, sf::Vector2i pos, int delta) {
  float r = 0, g = 0, b = 0, cnt = 0;

  if (pos.x - delta >= 0 && pixels_[pos.x - delta][pos.y]) {
    ++cnt;
    sf::Color c = image_.getPixel(pos.x - delta, pos.y);
    r += c.r;
    g += c.g;
    b += c.b;
  }
  if (pos.x + delta < kResolution.x && pixels_[pos.x + delta][pos.y]) {
    ++cnt;
    sf::Color c = image_.getPixel(pos.x + delta, pos.y);
    r += c.r;
    g += c.g;
    b += c.b;
  }
  if (pos.y - delta >= 0 && pixels_[pos.x][pos.y - delta]) {
    ++cnt;
    sf::Color c = image_.getPixel(pos.x, pos.y - delta);
    r += c.r;
    g += c.g;
    b += c.b;
  }
  if (pos.y + delta < kResolution.y && pixels_[pos.x][pos.y + delta]) {
    ++cnt;
    sf::Color c = image_.getPixel(pos.x, pos.y + delta);
    r += c.r;
    g += c.g;
    b += c.b;
  }

  r /= cnt;
  g /= cnt;
  b /= cnt;

  float disposition = GetDisposition(depth, 2 * delta);
  sf::Color color((int) (r + GetDisposition(depth, 2 * delta)) % 256, (int) (g + GetDisposition(depth, 2 * delta)) % 256, (int) (b + GetDisposition(depth, 2 * delta)) % 256);
  image_.setPixel(pos.x, pos.y, color);
  pixels_[pos.x][pos.y] = true;
}

float FractalGenerator::GetDisposition(float depth, float width) {
  float range = kSharpness * width / kResolution.x;
  dis_ = std::uniform_int_distribution<>(-range, range);
  return dis_(gen_);
//  dis_ = std::uniform_int_distribution<>(-kStartRange, kStartRange);
//  return kSharpness * dis_(gen_) * width / kResolution.x / depth;
}

void FractalGenerator::DiamondStep(float depth, sf::Vector2i top_left, sf::Vector2i bottom_right) {
  sf::Color c1 = image_.getPixel(top_left.x, top_left.y), c2 = image_.getPixel(bottom_right.x, top_left.y),
      c3 = image_.getPixel(top_left.x, bottom_right.y), c4 = image_.getPixel(bottom_right.x, bottom_right.y);

  float red = (float) (c1.r + c2.r + c3.r + c4.r) / 4.0, green = (float) (c1.g + c2.g + c3.g + c4.g) / 4.0,
      blue = (float) (c1.b + c2.b + c3.b + c4.b) / 4.0;

  float disposition = GetDisposition(depth, abs(bottom_right.x - top_left.x));
//    std::cout << disposition << '\n';

  sf::Vector2i center((top_left.x + bottom_right.x) / 2, (top_left.y + bottom_right.y) / 2);
  sf::Color color((int) (red + GetDisposition(depth, abs(bottom_right.x - top_left.x))) % 256, (int) (green + GetDisposition(depth, abs(bottom_right.x - top_left.x))) % 256, (int) (blue + GetDisposition(depth, abs(bottom_right.x - top_left.x))) % 256);
  image_.setPixel(center.x, center.y, color);
  pixels_[center.x][center.y] = true;
}

void FractalGenerator::GenerateFractal() {
  image_.create(kResolution.x, kResolution.y);

//    tl_ = sf::Color::Red;
//    bl_ = sf::Color::Yellow;
//    tr_ = sf::Color::Blue;
//    br_ = sf::Color::Green;

//    tl_ = sf::Color(255, 153, 0);
//    bl_ = sf::Color(20, 255, 0);
//    tr_ = sf::Color(255, 65, 255);
//    br_ = sf::Color(20, 247, 255);

  tl_ = sf::Color(dis_color_(gen_), dis_color_(gen_), dis_color_(gen_));
  bl_ = sf::Color(dis_color_(gen_), dis_color_(gen_), dis_color_(gen_));
  tr_ = sf::Color(dis_color_(gen_), dis_color_(gen_), dis_color_(gen_));
  br_ = sf::Color(dis_color_(gen_), dis_color_(gen_), dis_color_(gen_));

  image_.setPixel(0, 0, tl_);
  image_.setPixel(0, kResolution.y - 1, bl_);
  image_.setPixel(kResolution.x - 1, 0, tr_);
  image_.setPixel(kResolution.x - 1, kResolution.y - 1, br_);

  rand_range_ = kStartRange;

  pixels_.assign(kResolution.x, std::vector<bool>(kResolution.y, false));
  pixels_[0][0] = pixels_[kResolution.x - 1][0] = pixels_[0][kResolution.y - 1] =
  pixels_[kResolution.x - 1][kResolution.y - 1] = true;

  PaintRect(1, {0, 0}, {(int) kResolution.x - 1, (int) kResolution.y - 1});
//    int res = 0;
//    for (int i = 0; i < pixels_.size(); ++i) {
//        for (int j = 0; j < pixels_[i].size(); ++j) {
//            if (!pixels_[i][j])
//                ++res;
//        }
//    }
//    std::cout << res << '\n';
}

void FractalGenerator::PaintAverage(float depth, sf::Vector2i first, sf::Vector2i second) {
  sf::Vector2i pos((first.x + second.x) / 2, (first.y + second.y) / 2);
  sf::Color c1 = image_.getPixel(first.x, first.y), c2 = image_.getPixel(second.x, second.y);
//  image_.setPixel(pos.x, pos.y, sf::Color((c1.r + c2.r) / 2 + GetDisposition(depth, std::max(abs(second.x - first.x), abs(second.y - first.y))),
//                                          (c1.g + c2.g) / 2 + GetDisposition(depth, std::max(abs(second.x - first.x), abs(second.y - first.y))),
//                                          (c1.b + c2.b) / 2 + GetDisposition(depth, std::max(abs(second.x - first.x), abs(second.y - first.y)))));
  image_.setPixel(pos.x, pos.y, sf::Color((c1.r + c2.r) / 2,
                                          (c1.g + c2.g) / 2,
                                          (c1.b + c2.b) / 2));

  pixels_[pos.x][pos.y] = true;
}
