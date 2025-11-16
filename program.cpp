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
            the_board_ptr=arg2_the_board;
            age=arg3_age;
            length=1;
            width=1;
            sign='H';
            moveOnBoardIfOk(x,y,length,width,the_board_ptr,sign);
        }
};

class Elf : public Character{
    public:
        Elf(int arg0_x, int arg1_y, Board* arg2_the_board, int arg3_age){
            x=arg0_x;
            y=arg1_y;
            the_board_ptr=arg2_the_board;
            age=arg3_age;
            length=3; //elfs are taller and fatter than humans :)
            width=2;
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

class DoubleSpeedAbility : public BaseDecorator{
    public:
        DoubleSpeedAbility(Character* character) : BaseDecorator(character){}
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

class Group : public Character{
    public:
        list<Character*> group;
        void addCharacter(Character* character_ptr){
            group.push_back(character_ptr);
        }
        void moveUp() override{
            for(Character* c : group){
                c->moveUp();
            }
        }
        void moveDown() override{
            for(Character* c : group){
                c->moveDown();
            }
        }
        void moveLeft(){
            for(Character* c : group){
                c->moveLeft();
            }
        }
        void moveRight(){
            for(Character* c : group){
                c->moveRight();
            }
        }
};

class Building : public Entity{
    public:
        int width=0;
        int length=0;
        char sign;
        list<string> parts;
        void listParts(){
            cout<<"Building parts:\n";
            for(string p : parts){
                cout<<p<<endl;
            }
        }
};

class Builder{
    public: 
        Building* building_ptr;
        virtual void buildWalls(string material){}
        virtual void buildRoof(string type){}
        void buildWindows(){
            building_ptr->parts.push_back("windows");
        }
        Building* getBuilding(char arg0_sign, int arg1_x, int arg2_y, Board* arg3_the_board_ptr){
            building_ptr->sign=arg0_sign;
            building_ptr->x=arg1_x;
            building_ptr->y=arg2_y;
            building_ptr->the_board_ptr=arg3_the_board_ptr;
            moveOnBoardIfOk(building_ptr->x, building_ptr->y, building_ptr->length, building_ptr->width, building_ptr->the_board_ptr, building_ptr->sign);
            Building* result = building_ptr;
            building_ptr = new Building();
            return result;
        }
};

class CastleBuilder : public Builder{
    public:
        CastleBuilder(){
            building_ptr=new Building();
        }
        void buildWalls(string material) override{
            building_ptr->parts.push_back(material+" walls");
            building_ptr->width+=10;//size distinguishes castles from houses
            building_ptr->length+=5;
        }
        void buildRoof(string type) override{
            building_ptr->parts.push_back(type+" roof");
            building_ptr->length+=1;
        }
};

class HouseBuilder : public Builder{
    public:
        HouseBuilder(){
            building_ptr=new Building();
        }
        void buildWalls(string material) override{
            building_ptr->parts.push_back(material+" walls");
            building_ptr->width+=5;//size distinguishes castles from houses
            building_ptr->length+=3;
        }
        void buildRoof(string type) override{
            building_ptr->parts.push_back(type+" roof");
            building_ptr->length+=2;//roofs of houses are more pointy, therefore more lengthy
        }
};

class AbstractFactory{
    public:
        char sign;
        virtual Building* createCastle(int x, int y, Board* the_board_ptr)=0;
        virtual Building* createHouse(int x, int y, Board* the_board_ptr)=0;
};

class EuropeanFactory : public AbstractFactory{
    public:
        char sign='$'; //because the euro symbol doesn't work
        Building* createCastle(int x, int y, Board* the_board_ptr) override{
            CastleBuilder* castle_builder_ptr=new CastleBuilder();
            castle_builder_ptr->buildWalls("concrete");
            castle_builder_ptr->buildRoof("concrete flat");
            //no windows for european castles <3
            return castle_builder_ptr->getBuilding(sign,x,y,the_board_ptr);
        }
        Building* createHouse(int x, int y, Board* the_board_ptr) override{
            HouseBuilder* house_builder_ptr=new HouseBuilder();
            house_builder_ptr->buildWalls("concrete");
            house_builder_ptr->buildRoof("red");
            house_builder_ptr->buildWindows();
            return house_builder_ptr->getBuilding(sign,x,y,the_board_ptr);
        }
};

class AfricanFactory : public AbstractFactory{
    public:
        char sign='|'; 
        Building* createCastle(int x, int y, Board* the_board_ptr) override{
            CastleBuilder* castle_builder_ptr=new CastleBuilder();
            castle_builder_ptr->buildWalls("dirt");
            castle_builder_ptr->buildRoof("cane");
            //no windows for african castles <3
            return castle_builder_ptr->getBuilding(sign,x,y,the_board_ptr);
        }
        Building* createHouse(int x, int y, Board* the_board_ptr) override{
            HouseBuilder* house_builder_ptr=new HouseBuilder();
            house_builder_ptr->buildWalls("dirt");
            //africans are very poor: they don't have roofs or windows: just dirt walls
            return house_builder_ptr->getBuilding(sign,x,y,the_board_ptr);
        }
};

class AsianFactory : public AbstractFactory{
    public:
        char sign='^'; 
        Building* createCastle(int x, int y, Board* the_board_ptr) override{
            CastleBuilder* castle_builder_ptr=new CastleBuilder();
            castle_builder_ptr->buildWalls("bamboo");
            castle_builder_ptr->buildRoof("asian specific bamboo");
            castle_builder_ptr->buildWindows();
            return castle_builder_ptr->getBuilding(sign,x,y,the_board_ptr);
        }
        Building* createHouse(int x, int y, Board* the_board_ptr) override{
            HouseBuilder* house_builder_ptr=new HouseBuilder();
            house_builder_ptr->buildWalls("bamboo");
            house_builder_ptr->buildRoof("asian specific bamboo");
            return house_builder_ptr->getBuilding(sign,x,y,the_board_ptr);
        }
};

int main(){
    int board_width;
    int board_length;
    cout << "Enter board width(if you want to be safe, just enter 100):";
    cin >> board_width;
    cout << "Enter board length(if you want to be safe, just enter 100):";
    cin >> board_length;
    Board* board1_ptr=new Board(board_width,board_length);
    Human* human1_ptr=new Human(6,7,board1_ptr,100);
    board1_ptr->render();
    DoubleSpeedAbility* speedyHuman1_ptr=new DoubleSpeedAbility(human1_ptr);
    DoubleSpeedAbility* speedyHuman2_ptr=new DoubleSpeedAbility(speedyHuman1_ptr);
    speedyHuman2_ptr->moveUp();
    board1_ptr->render();
    speedyHuman2_ptr->moveLeft();
    board1_ptr->render();
    speedyHuman2_ptr->moveDown();
    board1_ptr->render();
    speedyHuman2_ptr->moveRight();
    board1_ptr->render();
    Elf* elf1_ptr=new Elf(10,11,board1_ptr,20);
    board1_ptr->render();
    elf1_ptr->moveDown();
    board1_ptr->render();
    Group* group1_ptr=new Group();
    group1_ptr->addCharacter(speedyHuman2_ptr);
    group1_ptr->addCharacter(elf1_ptr);
    group1_ptr->moveDown();
    board1_ptr->render();
    group1_ptr->moveDown();
    board1_ptr->render();
    EuropeanFactory* eu_factory_ptr = new EuropeanFactory();
    Building* european_castle_ptr = eu_factory_ptr->createCastle(80,30,board1_ptr);
    Building* european_house_ptr = eu_factory_ptr->createHouse(50,20,board1_ptr);
    board1_ptr->render();
    AsianFactory* asian_factory_ptr = new AsianFactory();
    Building* asian_house_ptr = asian_factory_ptr->createHouse(80,70,board1_ptr);
    AfricanFactory* african_factory_ptr = new AfricanFactory();
    Building* african_castle_ptr = african_factory_ptr->createCastle(25,50,board1_ptr);
    board1_ptr->render();
    european_castle_ptr->listParts();
    european_house_ptr->listParts();
    african_castle_ptr->listParts();
    asian_house_ptr->listParts();

    return 0;
}