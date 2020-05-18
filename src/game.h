//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef REVERSI_GAME_H_
#define REVERSI_GAME_H_

#include "graphic.h"

class Board;
class Human;
class Ai;

class Game {
 public:
  Game();
  ~Game();

  void Initialize();
  void Terminate();
  void Play();

 private:
  Graphic graphic_;
  Board *board_;
  Human *human_;
  Ai *ai_;
};

#endif  // REVERSI_GAME_H_