//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef REVERSI_HUMAN_H_
#define REVERSI_HUMAN_H_

#include "player.h"

class Graphic;

class Human : public Player {
 public:
  Human(Board::Color turn) : Player(turn) {
  }

  // Return "-1" if coordinates of the "mouse" is invalid.
  int GetPosition(const Board &board, const Graphic &graphic) const;
};

#endif  // REVERSI_HUMAN_H_