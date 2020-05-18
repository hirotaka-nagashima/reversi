//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef REVERSI_GRAPHIC_H_
#define REVERSI_GRAPHIC_H_

#include "window.h"
#include "board.h"

class Graphic {
 public:
  Graphic() { window_ = new Window(450, 450, "Reversi"); }
  ~Graphic() { delete window_; }

  void Initialize();
  Board::Color InputHumanTurn();
  int GetClickedId() const;
  void DisplayResult(const Board &board, Board::Color player_turn);
  void DisplayBoard(const Board &board, Board::Color turn,
                    Board::Color player_turn);
  void DisplayPass();
  void Terminate();

 private:
  Window *window_;
  TTF_Font *font_,
           *small_font_;
  SDL_Surface *image_board_,
              *image_piece_,
              *image_overlay_;
};

#endif  // REVERSI_GRAPHIC_H_