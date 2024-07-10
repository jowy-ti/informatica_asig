#include "Player.hh"
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME klk_manin13

typedef vector<vector<bool>> Mat;
typedef pair<int,int> Par;
typedef vector<vector<Par>> Mat_par;

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
  
  bool ubi_correct(const Pos ubi) {
    if (pos_ok(ubi) and cell(ubi).type != Waste) {
      if (cell(ubi).id != -1 and (unit(cell(ubi).id).type == Dead or unit(cell(ubi).id).player == me())) return false;
      return true;
    } 
    else return false;
  }
  
  bool objective(const Cell& celda, int i, int j, Pos& ubi, int dni) {
    int dif_i = ubi.i-i;
    int dif_j = ubi.j-j;
    Pos ubi_orig(i, j);
    ///if (my_unit(dni).rounds_for_zombie <= abs(dif_i)+abs(dif_j)) return true;
    ///else ;
    if (celda.food) return true;
    if (celda.id != -1 and unit(celda.id).type == Zombie) {
      Pos new_pos_up = ubi_orig+Up;
      Pos new_pos_down = ubi_orig+Down;
      Pos new_pos_left = ubi_orig+Left;
      Pos new_pos_right = ubi_orig+Right;
      if (unit(cell(ubi_orig).id).rounds_for_zombie != -1) return true;
      if (dif_i == 1 and dif_j == 1) {
        if (ubi_correct(new_pos_left)) move(dni, Left);
        else if (ubi_correct(new_pos_up)) move(dni, Up);
        ubi.i = i;
        ubi.j = j;
      }
      else if (dif_i == -1 and dif_j == -1) {
        if (ubi_correct(new_pos_down)) move(dni, Down);
        else if (ubi_correct(new_pos_right)) move(dni, Right);
        ubi.i = i;
        ubi.j = j;
      }
      else if (dif_i == -1 and dif_j == 1) {
        if (ubi_correct(new_pos_down)) move(dni, Down);
        else if (ubi_correct(new_pos_left)) move(dni, Left);
        ubi.i = i;
        ubi.j = j;
      }
      else if (dif_i == 1 and dif_j == -1) {
        if (ubi_correct(new_pos_up)) move(dni, Up);
        else if (ubi_correct(new_pos_right)) move(dni, Right);
        ubi.i = i;
        ubi.j = j;
      }
      else if ((abs(dif_i) == 2 and abs(dif_j) == 0) or (abs(dif_i) == 0 and abs(dif_j) == 2) or (abs(dif_i) == 1 and abs(dif_j) == 2) or (abs(dif_i) == 2 and abs(dif_j) == 1)) {
        ubi.i = i;
        ubi.j = j;
      }
      return true;
    }
    if (celda.id != -1 and unit(celda.id).type == Alive and unit(celda.id).player != me()) {
      if (unit(cell(ubi_orig).id).rounds_for_zombie != -1) return true;
      double enemy_power = strength(celda.owner);
      double my_power = strength(me());
      double result = my_power/(my_power+enemy_power);
      result = result*0.7+0.3;
      if (result > 0.5) {
        if (abs(dif_i) == 1 and abs(dif_j) == 1) {
          ubi.i = i;
          ubi.j = j;
        }
        return true;
      }
    }
    return false;
  }
  
  void bfs(Mat_par& dist, Mat& mapa, queue<Pos>& cola, Pos& ubi, int dni) {
    cola.push(ubi);
    int row = board_rows();
    int col = board_cols();
    int i = ubi.i;
    int j = ubi.j;
    int cont = 0;
    while (!cola.empty()) {
        ++cont;
        ubi = cola.front();
        if (cont == 220) return;
        cola.pop();
        Cell celda = cell(ubi);
        if (objective(celda, i, j, ubi, dni)) return;
        
        mapa[ubi.i][ubi.j] = true;
        Pos new_pos_up = ubi+Up;
        Pos new_pos_down = ubi+Down;
        Pos new_pos_left = ubi+Left;
        Pos new_pos_right = ubi+Right;
        
        if (ubi_correct(new_pos_up) and !mapa[new_pos_up.i][new_pos_up.j]) {
          dist[new_pos_up.i][new_pos_up.j] = {ubi.i, ubi.j};
          cola.push(new_pos_up);
          mapa[new_pos_up.i][new_pos_up.j] = true;
        }
        if (ubi_correct(new_pos_down) and !mapa[new_pos_down.i][new_pos_down.j]) {
          dist[new_pos_down.i][new_pos_down.j] = {ubi.i, ubi.j};
          cola.push(new_pos_down);
          mapa[new_pos_down.i][new_pos_down.j] = true;
        }
        if (ubi_correct(new_pos_left) and !mapa[new_pos_left.i][new_pos_left.j]) {
          dist[new_pos_left.i][new_pos_left.j] = {ubi.i, ubi.j};
          cola.push(new_pos_left);
          mapa[new_pos_left.i][new_pos_left.j] = true;
        }
        if (ubi_correct(new_pos_right) and !mapa[new_pos_right.i][new_pos_right.j]) {
          dist[new_pos_right.i][new_pos_right.j] = {ubi.i, ubi.j};
          cola.push(new_pos_right);
          mapa[new_pos_right.i][new_pos_right.j] = true;
        }
      }
  }
  void movement(const Mat_par& dist, const Pos& old_ubi, const Pos& dest_ubi, int dni) {
    int i1 = old_ubi.i;
    int j1 = old_ubi.j;
    int i = dest_ubi.i;
    int j = dest_ubi.j;
    if (i != i1 or j != j1) {
      while (dist[i][j].first != i1 or dist[i][j].second != j1) {
        int i2 = i;
        i = dist[i][j].first;
        j = dist[i2][j].second;
      }
      if (i > i1) move(dni, Down);
      else if (i < i1) move(dni, Up);
      else if (j > j1) move(dni, Right);
      else if (j < j1) move(dni, Left);
    }
  }
  
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {

    vector<int> tropas = alive_units(me());
    int tropas_size = tropas.size();
    
    for (int z = 0; z < tropas_size; ++z) {
      Mat mapa(board_rows(), vector<bool>(board_cols(), false));
      Mat_par dist(board_rows(), vector<Par>(board_cols()));
      int dni = tropas[z];
      Pos ubi = unit(dni).pos;
      queue<Pos> cola;
      Pos old_ubi = ubi;
      bfs(dist, mapa, cola, ubi, dni);
      Pos dest_ubi = ubi;
      movement(dist, old_ubi, dest_ubi, dni);
    }
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
