#include <bits/stdc++.h>
using namespace std;

class Board{
    public:
        vector<vector<char>> reference_board;
        int sizex;
        int sizey;
        Board(int board_width, int board_length){
            sizex=board_length;
            sizey=board_width;
            for(int i=0; i < sizex; i++){
                vector<char> v;
                for(int j=0; j < sizex; j++){
                    v.push_back('_');
                }
                reference_board.push_back(v);
            }
        }
        void render(){
            cout<<"Current Board State:\n";
            for(int i=0; i < sizex; i++){
                for(int j=0; j < sizey; j++){
                    cout<<reference_board[i][j];
                }
                cout<<"\n";
            }
        }
};

bool moveOnBoardIfOk(int x, int y, int height, int width, Board* the_board_ptr, char sign){
    for(int i=x;i<x+height;i++){
        for(int j=y;j<y+width;j++){
            if(the_board_ptr->reference_board.at(i).at(j)!='_'){
                return false;
            }
        }
    }
    for(int i=x;i<x+height;i++){
        for(int j=y;j<y+width;j++){
            if(the_board_ptr->reference_board.at(i).at(j)!='_'){
                the_board_ptr->reference_board.at(i).at(j)=sign;
            }
        }
    }
    return true;
};

void removeColumn(int x, int height, int y_to_be_removed, Board* the_board_ptr, char sign){
    for(int i=x;i<x+height;i++){
        the_board_ptr->reference_board.at(i).at(y_to_be_removed)='_';
    }
}

void removeLine(int y, int width, int x_to_be_removed, Board* the_board_ptr, char sign){
    for(int j=y;j<y+width;j++){
        the_board_ptr->reference_board.at(x_to_be_removed).at(j)='_';
    }
}

class Entity{
    public:
        int x;
        int y;
        int width;
        int height;
        Board* the_board_ptr; 
        Entity(){}
};

class Character : public Entity{
    public:
        int age;
        char sign;
        Character(){}
        void moveUp(){
            if(moveOnBoardIfOk(x-1,y,height,width,the_board_ptr,sign)==true){
                removeLine(y,width,x,the_board_ptr,sign);
                x=-1;
            }
        }
        void moveDown(){
            if(moveOnBoardIfOk(x+1,y,height,width,the_board_ptr,sign)==true){
                removeLine(y,width,x,the_board_ptr,sign);
                x=+1;
            }   
        }
        void moveLeft(){
            if(moveOnBoardIfOk(x,y-1,height,width,the_board_ptr,sign)==true){
                removeColumn(x,height,y,the_board_ptr,sign);
                y=-1;
            }
        }
        void moveRight(){
            if(moveOnBoardIfOk(x,y+1,height,width,the_board_ptr,sign)==true){
                removeColumn(x,height,y,the_board_ptr,sign);
                y=+1;
            }
        }
};

class Human : public Character{
    public:
        Human(int arg0_x, int arg1_y, Board* arg2_the_board){
            x=arg0_x;
            y=arg1_y;
            height=1;
            width=1;
            the_board_ptr=arg2_the_board;
            sign='H';
            moveOnBoardIfOk(x,y,height,width,the_board_ptr,sign);
        }
};

class Elf : public Character{
    public:
        Elf(int arg0_x, int arg1_y, Board* arg2_the_board){
            x=arg0_x;
            y=arg1_y;
            height=2; //elfs are taller than humans :)
            width=1;
            the_board_ptr=arg2_the_board;
            sign='E';
            moveOnBoardIfOk(x,y,height,width,the_board_ptr,sign);
        }
};

class BaseDecorator : public Character{
    public:
        Character* character_ptr;
        BaseDecorator(Character* character) : character_ptr(character){}

};

int main(){
    int board_width;
    int board_length;
    cout << "Enter board width:";
    cin >> board_width;
    cout << "Enter board length:";
    cin >> board_length;
    Board board1(board_width,board_length);
    Board* board1_ptr=&board1;
    // Entity e1(2,2,2,3,board1_ptr);
    board1.render();
    return 0;
}