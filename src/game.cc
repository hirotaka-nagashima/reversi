//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "game.h"
#include "board.h"
#include "human.h"
#include "ai.h"

Game::Game() : board_(NULL), human_(NULL), ai_(NULL) {
}

Game::~Game() {
  if (board_ != NULL)
    delete board_;
  if (human_ != NULL)
    delete human_;
  if (ai_ != NULL)
    delete ai_;
}

void Game::Initialize() {
  graphic_.Initialize();
}

void Game::Terminate() {
  graphic_.Terminate();
}

void Game::Play() {
  // Make a board.
  board_ = new Board();
  board_->Initialize();

  // Make players.
  const Board::Color kHumanTurn = graphic_.InputHumanTurn();
  const Board::Color kAiTurn = Board::Reverse(kHumanTurn);
  human_ = new Human(kHumanTurn);
  ai_ = new Ai(kAiTurn);

  // Play reversi.
  for (Board::Color turn = Board::kBlack; !board_->IsEnd();
       turn = Board::Reverse(turn)) {
    graphic_.DisplayBoard(*board_, turn, kHumanTurn);

    // Pass as needed.
    if (board_->IsPass(turn)) {
      graphic_.DisplayPass();
      continue;
    }

    // Place a piece.
    int position = (turn == kHumanTurn) ?
        human_->GetPosition(*board_, graphic_) : ai_->GetPosition(*board_);
    board_->PlacePiece(position, turn);
  }
  graphic_.DisplayResult(*board_, kHumanTurn);
}