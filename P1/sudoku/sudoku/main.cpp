//
//  main.cpp
//  sudoku
//
//  Created by 闰土那只猹 on 28/01/2022.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <math.h>

using namespace std;

void display_board(int wild);
void create_sudoku(int wild, string file_name);
bool check_num(int postion, int num, int wild);
void solve_sudoku(int n, int wild);

char sudoku_origin[20][20];
bool flag = false;
char number[10] = {'0','1','2','3','4','5','6','7','8','9'};
char number_16[17] ={'z','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

int main(){
    create_sudoku(9, "/Users/runtunazhicha/Desktop/P1_SUDOKU.txt");
    display_board(9);
    solve_sudoku(0, 9);
    cout << endl;
    cout << endl;
    display_board(9);
}

void create_sudoku(int wild, string file_name){
    char sudoku_perline[20];
    ifstream sudoku;
    sudoku.open(file_name, ios::in);
    
    for(int i = 0; i < wild; i++){
        sudoku.getline(sudoku_perline, sizeof(sudoku_perline));
        for(int j = 0; j < wild; j++){
            sudoku_origin[i][j] = sudoku_perline[j];
            }
    }
}

void display_board(int wild){
    const string div_line = "+------+------+------+";
    for(int i = 0; i < wild; i++){
        if(i % int(sqrt(wild)) == 0){
            cout << div_line << endl;
        }
        for(int j = 0; j < wild; j++){
            if(j % int(sqrt(wild)) == 0){
                cout << "|";
            }
            if(sudoku_origin[i][j] == 'X'){
                cout << "_" << " ";
            }
            else{
                cout << sudoku_origin[i][j] << " ";
            }
        }
        cout << "|";
        cout << endl;
    }
    cout << div_line << endl;
}

void solve_sudoku(int n, int wild){
    if(n > (pow(wild, 2)-1)){
        flag = true;
    }
    
    int x = n/wild, y = n%wild;
    
    if (sudoku_origin[x][y] != 'X') {
        solve_sudoku(n+1, wild);
        return;
    }
    
    for(int i = 1; i <= wild; i++){
        if(check_num(n, i, wild) == true){
            sudoku_origin[x][y] = number[i];
            solve_sudoku(n+1, wild);
            if(flag){
                return;
            }
            sudoku_origin[x][y] = 'X';
        }
    }
}

bool check_num(int postion, int num, int wild){
    int block_x = 0;
    int block_y = 0;
    
    for(int i = 0; i < wild; i++){
        if(sudoku_origin[postion/wild][i] == number[num]){
            return false;
        }
    }
    
    for(int j = 0; j < wild; j++){
        if(sudoku_origin[j][postion%wild] == number[num]){
            return false;
        }
    }
    
    block_x = postion/wild/int(sqrt(wild))*int(sqrt(wild));
    block_y = postion%wild/int(sqrt(wild))*int(sqrt(wild));
    for (int i = 0; i < int(sqrt(wild)); i++) {
        for(int j = 0; j < int(sqrt(wild)); j++){
            if (sudoku_origin[block_x + i][block_y + j] == number[num]) {
                return false;
            }
        }
    }
    return true;
}

