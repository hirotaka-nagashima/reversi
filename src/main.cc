//-----------------------------------------------------------------------------
// Copyright (c) 2015 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------
// 2016/11/06: Reconstructed with C++.
// 2015/04/20: Strengthened the AI.
// 201?/??/??: Project was created.
//-----------------------------------------------------------------------------

#include "game.h"
#include "window.h"

// NOTE: Comment out below to use SDL in VS2015 or later versions.
// https://stackoverflow.com/questions/30412951/
FILE _iob[] = {*stdin, *stdout, *stderr};
extern "C" FILE * __cdecl __iob_func() {
  return _iob;
}

int main(int argc, char *argv[]) {
  // You should use this to strengthen our AI.
  // http://hp.vector.co.jp/authors/VA015468/platina/app/index.html
  Game game;
  game.Initialize();
  game.Play();
  game.Terminate();
  return 0;
}
