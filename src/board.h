//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef REVERSI_BOARD_H_
#define REVERSI_BOARD_H_

class Board {
 public:
  enum Color {
    kNone,
    kBlack,
    kWhite,
  };

  // Range of "x" is from "0" to "kArrayLength".
  static int GetX(int id) { return id % kArrayLength; }
  // Range of "y" is from "0" to "kArrayLength".
  static int GetY(int id) { return id / kArrayLength; }
  // Range of "x" or "y" is from "0" to "kLength".
  static int GetId(int x, int y) {
    return (x + kSentinel) + (y + kSentinel) * kArrayLength;
  }
  // Use just at "for()".
  static void Increase(int *counter) {
    *counter += (*counter % kArrayLength == kLength) ? 3 : 1;
  }
  static bool IsCorner(int id) {
    int x = GetX(id) - 1;
    int y = GetY(id) - 1;
    bool is_x_valid = (x == 0 || x == kLength - 1);
    bool is_y_valid = (y == 0 || y == kLength - 1);
    return is_x_valid && is_y_valid;
  }
  static bool IsXPoint(int id) {
    int x = GetX(id) - 1;
    int y = GetY(id) - 1;
    bool is_x_valid = (x == 1 || x == kLength - 2);
    bool is_y_valid = (y == 1 || y == kLength - 2);
    return is_x_valid && is_y_valid;
  }
  static Color Reverse(Color color) {
    return color == kBlack ? kWhite : kBlack;
  }

  static const int kLength = 8;
  static const int kSentinel = 1;
  static const int kArrayLength = kSentinel + kLength + kSentinel;
  static const int k8Directions[8];

  void Initialize();
  void PlacePiece(int position, Color turn);
  bool IsPass(Color turn) const;
  bool IsValid(int position, Color turn) const;
  bool IsEnd() const;
  int CountPieces(Color turn) const;
  int CountAllPieces() const;
  int CountBlanksAround(int id) const;

  int cell(int id) const { return board_[id]; }

 private:
  int board_[kArrayLength * kArrayLength];
};

#endif  // REVERSI_BOARD_H_