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

int get_next(){
  static int next = 0;
  return next++;
}

void upper_right_corner(Matrix(int) &A, int lc, int lr, int uc, int ur, int (*f) ());

void lower_left_corner(Matrix(int) &A, int lc, int lr, int uc, int ur, int (*f) ()){
  // std::cout << lc << ' ' << uc << ' ' << lr << ' ' << ur << '\n';
  int i = ur - 1;
  int j = uc - 1;
  if (i > lr && j > lc){
    for (; j > lc; j--)
      A[i][j] = f();
    for (i--, j = lc + 1; i > lr; i--)
      A[i][j] = f();
    upper_right_corner(A, lc + 1, lr, uc, ur - 1, f);
  }
}

void upper_right_corner(Matrix(int) &A, int lc, int lr, int uc, int ur, int (*f) ()){
  // std::cout << lc << ' ' << uc << ' ' << lr << ' ' << ur << '\n';
  int i = lr + 1;
  int j = lc + 1;
  if (i < ur && j < uc){

    // v 1x1 matrix tactfully solved
    A[i][j] = f();
    j++;
    // ^ 1x1 matrix tactfully solved

    for (; j < uc; j++)
      A[i][j] = f();
    for (i++, j = uc - 1; i < ur; i++)
      A[i][j] = f();
    lower_left_corner(A, lc, lr + 1, uc - 1, ur, f);
  }
}

/*
 * Fills a matrix with a sequence by applying a function (get_next) traversing the matrix in spiral order from the outside in
 */
void spiral_fill(Matrix(int) &A, int m, int n){
  upper_right_corner(A, -1, -1, n, m, get_next);
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
