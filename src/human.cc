//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "human.h"
#include "graphic.h"

int Human::GetPosition(const Board &board, const Graphic &graphic) const {
  while (true) {
    int clicked_id = graphic.GetClickedId();
    if (board.IsValid(clicked_id, kTurn))
      return clicked_id;
  }

  // An error is occured.
  return -1;
}