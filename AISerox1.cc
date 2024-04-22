#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Serox1


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

  typedef vector<int> VI;

  Dir bfs_furyans(Pos& x, vector<vector<char>>& matriu){
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        if (first) aux.second = direction;
        aux.first += direction; 
        Cell c = cell(aux.first);
        if (c.type != Rock){
          if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'F'){
            if (c.id != -1) return aux.second; 
            Q.push(aux);
            matriu[aux.first.i][aux.first.j] = 'F';
          }
        }
        else {
          matriu[aux.first.i][aux.first.j] = 'R';
        }
        aux.first = old_pos;
      }
      first = false;
    }
    return None;
  }

  void move_furyans(vector<vector<char>>& matriu){    
    VI my_F = furyans(me());
    int n = my_F.size();
    for (int i = 0; i < n; ++i){
      Unit F = unit(my_F[i]);
      command(F.id, bfs_furyans(F.pos,matriu));
    }
  }

  Dir bfs_pioneers(Pos& x, vector<vector<char>>& matriu){
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        if (first) aux.second = direction;
        aux.first += direction; 
        Cell c = cell(aux.first);
        if (c.type != Rock){
          if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'P'){
            if (c.owner != me()) return aux.second;
            Q.push(aux);
            matriu[aux.first.i][aux.first.j] = 'P';
          } 
        }
        else {
          matriu[aux.first.i][aux.first.j] = 'R';
        }
        aux.first = old_pos;
      }
      first = false;
    }
    return None;
  }

  void move_pioneers(vector<vector<char>>& matriu){
    VI my_P = pioneers(me());
    int n = my_P.size();
    for (int i = 0; i < n; ++i){
      Unit P = unit(my_P[i]);
      command(P.id, bfs_pioneers(P.pos, matriu));
    }
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    vector<vector<char>> matriu(40,vector<char>(80));
    move_furyans(matriu);
    move_pioneers(matriu);
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
