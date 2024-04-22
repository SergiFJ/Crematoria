#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Serox11


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

  

  Dir bfs_enemy_furyans(Pos& x){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'H';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    int moves = 25;
    while (not Q.empty() and moves != 0){
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
      --moves;
    }
    return None;
  }

  Dir bfs_run_furyans(Pos& x, Dir& d, VI& enemy){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'F';
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
        int dir = int(d);
        if ((dir != 0 and dir != 7 and (i > dir+1 or i < dir-1)) or (dir == 0 and i > 1 and i != 7) or (dir == 7 and i != 1 and i < 6)){
          if (first) aux.second = direction;
          aux.first += direction; 
          Cell c = cell(aux.first);
          if (c.type != Rock){
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
      }
      first = false;
    }
    return None;
  }

  Dir bfs_furyans(Pos& x, VI& enemy){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'F';
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




  Dir bfs_enemy_pioneer(Pos& x){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'H';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    int moves = 25;
    while (not Q.empty() and moves != 0){
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
            if (c.id != -1 and (unit(c.id).type == Hellhound or (unit(c.id).type == Furyan and unit(c.id).player != me()))) return aux.second; 
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
      --moves;
    }
    return None;
  }


  Dir bfs_run_pioneers(Pos& x, Dir& d){
    vector<vector<char>> matriu(40,vector<char>(80));
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    matriu[x.i][x.j] = 'P';
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        int dir = int(d);
        if ((dir != 0 and dir != 7 and (i > dir+1 or i < dir-1)) or (dir == 0 and i > 1 and i != 7) or (dir == 7 and i != 1 and i < 6)){
          if (first) aux.second = direction;
          aux.first += direction; 
          Cell c = cell(aux.first);
          if (c.type != Rock and c.type != Elevator){
            if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'P'){
              if (c.owner != me() and c.id == -1) return aux.second;
              Q.push(aux);
              matriu[aux.first.i][aux.first.j] = 'P';
            }
          }
          else {
            matriu[aux.first.i][aux.first.j] = 'R';
          }
          aux.first = old_pos;
        }
      }
      first = false;
    }
    return None;
  }

  Dir bfs_pioneers(Pos& x){
    vector<vector<char>> matriu(40,vector<char>(80));
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    matriu[x.i][x.j] = 'P';
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        if (first) aux.second = direction;
        aux.first += direction; 
        Cell c = cell(aux.first);
        if (c.type != Rock and c.type != Elevator){
          if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'P'){
            if (first){
              if (c.owner != me() and c.id == -1) return aux.second;
            }
            else if (c.owner != me()) return aux.second;
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

  Dir bfs_gem(Pos& x){
    vector<vector<char>> matriu(40,vector<char>(80));
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
        if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'G'){
          if (c.gem) return aux.second;
          Q.push(aux);
          matriu[aux.first.i][aux.first.j] = 'G';
        } 
        else {
          matriu[aux.first.i][aux.first.j] = 'G';
        }
        aux.first = old_pos;
      }
      first = false;
    }
    return None;
  }

  void move_furyans(){
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
      vector<vector<char>> matriu(40,vector<char>(80));       
      Unit F = unit(my_F[i]);
      Dir m = bfs_enemy_furyans(F.pos);
      if (m == None){
        command(F.id, bfs_furyans(F.pos,enemy_P));
      }
      else {
        command(F.id, bfs_run_furyans(F.pos, m, enemy_P));
      }
    }
  }

  void move_pioneers(){
    VI my_P = pioneers(me());
    int n = my_P.size();
    for (int i = 0; i < n; ++i){
      Unit P = unit(my_P[i]);
      Pos aux = P.pos;
      aux.j -= 5;
      aux.k = 1;
      if (cell(P.pos).type == Elevator and P.pos.k == 0 and pos_ok(aux) and not daylight(aux)){
        command(P.id, Up);
      }
      else if (P.pos.k == 0){
        Dir m = bfs_enemy_pioneer(P.pos);
        if (m == None){
          command(P.id, bfs_pioneers(P.pos));
        }
        else {
          command(P.id, bfs_run_pioneers(P.pos, m));
        }
      }
      else if (P.pos.k == 1){
        command(P.id, bfs_gem(P.pos));
      }
    }
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_pioneers();
    move_furyans();
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);