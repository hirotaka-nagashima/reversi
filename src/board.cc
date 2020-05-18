//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "board.h"

const int Board::k8Directions[8] = {
    -kArrayLength - 1,
    -kArrayLength,
    -kArrayLength + 1,
    -1,
    1,
    kArrayLength - 1,
    kArrayLength,
    kArrayLength + 1};

void Board::Initialize() {
  // Set sentinels.
  for (int i = 0; i < kArrayLength; ++i)
    board_[i] = -1;

  // Set the board area as "0".
  for (int i = GetId(0, 0); i <= GetId(kLength - 1, kLength - 1);
       Increase(&i)) {
    board_[i] = 0;
  }

  board_[GetId(3, 3)] = board_[GetId(4, 4)] = kWhite;
  board_[GetId(3, 4)] = board_[GetId(4, 3)] = kBlack;
}

void Board::PlacePiece(int position, Color turn) {
  if (board_[position] != kNone)
    return;

  board_[position] = turn;
  for (int i = 0; i < 8; ++i) {  // For 8 directions.
    if (board_[position + k8Directions[i]] != Reverse(turn))
      continue;

    // Check flippable.
    int temp_position, counter = 0;
    int log[10] = {0};  // Log to flip later.
    do {
      temp_position = position + k8Directions[i] * ++counter;
      log[counter - 1] = temp_position;
    } while (board_[temp_position] == Reverse(turn));

    // Flip pieces.
    if (board_[temp_position] == turn) {
      for (int j = 0; log[j + 1] != 0; ++j)
        board_[log[j]] = turn;
    }
  }
}

bool Board::IsPass(Color turn) const {
  for (int i = GetId(0, 0); i <= GetId(kLength - 1, kLength - 1);
       Increase(&i)) {
    if (board_[i] == kNone && IsValid(i, turn))
      return false;
  }
  return true;
}

bool Board::IsValid(int position, Color turn) const {
  // Out of the board.
  if (position < GetId(0, 0) || GetId(kLength - 1, kLength - 1) < position)
    return false;

  // There is a piece already.
  if (board_[position] != kNone)
    return false;

  for (int i = 0; i < 8; ++i) {  // For 8 directions.
    if (board_[position + k8Directions[i]] != Reverse(turn))
      continue;

    int temp_position;
    for (temp_position = position + k8Directions[i] * 2;
         board_[temp_position] == Reverse(turn);
         temp_position += k8Directions[i]);
    if (board_[temp_position] == turn)
      return true;
  }
  return false;
}

bool Board::IsEnd() const {
  if (IsPass(kBlack) && IsPass(kWhite))
    return true;
  for (int i = GetId(0, 0); i <= GetId(kLength - 1, kLength - 1);
       Increase(&i)) {
    if (board_[i] == kNone)
      return false;
  }
  return true;
}

int Board::CountPieces(Color turn) const {
  int num_pieces = 0;
  for (int i = GetId(0, 0); i <= GetId(kLength - 1, kLength - 1);
       Increase(&i)) {
    if (board_[i] == turn)
      num_pieces++;
  }
  return num_pieces;
}

int Board::CountAllPieces() const {
  return CountPieces(kBlack) + CountPieces(kWhite);
}

int Board::CountBlanksAround(int id) const {
  int num_blanks = 0;
  for (int i = 0; i < 8; ++i) {  // For 8 directions.
    int dest = id + k8Directions[i];
    if (cell(dest) == kNone)
      ++num_blanks;
  }
  return num_blanks;
}