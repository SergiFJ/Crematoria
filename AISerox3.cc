#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Serox3


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
  typedef vector<int> VI;

  Dir bfs_hellhound(Pos& x, vector<vector<char>>& matriu){
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    int i = 81;
    while (not Q.empty() and i != 0){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        if (first) aux.second = direction;
        aux.first += direction; 
        Cell c = cell(aux.first);
        if (c.type != Rock){
          if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'H'){
            if (c.id != -1 and unit(c.id).type == Hellhound) return aux.second; 
            Q.push(aux);
            matriu[aux.first.i][aux.first.j] = 'H';
          }
        }
        else {
          matriu[aux.first.i][aux.first.j] = 'R';
        }
        aux.first = old_pos;
      }
      first = false;
      --i;
    }
    return None;
  }

  Dir bfs_run(Pos& x, Dir& d, vector<vector<char>>& matriu){
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        if (d != Dir(0) and d != Dir(7) and i < int(d)-1 and i > int(d)+1){
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
        }
        else if (d != Dir(0) and i > 1 and i != 7){
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
        }
        else if (d != Dir(7) and i != 0 and i < 6){
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
        }
        aux.first = old_pos;
      }
      first = false;
    }
    return None;
  }

  Dir bfs_furyans(Pos& x, VI& enemy, vector<vector<char>>& matriu){
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
        if (cell(aux.first).type != Rock){
          if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'F'){
            int n = enemy.size();
            for (int j = 0; j < n; ++j){
              if (aux.first == unit(enemy[j]).pos) return aux.second; 
            }
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
    VI enemy_P;
    for (int i = 0; i < 4; ++i){
      if (i != me()){
        VI pio = pioneers(i);
        enemy_P.insert(enemy_P.end(),pio.begin(),pio.end());
      }
    }
    
    VI my_F = furyans(me());
    int n = my_F.size();
    for (int i = 0; i < n; ++i){
      Unit F = unit(my_F[i]);
      Dir m = bfs_hellhound(F.pos,matriu);
      if (m == None){
        command(F.id, bfs_furyans(F.pos,enemy_P,matriu));
      }
      else {
        command(F.id, bfs_run(F.pos, m, matriu));
      }
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
      Dir m = bfs_hellhound(P.pos,matriu);
      if (m == None){
        command(P.id, bfs_pioneers(P.pos, matriu));
      }
      else {
        command(P.id, bfs_run(P.pos, m, matriu));
      }
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
