#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Null


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
/////////////ES POT POSAR ELS DOS BFS EN UN FENT QUE LA CONDICIO DEL IF INTERN CRIDI UNA ALTRE FUNCIO//////////////////////

  /**
   * Play method, invoked once per each round.
   */

  virtual void play () {
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);