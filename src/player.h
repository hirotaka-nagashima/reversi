//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef REVERSI_PLAYER_H_
#define REVERSI_PLAYER_H_

#include "board.h"

class Player {
 public:
  Player(Board::Color turn) : kTurn(turn) {}
  virtual ~Player() {}

 protected:
  const Board::Color kTurn;
};

#endif  // REVERSI_PLAYER_H_