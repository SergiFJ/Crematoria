//si no troba enemeics cap a on corre simplement no fa res

#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Serox_2


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

  

  Dir bfs_enemy_furyans_hellhound(Pos& x, Pos& enemy, int meu){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'H';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    int moves = 24;
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
            if (c.id != -1 and unit(c.id).type == Hellhound){
              enemy = aux.first;
              return aux.second;
            }  
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


  Dir bfs_enemy_furyans_furyans(Pos& x, Pos& enemy, int meu){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'H';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    int moves = 8;
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
            if (c.id != -1 and unit(c.id).type == Furyan and unit(c.id).health > unit(meu).health and unit(c.id).player != me()){
                enemy = aux.first;
                return aux.second;
            }  
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

  Dir bfs_run_furyans(Pos& x, Dir& d, int meu, Pos& enemy){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'F';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    Pos distancia;
    distancia.i = enemy.i - x.i;
    distancia.j = enemy.j - x.j;
    distancia.k = enemy.k - x.k;
    Dir final = None;
    //DIRECCIO ON ESTA
    int compare_i = distancia.i;
    int compare_j = distancia.j;
    if (compare_j < 0) compare_j *= -1;
    if (compare_i < 0) compare_i *= -1;
    if (compare_i == compare_j){    //puntes
        if (distancia.i < 0 and distancia.j < 0) final = TL;
        else if (distancia.i > 0 and distancia.j < 0) final = LB;
        else if (distancia.i < 0 and distancia.j > 0) final = RT;
        else if (distancia.i > 0 and distancia.j > 0) final = BR;
    }
    else {
        if (compare_i > compare_j){ //dalt o baix
            if (distancia.i > 0) final = Bottom;
            else final = Top;
        }
        else {
            if (distancia.j > 0) final = Right;
            else final = Left;
        }
    }
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        int dir = int(d);
        if (final == TL or final == LB or final == RT or final == BR){
          if ((dir != 0 and dir != 7 and (i > dir+1 or i < dir-1)) or (dir == 0 and i > 1 and i != 7) or (dir == 7 and i != 1 and i < 6)){
            if (first) aux.second = direction;
            aux.first += direction; 
            Cell c = cell(aux.first);
            if (c.type != Rock){
              if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'F'){
                  if (cell(aux.first).id != -1 and (unit(cell(aux.first).id).type == Pioneer or (unit(cell(aux.first).id).type == Furyan and unit(cell(aux.first).id).health < unit(meu).health)) and unit(cell(aux.first).id).player != me())
                    return aux.second; 
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
        else {
          if (final == Bottom){
            if (i < 6 and i > 2){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
                if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'F'){
                    if (cell(aux.first).id != -1 and (unit(cell(aux.first).id).type == Pioneer or (unit(cell(aux.first).id).type == Furyan and unit(cell(aux.first).id).health < unit(meu).health)) and unit(cell(aux.first).id).player != me())
                      return aux.second; 
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
          else if (final == Top){
            if (i == 7 or  i < 2){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
                if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'F'){
                    if (cell(aux.first).id != -1 and (unit(cell(aux.first).id).type == Pioneer or (unit(cell(aux.first).id).type == Furyan and unit(cell(aux.first).id).health < unit(meu).health)) and unit(cell(aux.first).id).player != me())
                      return aux.second; 
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
          else if (final == Right){
            if (i < 8 and i > 4){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
                if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'F'){
                    if (cell(aux.first).id != -1 and (unit(cell(aux.first).id).type == Pioneer or (unit(cell(aux.first).id).type == Furyan and unit(cell(aux.first).id).health < unit(meu).health)) and unit(cell(aux.first).id).player != me())
                      return aux.second; 
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
          else if (final == Left){
            if (i < 4 and i > 0){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
                if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'F'){
                    if (cell(aux.first).id != -1 and (unit(cell(aux.first).id).type == Pioneer or (unit(cell(aux.first).id).type == Furyan and unit(cell(aux.first).id).health < unit(meu).health)) and unit(cell(aux.first).id).player != me())
                      return aux.second; 
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
        }
      }
      first = false;
    }
    return None;
  }

  Dir bfs_furyans(Pos& x, int meu){
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
                if (cell(aux.first).id != -1 and (unit(cell(aux.first).id).type == Pioneer or (unit(cell(aux.first).id).type == Furyan and unit(cell(aux.first).id).health < unit(meu).health)) and unit(cell(aux.first).id).player != me())
                  return aux.second; 
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




  Dir bfs_enemy_pioneer_hellhound(Pos& x, Pos& enemy){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'H';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    int moves = 24;
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
            if (c.id != -1 and unit(c.id).type == Hellhound ){ //mirar quin numero de moves es millor, potser 16 etc
              enemy = aux.first;
              return aux.second; 
            }
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


  Dir bfs_enemy_pioneer_furyan(Pos& x, Pos& enemy){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'H';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    int moves = 8;
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
            if (c.id != -1 and unit(c.id).type == Furyan and unit(c.id).player != me()){ //mirar quin numero de moves es millor, potser 16 etc
              enemy = aux.first;
              return aux.second; 
            }
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


  Dir bfs_run_pioneers(Pos& x, Dir& d, Pos& enemy){
    vector<vector<char>> matriu(40,vector<char>(80));
    matriu[x.i][x.j] = 'P';
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    Pos distancia;
    distancia.i = enemy.i - x.i;
    distancia.j = enemy.j - x.j;
    distancia.k = enemy.k - x.k;
    Dir final = None;
    //DIRECCIO ON ESTA
    int compare_i = distancia.i;
    int compare_j = distancia.j;
    if (compare_j < 0) compare_j *= -1;
    if (compare_i < 0) compare_i *= -1;
    if (compare_i == compare_j){    //puntes
        if (distancia.i < 0 and distancia.j < 0) final = TL;
        else if (distancia.i > 0 and distancia.j < 0) final = LB;
        else if (distancia.i < 0 and distancia.j > 0) final = RT;
        else if (distancia.i > 0 and distancia.j > 0) final = BR;
    }
    else {
        if (compare_i > compare_j){ //dalt o baix
            if (distancia.i > 0) final = Bottom;
            else final = Top;
        }
        else {
            if (distancia.j > 0) final = Right;
            else final = Left;
        }
    }
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        int dir = int(d);
        if (final == TL or final == LB or final == RT or final == BR){
          if ((dir != 0 and dir != 7 and (i > dir+1 or i < dir-1)) or (dir == 0 and i > 1 and i != 7) or (dir == 7 and i != 1 and i < 6)){
            if (first) aux.second = direction;
            aux.first += direction; 
            Cell c = cell(aux.first);
            if (c.type != Rock){
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
        else {
          if (final == Bottom){
            if (i < 6 and i > 2){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
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
          else if (final == Top){
            if (i == 7 or  i < 2){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
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
          else if (final == Right){
            if (i < 8 and i > 4){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
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
          else if (final == Left){
            if (i < 4 and i > 0){
              if (first) aux.second = direction;
              aux.first += direction; 
              Cell c = cell(aux.first);
              if (c.type != Rock){
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
        }
      }
      first = false;
    }
    return bfs_pioneers(x);
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
        aux.first += direction; 
        Cell c = cell(aux.first);
        if (first and c.id == -1){
            aux.second = direction;
            if (c.type != Rock){
            if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'P'){
                if (first){
                if (c.owner != me()) return aux.second;
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
        else if (not first){
            aux.second = direction;
            if (c.type != Rock){
            if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'R' and matriu[aux.first.i][aux.first.j] != 'P'){
                if (first){
                if (c.owner != me()) return aux.second;
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
    matriu[x.i][x.j] = 'G';
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        if (first and cell(aux.first).id == -1){
            aux.second = direction;
            aux.first += direction; 
            if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'G' and not daylight(aux.first)){
            if (first){
                if (cell(aux.first).gem and cell(aux.first).id == -1) return aux.second;
            }
            else {
                if (cell(aux.first).gem) return aux.second;
            }
            Q.push(aux);
            matriu[aux.first.i][aux.first.j] = 'G';
            } 
            aux.first = old_pos;
        }
        if (not first){
            aux.second = direction;
            aux.first += direction; 
            if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'G' and not daylight(aux.first)){
            if (first){
                if (cell(aux.first).gem and cell(aux.first).id == -1) return aux.second;
            }
            else {
                if (cell(aux.first).gem) return aux.second;
            }
            Q.push(aux);
            matriu[aux.first.i][aux.first.j] = 'G';
            } 
            aux.first = old_pos;
        }
      }
      first = false;
    }
    return None;
  }

  Dir bfs_ascenssor(Pos& x){
    vector<vector<char>> matriu(40,vector<char>(80));
    queue<pair<Pos,Dir>> Q;
    Q.push(make_pair(x,None));
    pair<Pos,Dir> aux;
    bool first = true;
    matriu[x.i][x.j] = 'A';
    if (cell(x).type == Elevator) return Down;
    while (not Q.empty()){
      aux = Q.front();
      Q.pop();
      for (int i = 0; i < 8; ++i){
        Pos old_pos = aux.first;
        Dir direction = Dir(i);
        if (first) aux.second = direction;
        aux.first += direction; 
        if (pos_ok(aux.first) and matriu[aux.first.i][aux.first.j] != 'A' and not daylight(aux.first)){
          if (cell(aux.first).type == Elevator) return aux.second;
          Q.push(aux);
          matriu[aux.first.i][aux.first.j] = 'A';
        } 
        aux.first = old_pos;
      }
      first = false;
    }
    return None;
  }

  void move_furyans(){    
    VI my_F = furyans(me());
    int n = my_F.size();
    for (int i = 0; i < n; ++i){
      Unit F = unit(my_F[i]);
      command(F.id, bfs_furyans(F.pos,F.id));
    }
  }

  void move_pioneers(){
    VI my_P = pioneers(me());
    int n = my_P.size();
    for (int i = 0; i < n; ++i){
      Unit P = unit(my_P[i]);
      if (P.pos.k == 0){
        Pos aux = P.pos;
        aux.k = 1;
        if (cell(P.pos).type == Elevator and P.pos.k == 0 and not daylight(aux))
            command(P.id, Up);
        else
            command(P.id, bfs_pioneers(P.pos));
      }
      else if (P.pos.k == 1){
        
        Dir m = bfs_gem(P.pos);
        if (m == None){
          command(P.id,bfs_ascenssor(P.pos));
        }
        else              
          command(P.id,m);
      }
    }
  }
  void escapar(){
    VI my_P = pioneers(me());
    int n = my_P.size();
    VI my_F = furyans(me());
    int m = my_F.size();
    for (int i = 0; i < n; ++i){
        Unit P = unit(my_P[i]);
        Pos enemy;
        if (P.pos.k != 1){
            Dir m = bfs_enemy_pioneer_hellhound(P.pos,enemy);
            if (m == None){
                m = bfs_enemy_pioneer_furyan(P.pos,enemy);
                if (m != None)
                    command(P.id, bfs_run_pioneers(P.pos, m,enemy));
            }
            else {
                command(P.id, bfs_run_pioneers(P.pos, m,enemy));
            }
        }
    }
    for (int i = 0; i < m; ++i){
        Unit F = unit(my_F[i]);
        Pos enemy;
        Dir m = bfs_enemy_furyans_hellhound(F.pos,enemy, F.id);
        if (m == None){
            m = bfs_enemy_furyans_furyans(F.pos,enemy, F.id);
            if (m != None)
                command(F.id, bfs_run_furyans(F.pos, m, F.id,enemy));
        }
        else {
            command(F.id, bfs_run_furyans(F.pos, m, F.id,enemy));
        }
    }
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    escapar();
    move_pioneers();
    move_furyans();
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
