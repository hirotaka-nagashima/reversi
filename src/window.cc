//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "window.h"
#include <iostream>  // std::cerr, std::endl

const SDL_Color Window::kDefaultFontColor = {0xff, 0xff, 0xff};

void Window::Initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "ERROR: " << SDL_GetError() << std::endl;
    exit(-1);
  }
  if (TTF_Init() < 0) {
    std::cerr << "ERROR: " << TTF_GetError() << std::endl;
    exit(-1);
  }
  if (SDL_SetVideoMode(width_, height_, 16, SDL_HWSURFACE) == NULL) {
    std::cerr << "ERROR: " << SDL_GetError() << std::endl;
    exit(-1);
  }
  SDL_WM_SetCaption(title_.c_str(), title_.c_str());
  video_surface_ = SDL_GetVideoSurface();
}

void Window::Terminate() {
  SDL_FreeSurface(video_surface_);
  TTF_Quit();
  SDL_Quit();
}

void Window::ClearScreen() {
  SDL_FillRect(video_surface_, 0, 0);
}

void Window::DrawGraph(SDL_Surface *image,
                       int dest_x, int dest_y,
                       int id, int width, int height) {
  SDL_Rect src, dest;
  src.x = (id % 4) * width;
  src.y = (id / 4) * height;
  src.w = (width == 0) ? image->w : width;
  src.h = (height == 0) ? image->h : height;
  dest.x = dest_x;
  dest.y = dest_y;
  SDL_BlitSurface(image, &src, video_surface_, &dest);
}

void Window::DrawString(const char *text,
                        int dest_x, int dest_y,
                        TTF_Font *font) {
  SDL_Surface *temp_text =
      TTF_RenderUTF8_Blended(font, text, kDefaultFontColor);
  SDL_Rect src, dest;
  src.x = 0;
  src.y = 0;
  src.w = temp_text->w;
  src.h = temp_text->h;
  dest.x = dest_x;
  dest.y = dest_y;
  SDL_BlitSurface(temp_text, &src, video_surface_, &dest);
  SDL_FreeSurface(temp_text);
}

void Window::Display() {
  SDL_Flip(video_surface_);
}

void Window::Sleep(int duration) const {
  // Divide "duration" by 10 for a light processing.
  for (int i = 0; i < duration / 10; ++i) {
    SDL_Delay(10);
    CheckClose();
  }
}

void Window::CheckClose() const {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      exit(0);
  }
}

Point Window::WaitClick() const {
  while (true) {
    SDL_Event event;
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT)
      exit(0);
    if (event.type == SDL_MOUSEBUTTONUP) {
      Point point = {event.button.x, event.button.y};
      return point;
    }
  }
}