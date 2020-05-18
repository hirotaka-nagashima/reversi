//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef REVERSI_WINDOW_H_
#define REVERSI_WINDOW_H_

#include <string>
#include <SDL.h>
#include <SDL_image.h>  // Handle images.
#include <SDL_ttf.h>    // Handle fonts.

struct Point {
  int x;
  int y;
};

class Window {
 public:
  Window(int width, int height, std::string title)
      : width_(width),
        height_(height),
        title_(title) {}

  void Initialize();
  void Terminate();
  void ClearScreen();
  // Piece of image must be 4 per row.
  void DrawGraph(SDL_Surface *image,
                 int dest_x, int dest_y,
                 int id = 0, int width = 0, int height = 0);
  void DrawString(const char *text,
                  int dest_x, int dest_y,
                  TTF_Font *font);
  void Display();
  void Sleep(int duration) const;
  void CheckClose() const;
  // Return a clicked coordinates.
  Point WaitClick() const;

 private:
  static const SDL_Color kDefaultFontColor;

  const int width_;
  const int height_;
  const std::string title_;
  SDL_Surface *video_surface_;
};

#endif  // REVERSI_WINDOW_H_