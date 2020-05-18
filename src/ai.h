//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef REVERSI_AI_H_
#define REVERSI_AI_H_

#include "player.h"

class Ai : public Player {
 public:
  Ai(Board::Color turn) : Player(turn) {
  }

  int GetPosition(const Board &board) const;

 private:
  static const int kSearchDepth;
  static const int kNumPiecesToSwitchMode;

  int Evaluate(const Board &board, const Board &prev_board) const;
  int SimulateNextBoard(const Board &board, Board::Color turn,
                        int times, int best_evaluation) const;
};

#endif  // REVERSI_AI_H_