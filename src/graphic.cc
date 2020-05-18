//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "graphic.h"

void Graphic::Initialize() {
  window_->Initialize();

  // Load images.
  image_board_ = IMG_Load("resources/board.png");
  image_piece_ = IMG_Load("resources/piece.png");
  image_overlay_ = IMG_Load("resources/overlay.png");
  if (!image_board_ || !image_piece_ || !image_overlay_) {
    fprintf(stderr, "ERROR: %s\n", IMG_GetError());
    exit(-1);
  }
  
  // Load fonts.
  font_ = TTF_OpenFont("resources/font.ttf", 50);
  small_font_ = TTF_OpenFont("resources/font.ttf", 25);
  if (!font_ || !small_font_) {
    fprintf(stderr, "ERROR: %s\n", TTF_GetError());
    exit(-1);
  }
}

Board::Color Graphic::InputHumanTurn() {
  window_->DrawGraph(image_board_, 0, 0);
  window_->DrawGraph(image_overlay_, 0, 0);
  window_->DrawString("The 1st move / The 2nd move", 50, 180, small_font_);
  window_->DrawString("Press 1 / 2", 150, 220, small_font_);
  window_->Display();

  while (true) {
    window_->Sleep(100);
    Uint8 *key = SDL_GetKeyState(NULL);
    if (key[SDLK_1]) return Board::kBlack;
    if (key[SDLK_2]) return Board::kWhite;
  }
}

int Graphic::GetClickedId() const {
  // Get the clicked position.
  Point clicked = window_->WaitClick();
  clicked.y = clicked.y / 50 - 1;
  clicked.x = clicked.x / 50;
  return Board::GetId(clicked.x, clicked.y);
}

void Graphic::DisplayResult(const Board &board, Board::Color player_turn) {
  DisplayBoard(board, Board::kNone, player_turn);
  window_->DrawGraph(image_overlay_, 0, 0);

  // Display scores.
  int num_blacks = board.CountPieces(Board::kBlack);
  int num_whites = board.CountPieces(Board::kWhite);
  char temp[50];
  sprintf_s(temp, "%2d - %2d", num_blacks, num_whites);
  window_->DrawString(temp, 140, 130, font_);

  // Display a comment.
  if ((player_turn == Board::kBlack && num_whites < num_blacks) ||
      (player_turn == Board::kWhite && num_blacks < num_whites)) {
    window_->DrawString("You win! :)", 110, 190, font_);
  } else if ((player_turn == Board::kBlack && num_blacks < num_whites) ||
             (player_turn == Board::kWhite && num_whites < num_blacks)) {
    window_->DrawString("You lose :(", 110, 190, font_);
  } else {
    window_->DrawString("Draw :/", 135, 190, font_);
  }

  window_->Display();

  window_->WaitClick();
}

void Graphic::DisplayBoard(const Board &board, Board::Color turn,
                           Board::Color player_turn) {
  char *turn_name[2] = {"CPU", "Your"};
  window_->DrawGraph(image_board_, 0, 0);
  window_->DrawGraph(image_piece_, 400, 0, turn, 50, 50);
  window_->DrawString(turn_name[(turn == player_turn)], 145, -5, font_);
  for (int y = 0; y < Board::kLength; ++y) {
    for (int x = 0; x < Board::kLength; ++x) {
      int id = Board::GetId(x, y);
      if ((board.cell(id) != Board::kNone) ||
          (board.IsValid(id, turn) && turn == player_turn)) {
        window_->DrawGraph(image_piece_,
                           x * 50, (y + 1) * 50,
                           board.cell(id), 50, 50);
      }
    }
  }
  window_->Display();
}

void Graphic::DisplayPass() {
  window_->DrawString("Pass", 30, -5, font_);
  window_->Display();
  window_->Sleep(1000);
}

void Graphic::Terminate() {
  SDL_FreeSurface(image_board_);
  SDL_FreeSurface(image_piece_);
  SDL_FreeSurface(image_overlay_);
  TTF_CloseFont(font_);
  TTF_CloseFont(small_font_);
  window_->Terminate();
}