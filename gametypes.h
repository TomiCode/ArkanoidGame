/**
 * 
 * gametypes.h
 *
 * Author: Tomasz Król <tomicode@gmail.com>
 *
 * License:  please visit the LICENSE file for details.
 *
 **/

#ifndef GAMETYPES
#define GAMETYPES

namespace Arkanoid {
  enum GameTypes {
    GameObject
  };

  enum GameObjects {
    GamePaddle = 0,
    GameBall   = 1,
    GameBlock  = 2
  };

  enum GameSpecials {
    GameSpecialNone        = 0,
    GameSpecialPoints      = 1,
    GameSpecialBallSpeed   = 2,
    GameSpecialPaddleSpeed = 3,
    GameSpecialDurability  = 4
  };

  enum GameScreen {
    ScreenNoChange,
    ScreenPlaying,
    ScreenWelcome,
    ScreenBallSpeed,
    ScreenPaddleSpeed,
    ScreenPointMultiplayer,
    ScreenGameOver,
    ScreenComplete
  };
}

#endif // GAMETYPES

