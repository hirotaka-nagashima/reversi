//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "ai.h"
#include <climits>  // INT_MIN, INT_MAX

const int Ai::kSearchDepth = 5;
const int Ai::kNumPiecesToSwitchMode = 54;

int Ai::GetPosition(const Board &board) const {
  int best_position = -1;
  for (int i = Board::GetId(0, 0), best_evaluation = INT_MIN;
       i <= Board::GetId(Board::kLength - 1, Board::kLength - 1);
       Board::Increase(&i)) {  // For each piece.
    if (!board.IsValid(i, kTurn))
      continue;

    // Simulate next board.
    Board next_board(board);
    next_board.PlacePiece(i, kTurn);
    int temp_evaluation =
        SimulateNextBoard(next_board, Board::Reverse(kTurn),
                          kSearchDepth, INT_MAX);

    // Update best position.
    if (best_evaluation < temp_evaluation) {
      best_evaluation = temp_evaluation;
      best_position = i;
    }
  }
  return best_position;
}

int Ai::Evaluate(const Board &board, const Board &prev_board) const {
  // 2nd step.
  if (kNumPiecesToSwitchMode <= board.CountAllPieces())
    return board.CountPieces(kTurn);

  // 1st step.
  int evaluation = 0;
  for (int i = Board::GetId(0, 0);
       i <= Board::GetId(Board::kLength - 1, Board::kLength - 1);
       Board::Increase(&i)) {  // For each piece.
    // Update the basic evaluation.
    if (board.cell(i) == Board::kNone) {  // There is no piece.
      if (board.IsValid(i, kTurn))
        evaluation++;
      if (board.IsValid(i, Board::Reverse(kTurn)))
        evaluation--;
    } else {  // There is a piece.
      if (Board::IsCorner(i))
        evaluation += (board.cell(i) == kTurn) ? 15 : -15;
      if (Board::IsXPoint(i))
        evaluation -= (board.cell(i) == kTurn) ? 7 : -7;
    }

    // Consider the openness.
    bool was_piece_flipped = (prev_board.cell(i) + board.cell(i) ==
                              Board::kBlack + Board::kWhite);
    if (was_piece_flipped) {
      int num_blanks = board.CountBlanksAround(i);
      evaluation -= (board.cell(i) == kTurn) ? num_blanks : -num_blanks;
    }
  }
  return evaluation;
}

int Ai::SimulateNextBoard(const Board &board, Board::Color turn,
                          int times, int best_evaluation) const {
  const int kPlayerTurn = Board::Reverse(kTurn);

  // With a min-max algorithm.
  // https://en.wikipedia.org/wiki/Minimax
  int evaluation = (turn == kTurn) ? INT_MIN : INT_MAX;
  for (int i = Board::GetId(0, 0);
       i <= Board::GetId(Board::kLength - 1, Board::kLength - 1);
       Board::Increase(&i)) {  // For each piece.
    if (!board.IsValid(i, turn))
      continue;

    // Simulate a next board.
    Board next_board(board);
    next_board.PlacePiece(i, turn);

    // Evaluate the board.
    int temp_evaluation = (1 < times) ?
        SimulateNextBoard(next_board, Board::Reverse(turn),
                          times - 1, evaluation) :
        Evaluate(next_board, board);

    // Pruning.
    if ((best_evaluation != INT_MAX) &&
        ((turn == kTurn && best_evaluation < temp_evaluation) ||
         (turn == kPlayerTurn && temp_evaluation < best_evaluation))) {
      return temp_evaluation;
    }

    // Update the evaluation.
    if ((turn == kTurn && evaluation < temp_evaluation) ||
        (turn == kPlayerTurn && temp_evaluation < evaluation)) {
      evaluation = temp_evaluation;
    }
  }

  if (evaluation == INT_MAX)
    return Evaluate(board, board);
  return evaluation;
}