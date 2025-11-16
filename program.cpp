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
                for(int j=0; j < sizey; j++){
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

bool moveUpOnBoardIfOk(int x, int y, int length, int width, Board* the_board_ptr, char sign){
    for(int j=y;j<y+width;j++){
        if(the_board_ptr->reference_board.at(x-1).at(j)!='_'){
            return false;
        }
    }
    for(int j=y;j<y+width;j++){
        the_board_ptr->reference_board.at(x-1).at(j)=sign;
    }
    return true;
}

bool moveDownOnBoardIfOk(int x, int y, int length, int width, Board* the_board_ptr, char sign){
    for(int j=y;j<y+width;j++){
        if(the_board_ptr->reference_board.at(x+length).at(j)!='_'){
            return false;
        }
    }
    for(int j=y;j<y+width;j++){
        the_board_ptr->reference_board.at(x+length).at(j)=sign;
    }
    return true;
}

bool moveLeftOnBoardIfOk(int x, int y, int length, int width, Board* the_board_ptr, char sign){
    for(int i=x;i<x+length;i++){
        if(the_board_ptr->reference_board.at(i).at(y-1)!='_'){
            return false;
        }
    }
    for(int i=x;i<x+length;i++){
        the_board_ptr->reference_board.at(i).at(y-1)=sign;
    }
    return true;
}

bool moveRightOnBoardIfOk(int x, int y, int length, int width, Board* the_board_ptr, char sign){
    for(int i=x;i<x+length;i++){
        if(the_board_ptr->reference_board.at(i).at(y+width)!='_'){
            return false;
        }
    }
    for(int i=x;i<x+length;i++){
        the_board_ptr->reference_board.at(i).at(y+width)=sign;
    }
    return true;
}

bool moveOnBoardIfOk(int x, int y, int length, int width, Board* the_board_ptr, char sign){
    for(int i=x;i<x+length;i++){
        for(int j=y;j<y+width;j++){
            if(the_board_ptr->reference_board.at(i).at(j)!='_'){
                return false;
            }
        }
    }
    for(int i=x;i<x+length;i++){
        for(int j=y;j<y+width;j++){
            the_board_ptr->reference_board.at(i).at(j)=sign;
        }
    }
    return true;
};

void removeColumn(int x, int length, int y_to_be_removed, Board* the_board_ptr, char sign){
    for(int i=x;i<x+length;i++){
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
        int length;
        Board* the_board_ptr; 
        Entity(){}
};

class Character : public Entity{
    public:
        int age;
        char sign;
        Character(){}
        virtual void moveUp(){
            if(moveUpOnBoardIfOk(x,y,length,width,the_board_ptr,sign)==true){
                removeLine(y,width,x+length-1,the_board_ptr,sign);
                x=x-1;
            }
        }
        virtual void moveDown(){
            if(moveDownOnBoardIfOk(x,y,length,width,the_board_ptr,sign)==true){
                removeLine(y,width,x,the_board_ptr,sign);
                x=x+1;
            }   
        }
        virtual void moveLeft(){
            if(moveLeftOnBoardIfOk(x,y,length,width,the_board_ptr,sign)==true){
                removeColumn(x,length,y+width-1,the_board_ptr,sign);
                y=y-1;
            }
        }
        virtual void moveRight(){
            if(moveRightOnBoardIfOk(x,y,length,width,the_board_ptr,sign)==true){
                removeColumn(x,length,y,the_board_ptr,sign);
                y=y+1;
            }
        }
};

class Human : public Character{
    public:
        Human(int arg0_x, int arg1_y, Board* arg2_the_board, int arg3_age){
            x=arg0_x;
            y=arg1_y;
            length=2;
            width=2;
            the_board_ptr=arg2_the_board;
            age=arg3_age;
            sign='H';
            moveOnBoardIfOk(x,y,length,width,the_board_ptr,sign);
        }
};

class Elf : public Character{
    public:
        Elf(int arg0_x, int arg1_y, Board* arg2_the_board, int arg3_age){
            x=arg0_x;
            y=arg1_y;
            length=2; //elfs are taller than humans :)
            width=1;
            the_board_ptr=arg2_the_board;
            age=arg3_age;
            sign='E';
            moveOnBoardIfOk(x,y,length,width,the_board_ptr,sign);
        }
};

class BaseDecorator : public Character{
    public:
        Character* character_ptr;
        BaseDecorator(Character* character) : character_ptr{character}{}
        void moveUp() override{
            return character_ptr->moveUp();
        }
        void moveDown() override{
            return character_ptr->moveDown();
        }
        void moveLeft() override{
            return character_ptr->moveLeft();
        }
        void moveRight() override{
            return character_ptr->moveRight();
        }
};

class DoubleSpeed : public BaseDecorator{
    public:
        DoubleSpeed(Character* character) : BaseDecorator(character){}
        void moveUp() override{
            BaseDecorator::moveUp();
            BaseDecorator::moveUp();
        }
        void moveDown() override{
            BaseDecorator::moveDown();
            BaseDecorator::moveDown();
        }
        void moveLeft(){
            BaseDecorator::moveLeft();
            BaseDecorator::moveLeft();
        }
        void moveRight(){
            BaseDecorator::moveRight();
            BaseDecorator::moveRight();
        }
};

int main(){
    int board_width;
    int board_length;
    cout << "Enter board width:";
    cin >> board_width;
    cout << "Enter board length:";
    cin >> board_length;
    Board* board1_ptr=new Board(board_width,board_length);
    Human* human1_ptr=new Human(6,7,board1_ptr,100);
    board1_ptr->render();
    DoubleSpeed* speedyHuman1_ptr=new DoubleSpeed(human1_ptr);
    DoubleSpeed* speedyHuman2_ptr=new DoubleSpeed(speedyHuman1_ptr);
    speedyHuman2_ptr->moveUp();
    board1_ptr->render();
    speedyHuman2_ptr->moveLeft();
    board1_ptr->render();
    speedyHuman2_ptr->moveDown();
    board1_ptr->render();
    speedyHuman2_ptr->moveRight();
    board1_ptr->render();
    return 0;
}