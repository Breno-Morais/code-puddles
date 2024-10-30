/*
 * This file is part of Code Puddles.
 * 
 * Code Puddles is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at your
 * option) any later version.
 *
 * Code Puddles is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Code Puddles. If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2024 Garrenlus De Souza
 */

#include <iostream>
#include <vector>

#define Matrix(Type) std::vector<std::vector<Type>>
#define get_matrix(Type, m, n, defaultValue) Matrix(Type)(m, std::vector<Type>(n, defaultValue))

enum Direction {
  HORIZONTAL,
  VERTICAL,
  REVERSE_HORIZONTAL,
  REVERSE_VERTICAL,
};

int get_next(){
  static int next = 0;
  return next++;
}

void fill(Matrix(int) &A, int &i, int &j, int end, Direction d, int (*f) ()) {  
  switch(d) {
    case HORIZONTAL:
      for(; j < end; j++) {
        A[i][j] = f();
      };
      break;

    case VERTICAL:
      for(; i < end; i++) {
        A[i][j] = f();
      };
      break;

    case REVERSE_HORIZONTAL:
      for(; j > end; j--) {
        A[i][j] = f();
      };
      break;

    case REVERSE_VERTICAL:
      for(; i > end; i--) {
        A[i][j] = f();
      };
      break;
  }
  
}

void spiral(Matrix(int) &A, int sr, int sc, int br, int bc, int (*f) ()) {
  int i = sr + 1;
  int j = sc + 1;
  int pc = bc - sc - 2;
  int pr = br - sr - 2;

  if(pc > 0 || pr > 0) {
    if(i<br && j<(bc - 1))
      fill(A, i, j, j+pc, HORIZONTAL, f);

    if(i<(br-1) && j<bc)
      fill(A, i, j, i+pr, VERTICAL, f);

    if(i<br && (sc+1)<j<bc)
      fill(A, i, j, j-pc, REVERSE_HORIZONTAL, f);

    if((sr+1)<i<(br-1) && sc<j<bc)
      fill(A, i, j, i-pr, REVERSE_VERTICAL, f);

    spiral(A, sr + 1, sc + 1, br - 1, bc - 1, f);
  } else if( pc == 0 && pr == 0) {
    A[i][j] = f();
  }
}

/*
 * Fills a matrix with a sequence by applying a function (get_next) traversing the matrix in spiral order from the outside in
 */
void spiral_fill(Matrix(int) &A, int m, int n){
  spiral(A, -1, -1, m, n, get_next);
}

void print_matrix(Matrix(int) &M, int m, int n){
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      std::cout << M[i][j] << ' ';
    }
    if (i < m - 1) std::cout << '\n';
  }
}

// this works given the nature of the sequence we are using here
void reverse_spiral(Matrix(int) &A, int m, int n){
  auto complement = [m, n] (int x) -> int { return  m * n - (x + 1); };
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      A[i][j] = complement(A[i][j]);
    }
  }
}

int main(int argc, char *args[]){
  if (argc < 3){
    std::cout << "Expected use is: " << args[0] << " m n";
    return 1;
  }

  int m = std::stoi(args[1]), n = std::stoi(args[2]);
  auto M = get_matrix(int, m, n, 0);
  spiral_fill(M, m, n);
  // reverse_spiral(M, m, n);
  print_matrix(M, m, n);
  return 0;
}
