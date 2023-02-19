// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT7L 
// Names: Liau Kai Ze | Lai Cheng Yung
// IDs: 1211102809 | 1211102810
// Emails: 1211102809@student.mmu.edu.my | 1211102810@student.mmu.edu.my
// Phones: 012-5158580 | 010-2528292
// ********************************************************* 

#include "pf/helper.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <algorithm> //for string to lower / to upper
#include <unistd.h> //for system sleep
using namespace std;

int X = 15, Y = 5, Z = 1, init = 0;
int aX, aY;

void settings()
{
    char selection;

    while(true)
    {
        cout << "Default game settings: " << endl;
        cout << "Board Rows: " <<  X <<" (Minimum of 1 row and maximum of 50 rows.)"<<endl;
        cout << "Board Columns:  " << Y <<" (Minimum of 1 columns and maximum of 50 columns.)" <<endl;
        cout << "Number of Zombies: "<< Z <<" (Minimum of 1 zombies and maximum of 9 zombies.)"<< endl;
        cout <<"Would you like to change the settings? (y/n)"<<endl;
        cin >> selection;
        cout <<endl;
        
        if (selection == 'Y' || selection == 'y')
        {
            cout << "New Board Rows (Odd Numbers Only): " ;
            cin >> X;
            while (true)
            {
                if(cin.fail() || X > 50 || X <1 || X % 2 == 0)
                {
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Board Rows: " ;
                    cin>>X;
                }
                else
                {
                    break;
                }
            }

            cout << "New Board Columns (Odd Numbers Only): " ;
            cin >> Y;
            while (true)
            {
                if(cin.fail() || Y >50 || Y <1 || Y % 2 == 0)
                {
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Board Columns:  " ;
                    cin>>Y;
                }
                else
                {
                    break;
                }
            }

            cout << "New Number of Zombies: ";
            cin >> Z;
            while (true)
            {
                if(cin.fail() || Z>9 || Z<1)
                {
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Number of Zombies: ";
                    cin>>Z;
                }
                else
                {
                    break;
                }
            }

            cout << "New settings saved"<< endl <<endl;
        }

        else if (selection == 'N' || selection == 'n')
        {
            break;
        }

        else
        {
            cout << "Invalid Selection"<<endl<<endl;
        }
    }
}

void confirm()
    {
        cout << "Press enter to continue . . . " << endl;
        cin.get();
        cin.ignore();
    }

class Board
{
    private:
        vector<vector<char>> board_; // convention to put trailing underscore
        int boardX_, boardY_, zombies_;// to indicate private data

    public:
        Board(int boardX = X, int boardY = Y);
        void init(int boardX, int boardY);
        void display() const;
        int getBoardX() const;
        int getBoardY() const;
        char getObject(int x, int y) const;
        void setObject(int x, int y, int ch);
        bool isEmpty(int x, int y, char ch);
        bool isInsideMap(int x, int y, int maxX, int maxY);
        void help();
        void arrow();
        char command();
};

class Alien
{
    private:
        int x_, y_, hp_, dmg_;
        char heading_,alien_;
        
    public:
        Alien();
        void landinit(Board &board);
        void land(Board &board, int x, int y);
        int getX() const;
        int getY() const;
        char getHeading();
        void status();
        void up(Board &board);
        void down(Board &board);
        void left(Board &board);
        void right(Board &board);
        char getItem(Board &board);
        char checkItem(char item);
        void damage(int hp);
        void reset();
        void main();
};

class Zombie
{
    private:
        int num_ = Z;
        int x1_, y1_, hp1_, dmg1_, range1_;
        int x2_, y2_, hp2_, dmg2_, range2_;
        int x3_, y3_, hp3_, dmg3_, range3_;
        int x4_, y4_, hp4_, dmg4_, range4_;
        int x5_, y5_, hp5_, dmg5_, range5_;
        int x6_, y6_, hp6_, dmg6_, range6_;
        int x7_, y7_, hp7_, dmg7_, range7_;
        int x8_, y8_, hp8_, dmg8_, range8_;
        int x9_, y9_, hp9_, dmg9_, range9_;

    public:
        Zombie();
        void landinit(Board &board);
        void land(Board &board);
        int getX(int num);
        int getY(int num);
        void status();
        void up(int zombie);
        void down(int zombie);
        void left(int zombie);
        void right(int zombie);
        char search(int zombie);
        void damage(int zombie, int damage);
        void main();
};

Board::Board(int boardX, int boardY)
{
    init(boardX, boardY);
}

void Board::init(int boardX,int boardY)
{
    boardX_ = boardX;
    boardY_ = boardY;

    char objects[] = {' ', ' ', 'v', '^', '<', '>', 'h', ' ', 'r', ' '}; //todo add pod
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector

    board_.resize(boardY_); // create empty rows

    for (int i = 0; i < boardY_; ++i)
    {
        board_[i].resize(boardX_); // resize each row
    }

    // put random characters into the vector array
    for (int i = 0; i < boardY_; ++i)
    {
        for (int j = 0; j < boardX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            board_[i][j] = objects[objNo];
        }
    }
}

void Board::display() const
{
    // for each row
    for (int i = 0; i < boardY_; ++i)
    {
        // display upper border of the row
        cout << " ";
        for (int j = 0; j < boardX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (boardY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < boardX_; ++j)
        {
            cout << "|" << board_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << " ";
    for (int j = 0; j < boardX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
    for (int j = 0; j < boardX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    for (int j = 0; j < boardX_; ++j) // j== 0..14
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;

    // int numZombies;
    // numZombies = Z;

    // while (numZombies > 0)
    // {
    //     cout<< "Zombie " <<numZombies<<" : "<<endl<<endl;
    //     numZombies--;
    // }
}

int Board::getBoardX() const
{
    return boardX_;
}

int Board::getBoardY() const
{
    return boardY_;
}

char Board::getObject(int x, int y) const
{
    return board_[boardY_-y][x-1];
}

void Board::setObject(int x, int y, int ch)
{
    board_[boardY_-y][x-1] = ch;
}

bool Board::isEmpty(int x, int y, char ch)
{
    return x, y, (isblank(ch));
}

bool Board::isInsideMap(int x, int y, int maxX, int maxY)
{
    return (1<=x &&1<=y) && (x<=maxX && y<=maxY);
}

void Board::help()
{
    cout << endl;
    cout << "Commands" << endl;
    cout << "1. up       - Move up" << endl;
    cout << "2. down     - Move down" << endl;
    cout << "3. left     - Move left" << endl;
    cout << "4. right    - Move right" << endl;
    cout << "5. arrow    - Change the direction of an arrow" << endl;
    cout << "6. help     - Display these user commands" << endl;
    cout << "7. save     - Save the game" << endl;
    cout << "8. load     - Load a game" << endl;
    cout << "9. quit     - Quit this game" << endl<<endl;
}

void Board::arrow()
{
    Board board;
    int x,y;
    char obj;
    string direction;

    while (true)
    {
        cout<<endl<<"Enter column: "<<endl;
        cin>>x;
        cout<<"Enter row: "<<endl;
        cin>>y;

        if (board.getObject(x, y) != '^' && board.getObject(x, y) != 'v' && board.getObject(x, y) != '<' && board.getObject(x, y) != '>')
        {
            cout<< "The item selected is not found, please try again.";
        }
        else
        {
            obj = board.getObject(x, y);
            break;
        }
    }

    cout<<obj;
    while (true)
    {   
        cout<<endl<<"Enter direction (up/down/left/right): "<<endl;
        cin>>direction;

        if (direction != "up" && direction != "down" && direction != "left" && direction != "right")
        {
            cout<< "Wrong input, please try again.";
        }
        else
        {
            break;
        }
    }

    if (direction == "up")
    {
        board.setObject(x,y,'^');
    }

    else if (direction == "down")
    {
        board.setObject(x,y,'v');
    }

    else if (direction == "left")
    {
        board.setObject(x,y,'<');
    }

    else
    {
        board.setObject(x,y,'>');
    }
}

Alien::Alien()
{
    hp_ = 100;
    dmg_ = 0;
}

void Alien::landinit(Board &board)
{
    x_ = board.getBoardX() / 2;
    y_ = board.getBoardY() / 2 + 1;
    heading_ = '^';
    alien_ = 'A';
    board.setObject(x_, y_, alien_);
}

void Alien::land(Board &board , int x, int y)
{
    Alien alien;
    board.setObject(aX, aY, alien_);
}

int Alien::getX() const
{
    return x_;
}

int Alien::getY() const
{
    return y_;
}

char Alien::getHeading()
{
    return heading_;
}

void Alien::status()
{
    cout<<"Alien : Health - "<<hp_<<", Damage - "<<dmg_<<endl<<endl;
}

void Alien::up(Board &board)
{
    board.setObject(x_, y_, '.');
        y_++;
    heading_ = '^';
    board.setObject(x_, y_, alien_);
}

void Alien::down(Board &board)
{
    board.setObject(x_, y_, '.');
        y_--;
    heading_ = 'v';
    board.setObject(x_, y_, alien_);
}

void Alien::left(Board &board)
{
    board.setObject(x_, y_, '.');
        x_--;
    heading_ = '<';
    board.setObject(x_, y_, alien_);
}

void Alien::right(Board &board)
{
    board.setObject(x_, y_, '.');
        x_++;
    heading_ = '>';
    board.setObject(x_, y_, alien_);
}

char Alien::getItem(Board &board)
{
    Alien alien;
    char item;

    if(x_ == 1 || y_ == 1 || x_ == X || y_ == Y)
    {
        return item;
    }
    else
    {
        if(heading_ == '<')
        {
            item  = board.getObject(x_ - 1, y_);
        }

        else if(heading_ == '>')
        {
            item  = board.getObject(x_ + 1, y_);
        }

        else if(heading_ == '^')
        {
            item  = board.getObject(x_, y_ + 1);
        }

        else
        {
            item  = board.getObject(x_, y_ - 1);
        }
    }
    return item;
}

char Alien::checkItem(char item)
{
    Alien alien;
    Board board;
    Zombie zombie;

    if (item == 'r')
    {
        int num;
        cout<<"A rock is blocking the alien's way."<<endl;
        num = rand() % 2;

        if (num == true)
        {
            cout<<"The alien finds a pod beneath the rock."<<endl<<endl;

            if (heading_ == '<')
            {
                board.setObject(x_ - 1, y_, 'p');
            }

            else if (heading_ == '>')
            {
                board.setObject(x_ + 1, y_, 'p');
            }

            else if (heading_ == '^')
            {
                board.setObject(x_, y_ + 1, 'p');
            }

            else
            {
                board.setObject(x_, y_ - 1, 'p');
            }
        }

        else
        {
            cout<<"The alien finds health beneath the rock."<<endl;
            cout<<"The alien gains 20 health,"<<endl<<endl;
            hp_ = hp_ + 20;

            if (heading_ == '<')
            {
                board.setObject(x_ - 1, y_, 'h');
            }

            else if (heading_ == '>')
            {
                board.setObject(x_ + 1, y_, 'h');
            }

            else if (heading_ == '^')
            {
                board.setObject(x_, y_ + 1, 'h');
            }

            else
            {
                board.setObject(x_, y_ - 1, 'h');
            }
        }
    }

    else if (item == 'h')
    {
        cout<<"Alien finds health, Alien's health is increased by 20."<<endl;
        hp_ = hp_ + 20;
    }

    else if (item == 'p')
    {
        cout<<"Alien finds a pod."<<endl;
        while (true)
        {
            int zomX [9] = {zombie.getX(1), zombie.getX(2), zombie.getX(3), zombie.getX(4), zombie.getX(5), zombie.getX(6), zombie.getX(7), zombie.getX(8), zombie.getX(9)};
            int zomY[9] = {zombie.getY(1), zombie.getY(2), zombie.getY(3), zombie.getY(4), zombie.getY(5), zombie.getY(6), zombie.getY(7), zombie.getY(8), zombie.getY(9)};
            int distance[9];
            int closest[2] = {100, 0};

            for (int i = 0; i < Z; ++i)
            {
                distance[i] = zomX[i] + zomY[i];
            }       

            for (int j = 0; j <= sizeof(distance); ++j)
            {
                if (distance[j] > 0 && distance[j] < X+Y)
                {
                    if (distance[j] < closest[0])
                    {
                        closest[0] = distance[j];
                        closest[1] = j;
                    }
                }
            }

            cout<<"Zombie "<<closest[1]<<" is the closest to the alien."<<endl;
            cout<<"Zombie "<<closest[1]<<" recieves 10 damage."<<endl;
            zombie.damage(closest[1], 10);
        }
    }

    else if (item == '^')
    {
        cout<< "Alien finds a up arrow, alien will move up."<<endl<<"Alien's damage will increase by 20."<<endl;
        dmg_ = dmg_ + 20;
        heading_ = '^';
    }

    else if (item == 'v')
    {
        cout<< "Alien finds a down arrow, alien will move down."<<endl<<"Alien's damage will increase by 20."<<endl;
        dmg_ = dmg_ + 20;
        heading_ = 'v';
    }

    else if (item == '>')
    {
        cout<< "Alien finds a right arrow, alien will move right."<<endl<<"Alien's damage will increase by 20."<<endl;
        dmg_ = dmg_ + 20;
        heading_ = '>';
    }

    else if (item == '<')
    {
        cout<< "Alien finds a left arrow, alien will move left."<<endl<<"Alien's damage will increase by 20."<<endl;
        dmg_ = dmg_ + 20;
        heading_ = '<';
    }

    else if(item == '1' || item == '2' || item == '3' || item == '4' || item == '5' || item == '6' || item == '7' || item == '8' || item == '9')
    {
        if (item == '1')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(1, dmg_);
        }
        else if (item == '2')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(2, dmg_);
        }
        else if (item == '3')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(3, dmg_);
        }
        else if (item == '4')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(4, dmg_);
        }
        else if (item == '5')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(5, dmg_);
        }
        else if (item == '6')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(6, dmg_);
        }
        else if (item == '7')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(7, dmg_);
        }
        else if (item == '8')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(8, dmg_);
        }
        else if (item == '9')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(9, dmg_);
        }
    }
    else
    {
    }
    return item;
}

void Alien::damage(int hp)
{
    hp_ = hp_ - hp;
}

void Alien::reset()
{
    Board board;
    char trail;
    int seed;

    for (int i = 1; i <= X; ++i)
    {
        for (int j = 1; j <= Y; ++j)
        {
            //trail = board.getObject(i,j);
            //cout<<trail<<endl;
            if (trail == '.')
            {
                seed = rand() % 9 + 1;
                if (seed == 1)
                {
                    board.setObject(i,j,'^');
                }
                else if (seed == 2)
                {
                    board.setObject(i,j,'v');
                }
                else if (seed == 3)
                {
                    board.setObject(i,j,'<');
                }
                else if (seed == 4)
                {
                    board.setObject(i,j,'>');
                }
                else if (seed == 5)
                {
                    board.setObject(i,j,'h');
                }
                else if (seed == 6)
                {
                    board.setObject(i,j,'p');
                }
                else if (seed == 7)
                {
                    board.setObject(i,j,'r');
                }
                else
                {
                    board.setObject(i,j,' ');
                }
            }
        }
    }
}

Zombie::Zombie()
{
    hp1_ = (rand() % 3 + 1) * 100, dmg1_ = (rand() % 5 + 1) * 5, range1_ = rand() % 4 + 1;
    hp2_ = (rand() % 3 + 1) * 100, dmg2_ = (rand() % 5 + 1) * 5, range2_ = rand() % 4 + 1;
    hp3_ = (rand() % 3 + 1) * 100, dmg3_ = (rand() % 5 + 1) * 5, range3_ = rand() % 4 + 1;
    hp4_ = (rand() % 3 + 1) * 100, dmg4_ = (rand() % 5 + 1) * 5, range4_ = rand() % 4 + 1;
    hp5_ = (rand() % 3 + 1) * 100, dmg5_ = (rand() % 5 + 1) * 5, range5_ = rand() % 4 + 1;
    hp6_ = (rand() % 3 + 1) * 100, dmg6_ = (rand() % 5 + 1) * 5, range6_ = rand() % 4 + 1;
    hp7_ = (rand() % 3 + 1) * 100, dmg7_ = (rand() % 5 + 1) * 5, range7_ = rand() % 4 + 1;
    hp8_ = (rand() % 3 + 1) * 100, dmg8_ = (rand() % 5 + 1) * 5, range8_ = rand() % 4 + 1;
    hp9_ = (rand() % 3 + 1) * 100, dmg9_ = (rand() % 5 + 1) * 5, range9_ = rand() % 4 + 1;
}

void Zombie::landinit(Board &board)
{
    x1_ = rand() % X + 1; y1_ = rand() % Y + 1;
    x2_ = rand() % X + 1; y2_ = rand() % Y + 1;
    x3_ = rand() % X + 1; y3_ = rand() % Y + 1;
    x4_ = rand() % X + 1; y4_ = rand() % Y + 1;
    x5_ = rand() % X + 1; y5_ = rand() % Y + 1;
    x6_ = rand() % X + 1; y6_ = rand() % Y + 1;
    x7_ = rand() % X + 1; y7_ = rand() % Y + 1;
    x8_ = rand() % X + 1; y8_ = rand() % Y + 1;
    x9_ = rand() % X + 1; y9_ = rand() % Y + 1;

    if (num_ == 1)
    {
        board.setObject(x1_, y1_, '1');
    }

    else if (num_ == 2)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
    }

    else if (num_ == 3)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
    }

    else if (num_ == 4)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
    }

    else if (num_ == 5)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
    }

    else if (num_ == 6)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
    }

    else if (num_ == 7)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
        board.setObject(x7_, y7_, '7');
    }
    
    else if (num_ == 8)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
        board.setObject(x7_, y7_, '7');
        board.setObject(x8_, y8_, '8');
    }

    else if (num_ == 9)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
        board.setObject(x7_, y7_, '7');
        board.setObject(x8_, y8_, '8');
        board.setObject(x9_, y9_, '9');
    }
}

void Zombie::land(Board &board)
{
    cout<<x1_<<"  "<<y1_<<endl<<endl;
    if (num_ == 1)
    {
        board.setObject(x1_, y1_, '1');
    }

    else if (num_ == 2)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
    }

    else if (num_ == 3)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
    }

    else if (num_ == 4)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
    }

    else if (num_ == 5)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
    }

    else if (num_ == 6)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
    }

    else if (num_ == 7)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
        board.setObject(x7_, y7_, '7');
    }
    
    else if (num_ == 8)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
        board.setObject(x7_, y7_, '7');
        board.setObject(x8_, y8_, '8');
    }

    else if (num_ == 9)
    {
        board.setObject(x1_, y1_, '1');
        board.setObject(x2_, y2_, '2');
        board.setObject(x3_, y3_, '3');
        board.setObject(x4_, y4_, '4');
        board.setObject(x5_, y5_, '5');
        board.setObject(x6_, y6_, '6');
        board.setObject(x7_, y7_, '7');
        board.setObject(x8_, y8_, '8');
        board.setObject(x9_, y9_, '9');
    }
}

int Zombie::getX(int num)
{
    if (num == 1)
    {
        return x1_;
    }

    else if (num == 2)
    {
        return x2_;
    }

    else if (num == 3)
    {
        return x3_;
    }

    else if (num == 4)
    {
        return x4_;
    }

    else if (num == 5)
    {
        return x5_;
    }

    else if (num == 6)
    {
        return x6_;
    }

    else if (num == 7)
    {
        return x7_;
    }
    
    else if (num == 8)
    {
        return x8_;
    }

    else if (num == 9)
    {
        return x9_;
    }
    return 0;
}

int Zombie::getY(int num)
{
    if (num == 1)
    {
        return y1_;
    }

    else if (num == 2)
    {
        return y2_;
    }

    else if (num == 3)
    {
        return y3_;
    }

    else if (num == 4)
    {
        return y4_;
    }

    else if (num == 5)
    {
        return y5_;
    }

    else if (num == 6)
    {
        return y6_;
    }

    else if (num == 7)
    {
        return y7_;
    }
    
    else if (num == 8)
    {
        return y8_;
    }

    else if (num == 9)
    {
        return y9_;
    }
    return 0;
}

void Zombie::status()
{
    if (num_ == 1)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
    }

    else if (num_ == 2)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
    }

    else if (num_ == 3)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<hp3_<<", Damage - "<<dmg3_<<", Range - "<<range3_<<endl<<endl;
    }

    else if (num_ == 4)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<hp3_<<", Damage - "<<dmg3_<<", Range - "<<range3_<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<hp4_<<", Damage - "<<dmg4_<<", Range - "<<range4_<<endl<<endl;
    }

    else if (num_ == 5)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<hp3_<<", Damage - "<<dmg3_<<", Range - "<<range3_<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<hp4_<<", Damage - "<<dmg4_<<", Range - "<<range4_<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<hp5_<<", Damage - "<<dmg5_<<", Range - "<<range5_<<endl<<endl;
    }

    else if (num_ == 6)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<hp3_<<", Damage - "<<dmg3_<<", Range - "<<range3_<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<hp4_<<", Damage - "<<dmg4_<<", Range - "<<range4_<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<hp5_<<", Damage - "<<dmg5_<<", Range - "<<range5_<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<hp6_<<", Damage - "<<dmg6_<<", Range - "<<range6_<<endl<<endl;
    }

    else if (num_ == 7)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<hp3_<<", Damage - "<<dmg3_<<", Range - "<<range3_<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<hp4_<<", Damage - "<<dmg4_<<", Range - "<<range4_<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<hp5_<<", Damage - "<<dmg5_<<", Range - "<<range5_<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<hp6_<<", Damage - "<<dmg6_<<", Range - "<<range6_<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<hp7_<<", Damage - "<<dmg7_<<", Range - "<<range7_<<endl<<endl;
    }
    
    else if (num_ == 8)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<hp3_<<", Damage - "<<dmg3_<<", Range - "<<range3_<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<hp4_<<", Damage - "<<dmg4_<<", Range - "<<range4_<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<hp5_<<", Damage - "<<dmg5_<<", Range - "<<range5_<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<hp6_<<", Damage - "<<dmg6_<<", Range - "<<range6_<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<hp7_<<", Damage - "<<dmg7_<<", Range - "<<range7_<<endl<<endl;
        cout<<"Zombie 8 : Health - "<<hp8_<<", Damage - "<<dmg8_<<", Range - "<<range8_<<endl<<endl;
    }

    else if (num_ == 9)
    {
        cout<<"Zombie 1 : Health - "<<hp1_<<", Damage - "<<dmg1_<<", Range - "<<range1_<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<hp2_<<", Damage - "<<dmg2_<<", Range - "<<range2_<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<hp3_<<", Damage - "<<dmg3_<<", Range - "<<range3_<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<hp4_<<", Damage - "<<dmg4_<<", Range - "<<range4_<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<hp5_<<", Damage - "<<dmg5_<<", Range - "<<range5_<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<hp6_<<", Damage - "<<dmg6_<<", Range - "<<range6_<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<hp7_<<", Damage - "<<dmg7_<<", Range - "<<range7_<<endl<<endl;
        cout<<"Zombie 8 : Health - "<<hp8_<<", Damage - "<<dmg8_<<", Range - "<<range8_<<endl<<endl;
        cout<<"Zombie 9 : Health - "<<hp9_<<", Damage - "<<dmg9_<<", Range - "<<range9_<<endl<<endl;
    }
}

void Zombie::up(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(x1_, y1_, ' ');
        y1_++;
    }

    else if (zombie == 2)
    {
        board.setObject(x2_, y2_, ' ');
        y2_++;
    }

    else if (zombie == 3)
    {
        board.setObject(x3_, y3_, ' ');
        y3_++;
    }

    else if (zombie == 4)
    {
        board.setObject(x4_, y4_, ' ');
        y4_++;
    }

    else if (zombie == 5)
    {
        board.setObject(x5_, y5_, ' ');
        y5_++;
    }

    else if (zombie == 6)
    {
        board.setObject(x6_, y6_, ' ');
        y6_++;
    }

    else if (zombie == 7)
    {
        board.setObject(x7_, y7_, ' ');
        y7_++;
    }
    
    else if (zombie == 8)
    {
        board.setObject(x8_, y8_, ' ');
        y8_++;
    }

    else if (zombie == 9)
    {
        board.setObject(x9_, y9_, ' ');
        y9_++;
    }
}

void Zombie::down(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(x1_, y1_, ' ');
        y1_--;
    }

    else if (zombie == 2)
    {
        board.setObject(x2_, y2_, ' ');
        y2_--;
    }

    else if (zombie == 3)
    {
        board.setObject(x3_, y3_, ' ');
        y3_--;
    }

    else if (zombie == 4)
    {
        board.setObject(x4_, y4_, ' ');
        y4_--;
    }

    else if (zombie == 5)
    {
        board.setObject(x5_, y5_, ' ');
        y5_--;
    }

    else if (zombie == 6)
    {
        board.setObject(x6_, y6_, ' ');
        y6_--;
    }

    else if (zombie == 7)
    {
        board.setObject(x7_, y7_, ' ');
        y7_--;
    }
    
    else if (zombie == 8)
    {
        board.setObject(x8_, y8_, ' ');
        y8_--;
    }

    else if (zombie == 9)
    {
        board.setObject(x9_, y9_, ' ');
        y9_--;
    }
}

void Zombie::left(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(x1_, y1_, ' ');
        x1_--;
    }

    else if (zombie == 2)
    {
        board.setObject(x2_, y2_, ' ');
        x2_--;
    }

    else if (zombie == 3)
    {
        board.setObject(x3_, y3_, ' ');
        x3_--;
    }

    else if (zombie == 4)
    {
        board.setObject(x4_, y4_, ' ');
        x4_--;
    }

    else if (zombie == 5)
    {
        board.setObject(x5_, y5_, ' ');
        x5_--;
    }

    else if (zombie == 6)
    {
        board.setObject(x6_, y6_, ' ');
        x6_--;
    }

    else if (zombie == 7)
    {
        board.setObject(x7_, y7_, ' ');
        x7_--;
    }
    
    else if (zombie == 8)
    {
        board.setObject(x8_, y8_, ' ');
        x8_--;
    }

    else if (zombie == 9)
    {
        board.setObject(x9_, y9_, ' ');
        x9_--;
    }
}

void Zombie::right(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(x1_, y1_, ' ');
        x1_++;
    }

    else if (zombie == 2)
    {
        board.setObject(x2_, y2_, ' ');
        x2_++;
    }

    else if (zombie == 3)
    {
        board.setObject(x3_, y3_, ' ');
        x3_++;
    }

    else if (zombie == 4)
    {
        board.setObject(x4_, y4_, ' ');
        x4_++;
    }

    else if (zombie == 5)
    {
        board.setObject(x5_, y5_, ' ');
        x5_++;
    }

    else if (zombie == 6)
    {
        board.setObject(x6_, y6_, ' ');
        x6_++;
    }

    else if (zombie == 7)
    {
        board.setObject(x7_, y7_, ' ');
        x7_++;
    }
    
    else if (zombie == 8)
    {
        board.setObject(x8_, y8_, ' ');
        x8_++;
    }

    else if (zombie == 9)
    {
        board.setObject(x9_, y9_, ' ');
        x9_++;
    }
}

char Zombie::search(int zombie)
{
    Board board;
    char searchU, searchD, searchL, searchR;

    if (zombie == 1)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }

    else if (zombie == 2)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }

    else if (zombie == 3)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range3_; ++i)
        {
            searchU  = board.getObject(x3_, y3_ + i);
            searchD  = board.getObject(x3_, y3_ - i);
            searchL  = board.getObject(x3_ - i, y3_);
            searchR  = board.getObject(x3_ + i, y3_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }

    else if (zombie == 4)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range3_; ++i)
        {
            searchU  = board.getObject(x3_, y3_ + i);
            searchD  = board.getObject(x3_, y3_ - i);
            searchL  = board.getObject(x3_ - i, y3_);
            searchR  = board.getObject(x3_ + i, y3_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range4_; ++i)
        {
            searchU  = board.getObject(x4_, y4_ + i);
            searchD  = board.getObject(x4_, y4_ - i);
            searchL  = board.getObject(x4_ - i, y4_);
            searchR  = board.getObject(x4_ + i, y4_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }

    else if (zombie == 5)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range3_; ++i)
        {
            searchU  = board.getObject(x3_, y3_ + i);
            searchD  = board.getObject(x3_, y3_ - i);
            searchL  = board.getObject(x3_ - i, y3_);
            searchR  = board.getObject(x3_ + i, y3_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range4_; ++i)
        {
            searchU  = board.getObject(x4_, y4_ + i);
            searchD  = board.getObject(x4_, y4_ - i);
            searchL  = board.getObject(x4_ - i, y4_);
            searchR  = board.getObject(x4_ + i, y4_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range5_; ++i)
        {
            searchU  = board.getObject(x5_, y5_ + i);
            searchD  = board.getObject(x5_, y5_ - i);
            searchL  = board.getObject(x5_ - i, y5_);
            searchR  = board.getObject(x5_ + i, y5_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }

    else if (zombie == 6)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range3_; ++i)
        {
            searchU  = board.getObject(x3_, y3_ + i);
            searchD  = board.getObject(x3_, y3_ - i);
            searchL  = board.getObject(x3_ - i, y3_);
            searchR  = board.getObject(x3_ + i, y3_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range4_; ++i)
        {
            searchU  = board.getObject(x4_, y4_ + i);
            searchD  = board.getObject(x4_, y4_ - i);
            searchL  = board.getObject(x4_ - i, y4_);
            searchR  = board.getObject(x4_ + i, y4_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range5_; ++i)
        {
            searchU  = board.getObject(x5_, y5_ + i);
            searchD  = board.getObject(x5_, y5_ - i);
            searchL  = board.getObject(x5_ - i, y5_);
            searchR  = board.getObject(x5_ + i, y5_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range6_; ++i)
        {
            searchU  = board.getObject(x6_, y6_ + i);
            searchD  = board.getObject(x6_, y6_ - i);
            searchL  = board.getObject(x6_ - i, y6_);
            searchR  = board.getObject(x6_ + i, y6_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }

    else if (zombie == 7)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range3_; ++i)
        {
            searchU  = board.getObject(x3_, y3_ + i);
            searchD  = board.getObject(x3_, y3_ - i);
            searchL  = board.getObject(x3_ - i, y3_);
            searchR  = board.getObject(x3_ + i, y3_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range4_; ++i)
        {
            searchU  = board.getObject(x4_, y4_ + i);
            searchD  = board.getObject(x4_, y4_ - i);
            searchL  = board.getObject(x4_ - i, y4_);
            searchR  = board.getObject(x4_ + i, y4_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range5_; ++i)
        {
            searchU  = board.getObject(x5_, y5_ + i);
            searchD  = board.getObject(x5_, y5_ - i);
            searchL  = board.getObject(x5_ - i, y5_);
            searchR  = board.getObject(x5_ + i, y5_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range6_; ++i)
        {
            searchU  = board.getObject(x6_, y6_ + i);
            searchD  = board.getObject(x6_, y6_ - i);
            searchL  = board.getObject(x6_ - i, y6_);
            searchR  = board.getObject(x6_ + i, y6_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range7_; ++i)
        {
            searchU  = board.getObject(x7_, y7_ + i);
            searchD  = board.getObject(x7_, y7_ - i);
            searchL  = board.getObject(x7_ - i, y7_);
            searchR  = board.getObject(x7_ + i, y7_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }
    
    else if (zombie == 8)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range3_; ++i)
        {
            searchU  = board.getObject(x3_, y3_ + i);
            searchD  = board.getObject(x3_, y3_ - i);
            searchL  = board.getObject(x3_ - i, y3_);
            searchR  = board.getObject(x3_ + i, y3_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range4_; ++i)
        {
            searchU  = board.getObject(x4_, y4_ + i);
            searchD  = board.getObject(x4_, y4_ - i);
            searchL  = board.getObject(x4_ - i, y4_);
            searchR  = board.getObject(x4_ + i, y4_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range5_; ++i)
        {
            searchU  = board.getObject(x5_, y5_ + i);
            searchD  = board.getObject(x5_, y5_ - i);
            searchL  = board.getObject(x5_ - i, y5_);
            searchR  = board.getObject(x5_ + i, y5_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range6_; ++i)
        {
            searchU  = board.getObject(x6_, y6_ + i);
            searchD  = board.getObject(x6_, y6_ - i);
            searchL  = board.getObject(x6_ - i, y6_);
            searchR  = board.getObject(x6_ + i, y6_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range7_; ++i)
        {
            searchU  = board.getObject(x7_, y7_ + i);
            searchD  = board.getObject(x7_, y7_ - i);
            searchL  = board.getObject(x7_ - i, y7_);
            searchR  = board.getObject(x7_ + i, y7_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range8_; ++i)
        {
            searchU  = board.getObject(x8_, y8_ + i);
            searchD  = board.getObject(x8_, y8_ - i);
            searchL  = board.getObject(x8_ - i, y8_);
            searchR  = board.getObject(x8_ + i, y8_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }

    else if (zombie == 9)
    {
        for (int i = 1; i<=range1_; ++i)
        {
            searchU  = board.getObject(x1_, y1_ + i);
            searchD  = board.getObject(x1_, y1_ - i);
            searchL  = board.getObject(x1_ - i, y1_);
            searchR  = board.getObject(x1_ + i, y1_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range2_; ++i)
        {
            searchU  = board.getObject(x2_, y2_ + i);
            searchD  = board.getObject(x2_, y2_ - i);
            searchL  = board.getObject(x2_ - i, y2_);
            searchR  = board.getObject(x2_ + i, y2_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range3_; ++i)
        {
            searchU  = board.getObject(x3_, y3_ + i);
            searchD  = board.getObject(x3_, y3_ - i);
            searchL  = board.getObject(x3_ - i, y3_);
            searchR  = board.getObject(x3_ + i, y3_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range4_; ++i)
        {
            searchU  = board.getObject(x4_, y4_ + i);
            searchD  = board.getObject(x4_, y4_ - i);
            searchL  = board.getObject(x4_ - i, y4_);
            searchR  = board.getObject(x4_ + i, y4_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range5_; ++i)
        {
            searchU  = board.getObject(x5_, y5_ + i);
            searchD  = board.getObject(x5_, y5_ - i);
            searchL  = board.getObject(x5_ - i, y5_);
            searchR  = board.getObject(x5_ + i, y5_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range6_; ++i)
        {
            searchU  = board.getObject(x6_, y6_ + i);
            searchD  = board.getObject(x6_, y6_ - i);
            searchL  = board.getObject(x6_ - i, y6_);
            searchR  = board.getObject(x6_ + i, y6_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range7_; ++i)
        {
            searchU  = board.getObject(x7_, y7_ + i);
            searchD  = board.getObject(x7_, y7_ - i);
            searchL  = board.getObject(x7_ - i, y7_);
            searchR  = board.getObject(x7_ + i, y7_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range8_; ++i)
        {
            searchU  = board.getObject(x8_, y8_ + i);
            searchD  = board.getObject(x8_, y8_ - i);
            searchL  = board.getObject(x8_ - i, y8_);
            searchR  = board.getObject(x8_ + i, y8_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
        for (int i = 1; i<=range9_; ++i)
        {
            searchU  = board.getObject(x9_, y9_ + i);
            searchD  = board.getObject(x9_, y9_ - i);
            searchL  = board.getObject(x9_ - i, y9_);
            searchR  = board.getObject(x9_ + i, y9_);
            if (searchU == 'A' || searchD == 'A' || searchL == 'A' || searchR == 'A')
            {
                return 'A';
            }
        }
    }
    return 0;
}

void Zombie::damage(int zombie, int damage)
{
    if (zombie == 1)
    {
        hp1_ = hp1_ - damage;
    }

    else if (zombie == 2)
    {
        hp2_ = hp2_ - damage;
    }

    else if (zombie == 3)
    {
        hp3_ = hp3_ - damage;
    }

    else if (zombie == 4)
    {
        hp4_ = hp4_ - damage;
    }

    else if (zombie == 5)
    {
        hp5_ = hp5_ - damage;
    }

    else if (zombie == 6)
    {
        hp6_ = hp6_ - damage;
    }

    else if (zombie == 7)
    {
        hp7_ = hp7_ - damage;
    }

    else if (zombie == 8)
    {
        hp8_ = hp8_ - damage;
    }

    else if (zombie == 9)
    {
        hp9_ = hp9_ - damage;
    }
}

void test1_3()
{
    Board board;
cout << "Dim X = " << board.getBoardX() << endl;
cout << "Dim Y = " << board.getBoardY() << endl;
}

void test1_4()
{
    Board board;
    board.display();

    int x, y;
    char obj;

    x = 1;
    y = 1;
    obj = board.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
        << obj << "]" << endl;

    x = 15;
    y = 2;
    obj = board.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
        << obj << "]" << endl;

    x = 5;
    y = 5;
    obj = board.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
        << obj << "]" << endl;

    x = 10;
    y = 2;
    obj = board.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
        << obj << "]" << endl;
}

void test1_5()
{
    Board board;

    int x1 = 1, y1 = 1;
    char ch1 = 'A';

    int x2 = 15, y2 = 1;
    char ch2 = 'B';

    int x3 = 15, y3 = 5;
    char ch3 = 'C';

    int x4 = 1, y4 = 5;
    char ch4 = 'D';

    int x5 = 7, y5 = 3;
    char ch5 = 'E';

    board.setObject(x1, y1, ch1);
    board.setObject(x2, y2, ch2);
    board.setObject(x3, y3, ch3);
    board.setObject(x4, y4, ch4);
    board.setObject(x5, y5, ch5);

    board.display();
    cout << "The object " << ch1 << " should be at column "
         << x1 << " and row " << y1 << endl;
    cout << "The object " << ch2 << " should be at column "
         << x2 << " and row " << y2 << endl;
    cout << "The object " << ch3 << " should be at column "
         << x3 << " and row " << y3 << endl;
    cout << "The object " << ch4 << " should be at column "
         << x4 << " and row " << y4 << endl;
    cout << "The object " << ch5 << " should be at column "
         << x5 << " and row " << y5 << endl;
}

void test1_6()
{
    Board board;
    int maxX = board.getBoardX();
    int maxY = board.getBoardY();

    int x1 = 2, y1 = 4;
    char ch1 = 'Z';

    int x2 = 10, y2 = 3;
    char ch2 = ' ';

    board.setObject(x1, y1, ch1);
    board.setObject(x2, y2, ch2);
    board.display();
    
    cout << boolalpha;
    cout << "Is (" << x1 << ", " << y1 << ") empty? Answer = "
         << board.isEmpty(x1, y1,ch1) << endl;
    cout << "Is (" << x2 << ", " << y2 << ") empty? Answer = "
         << board.isEmpty(x2, y2,ch2) << endl;

    int x3 = 15, y3 = 5;
    int x4 = 0, y4 = 3;
    
    cout << "Is (" << x3 << ", " << y3 << ") inside board? Answer = "
         << board.isInsideMap(x3, y3,maxX,maxY) << endl;
    cout << "Is (" << x4 << ", " << y4 << ") inside board? Answer = "
         << board.isInsideMap(x4, y4,maxX,maxY) << endl;

}

void test2_1()
{
    Board board;
    Alien alien;
    //alien.land(board);
    board.display();
    cout << "Status of the alien:" << endl
    << " Location: (" << alien.getX() << ", " << alien.getY() << ")"

    << endl;

    //<< " Heading: " << alien.getHeading() << endl;
}

void test2_2()
{
    Board board;
    Alien alien;

    //alien.land(board);
    board.display();
    cin.get(); //system("pause");

    alien.left(board);
    board.display();
    cin.get(); //system("pause");

    alien.up(board);
    board.display();
    cin.get(); //system("pause");

    alien.up(board);
    board.display();
    cin.get(); //system("pause");

    alien.right(board);
    board.display();
    cin.get(); //system("pause");

    alien.up(board);
    board.display();
}

char Board::command()
{
    Board board;
    Alien alien;
    string command;

    while (true)
    {
        cout<<"command >> ";
        cin>>command;
        transform(command.begin(), command.end(), command.begin(), ::tolower);
        
        if(command == "up")
        {
            return 'u';
            break;
        }

        else if (command == "down")
        {
            return 'd';
            break;
        }

        else if (command == "left")
        {
            return 'l';
            break;
        }

        else if (command == "right")
        {
            return 'r';
            break;
        }

        else if (command == "arrow")
        {
            return 'a';
            break;
        }

        else if (command == "help")
        {
            return 'h';
            break;
        }

        else if (command == "save")
        {
            return 's';
            break;
        }

        else if (command == "load")
        {
            return 'o';
            break;
        }

        else if (command == "quit")
        {
            while (true)
            {
                cout<<"Do you want to quit the game? (y/n)"<<endl;
                char select;
                cin>>select;
                if (select == 'y' || select == 'Y')
                {
                    cout<<endl<<"Thanks for playing!"<<endl;
                    usleep(2000000);
                    return 'q';
                    break;
                }
                else if (select == 'n' || select == 'N')
                {
                    cout<<endl;
                    break;
                }
                else
                {
                    cout<<"Entered wrong command, please try again."<<endl<<endl;
                }
            }
        }

        else
        {
            cout<<"Entered wrong command, please try again."<<endl<<endl;
        }
    }
    return 'z';
}

void Alien::main()
{
    Board board;
    Alien alien;
    Zombie zombie;
    char command;
    char item;

    if (init == false)
    {
        alien.landinit(board);
        zombie.landinit(board);
        init = 1;
    }
    else
    {
        alien.land(board, aX, aY);
        zombie.land(board);
    }

    board.display();
    alien.status();
    zombie.status();

    command = board.command();

    while(true)
    {
        if (command == 'u' || command == 'd' || command == 'l' || command == 'r')
        {
            if (command == 'u')
            {
                heading_ = '^';
            }

            else if(command == 'd')
            {
                heading_ = 'v';
            }

            else if(command == 'l')
            {
                heading_ = '<';
            }

            else if(command == 'r')
            {
                heading_= '>';
            }
            break;
        }

        if (command == 'a')
        {
            board.arrow();
        }

        if (command == 'h')
        {
            //system("cls"); //undo before launch
            board.help();
            alien.main();
        }

        if (command == 'q')
        {
            abort();
        }
    }

    //system("cls"); //undo before launch
    board.display();
    alien.status();
    zombie.status();
    confirm();
    //system("cls"); //undo before launch

    while (true)
    {
        if (heading_ == '^')
        {
            alien.up(board);
            board.display();
            alien.status();
            zombie.status();
            item = alien.checkItem(alien.getItem(board));
            heading_ = alien.getHeading();
            confirm();
            //system("cls"); //undo before launch

            if (item == 'r' || item == '1' || item == '2' || item == '3' || item == '4' || item == '5' || item == '6' || item == '7' || item == '8' || item == '9')
            {
                cout<<"Alien has ended their turn."<<endl<< "Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }
        }

        else if (heading_ == 'v')
        {
            alien.down(board);
            board.display();
            alien.status();
            zombie.status();
            item = alien.checkItem(alien.getItem(board));
            heading_ = alien.getHeading();
            confirm();
            //system("cls"); //undo before launch

            if (item == 'r' || item == '1' || item == '2' || item == '3' || item == '4' || item == '5' || item == '6' || item == '7' || item == '8' || item == '9')
            {
                cout<<"Alien has ended their turn."<<endl<< "Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }
        }

        else if (heading_ == '<')
        {
            alien.left(board);
            board.display();
            alien.status();
            zombie.status();
            item = alien.checkItem(alien.getItem(board));
            heading_ = alien.getHeading();
            confirm();
            //system("cls"); //undo before launch

            if (item == 'r' || item == '1' || item == '2' || item == '3' || item == '4' || item == '5' || item == '6' || item == '7' || item == '8' || item == '9')
            {
                cout<<"Alien has ended their turn."<<endl<< "Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }
        }

        else if (heading_ == '>')
        {
            alien.right(board);
            board.display();
            alien.status();
            zombie.status();
            item = alien.checkItem(alien.getItem(board));
            heading_ = alien.getHeading();
            confirm();
            //system("cls"); //undo before launch

            if (item == 'r' || item == '1' || item == '2' || item == '3' || item == '4' || item == '5' || item == '6' || item == '7' || item == '8' || item == '9')
            {
                cout<<"Alien has ended their turn."<<endl<< "Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                dmg_ = 0;
                alien.reset();
                break;
            }
        }
    }

    if(hp_ <= 0)
    {
        cout<<endl<<"Alien has no life left. Game Over."<<endl;
        cout<<"The game will terminate in 5 seconds."<<endl<<endl;
        cout<<"5"<<endl;
        usleep(1000000);
        cout<<"4"<<endl;
        usleep(1000000);
        cout<<"3"<<endl;
        usleep(1000000);
        cout<<"2"<<endl;
        usleep(1000000);
        cout<<"1"<<endl;
        usleep(1000000);
        abort();
    }
    board.display();
    alien.status();
    zombie.status();
    x_ = alien.getX(); y_ = alien.getY();
    aX = x_; aY = y_;
    zombie.main();
}

void Zombie::main()
{
    Board board;
    Alien alien;
    Zombie zombie;
    int hp, seed;
    hp = hp1_ + hp2_ + hp3_ + hp4_ + hp5_ + hp6_ + hp7_ + hp8_ + hp9_;

        cout<<x1_<<"  "<<y1_<<endl;
        cout<<x2_<<"  "<<y2_<<endl;
        cout<<x3_<<"  "<<y3_<<endl;
        cout<<x4_<<"  "<<y4_<<endl;
        cout<<x5_<<"  "<<y5_<<endl;
        cout<<x6_<<"  "<<y6_<<endl;
        cout<<x7_<<"  "<<y7_<<endl;
        cout<<x8_<<"  "<<y8_<<endl;
        cout<<x9_<<"  "<<y9_<<endl<<endl;

        cout<<zombie.getX(1)<<"  "<<zombie.getY(1)<<endl<<endl;

    alien.land(board, aX, aY);
    zombie.land(board);
    board.display();
    alien.status();
    zombie.status();
            cout<<x1_<<"  "<<y1_<<endl;
        cout<<x2_<<"  "<<y2_<<endl;
        cout<<x3_<<"  "<<y3_<<endl;
        cout<<x4_<<"  "<<y4_<<endl;
        cout<<x5_<<"  "<<y5_<<endl;
        cout<<x6_<<"  "<<y6_<<endl;
        cout<<x7_<<"  "<<y7_<<endl;
        cout<<x8_<<"  "<<y8_<<endl;
        cout<<x9_<<"  "<<y9_<<endl;
    confirm();
    //system("cls"); //undo before launch

    if (num_ == 1)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }
        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
    }

    else if (num_ == 2)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }

        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
    }

    else if (num_ == 3)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }
        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
        if (hp3_ <= 0)
        {
            cout<<"Zombie 3 has no life left.";
            hp3_ = 0;
            board.setObject(x3_ ,y3_, ' ');
        }
    }

    else if (num_ == 4)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }

        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
        if (hp3_ <= 0)
        {
            cout<<"Zombie 3 has no life left.";
            hp3_ = 0;
            board.setObject(x3_ ,y3_, ' ');
        }
        if (hp4_ <= 0)
        {
            cout<<"Zombie 4 has no life left.";
            hp4_ = 0;
            board.setObject(x4_ ,y4_, ' ');
        }
    }

    else if (num_ == 5)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }

        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
        if (hp3_ <= 0)
        {
            cout<<"Zombie 3 has no life left.";
            hp3_ = 0;
            board.setObject(x3_ ,y3_, ' ');
        }
        if (hp4_ <= 0)
        {
            cout<<"Zombie 4 has no life left.";
            hp4_ = 0;
            board.setObject(x4_ ,y4_, ' ');
        }
        if (hp5_ <= 0)
        {
            cout<<"Zombie 5 has no life left.";
            hp5_ = 0;
            board.setObject(x5_ ,y5_, ' ');
        }
    }

    else if (num_ == 6)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }

        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
        if (hp3_ <= 0)
        {
            cout<<"Zombie 3 has no life left.";
            hp3_ = 0;
            board.setObject(x3_ ,y3_, ' ');
        }
        if (hp4_ <= 0)
        {
            cout<<"Zombie 4 has no life left.";
            hp4_ = 0;
            board.setObject(x4_ ,y4_, ' ');
        }
        if (hp5_ <= 0)
        {
            cout<<"Zombie 5 has no life left.";
            hp5_ = 0;
            board.setObject(x5_ ,y5_, ' ');
        }
        if (hp6_ <= 0)
        {
            cout<<"Zombie 6 has no life left.";
            hp6_ = 0;
            board.setObject(x6_ ,y6_, ' ');
        }
    }

    else if (num_ == 7)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }

        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
        if (hp3_ <= 0)
        {
            cout<<"Zombie 3 has no life left.";
            hp3_ = 0;
            board.setObject(x3_ ,y3_, ' ');
        }
        if (hp4_ <= 0)
        {
            cout<<"Zombie 4 has no life left.";
            hp4_ = 0;
            board.setObject(x4_ ,y4_, ' ');
        }
        if (hp5_ <= 0)
        {
            cout<<"Zombie 5 has no life left.";
            hp5_ = 0;
            board.setObject(x5_ ,y5_, ' ');
        }
        if (hp6_ <= 0)
        {
            cout<<"Zombie 6 has no life left.";
            hp6_ = 0;
            board.setObject(x6_ ,y6_, ' ');
        }
        if (hp7_ <= 0)
        {
            cout<<"Zombie 7 has no life left.";
            hp7_ = 0;
            board.setObject(x7_ ,y7_, ' ');
        }
    }
    
    else if (num_ == 8)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }

        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
        if (hp3_ <= 0)
        {
            cout<<"Zombie 3 has no life left.";
            hp3_ = 0;
            board.setObject(x3_ ,y3_, ' ');
        }
        if (hp4_ <= 0)
        {
            cout<<"Zombie 4 has no life left.";
            hp4_ = 0;
            board.setObject(x4_ ,y4_, ' ');
        }
        if (hp5_ <= 0)
        {
            cout<<"Zombie 5 has no life left.";
            hp5_ = 0;
            board.setObject(x5_ ,y5_, ' ');
        }
        if (hp6_ <= 0)
        {
            cout<<"Zombie 6 has no life left.";
            hp6_ = 0;
            board.setObject(x6_ ,y6_, ' ');
        }
        if (hp7_ <= 0)
        {
            cout<<"Zombie 7 has no life left.";
            hp7_ = 0;
            board.setObject(x7_ ,y7_, ' ');
        }
        if (hp8_ <= 0)
        {
            cout<<"Zombie 8 has no life left.";
            hp8_ = 0;
            board.setObject(x8_ ,y8_, ' ');
        }
    }

    else if (num_ == 9)
    {
        for (int i = 1; i<=num_; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            seed = (rand()%5) - 1;
            if (seed == 1)
            {
                zombie.up(i);
                cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
            }
            else if (seed == 2)
            {
                zombie.down(i);
                cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
            }
            else if (seed == 3)
            {
                zombie.left(i);
                cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
            }
            else
            {
                zombie.right(i);
                cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (zombie.search(i) == 'A')
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<dmg1_<< " damage.";
                    alien.damage(dmg1_);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<dmg2_<< " damage.";
                    alien.damage(dmg2_);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<dmg3_<< " damage.";
                    alien.damage(dmg3_);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<dmg4_<< " damage.";
                    alien.damage(dmg4_);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<dmg5_<< " damage.";
                    alien.damage(dmg5_);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<dmg6_<< " damage.";
                    alien.damage(dmg6_);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<dmg7_<< " damage.";
                    alien.damage(dmg7_);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<dmg8_<< " damage.";
                    alien.damage(dmg8_);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<dmg9_<< " damage.";
                    alien.damage(dmg9_);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<" round is over.";
        }

        if (hp1_ <= 0)
        {
            cout<<"Zombie 1 has no life left.";
            hp1_ = 0;
            board.setObject(x1_ ,y1_, ' ');
        }
        if (hp2_ <= 0)
        {
            cout<<"Zombie 2 has no life left.";
            hp2_ = 0;
            board.setObject(x2_ ,y2_, ' ');
        }
        if (hp3_ <= 0)
        {
            cout<<"Zombie 3 has no life left.";
            hp3_ = 0;
            board.setObject(x3_ ,y3_, ' ');
        }
        if (hp4_ <= 0)
        {
            cout<<"Zombie 4 has no life left.";
            hp4_ = 0;
            board.setObject(x4_ ,y4_, ' ');
        }
        if (hp5_ <= 0)
        {
            cout<<"Zombie 5 has no life left.";
            hp5_ = 0;
            board.setObject(x5_ ,y5_, ' ');
        }
        if (hp6_ <= 0)
        {
            cout<<"Zombie 6 has no life left.";
            hp6_ = 0;
            board.setObject(x6_ ,y6_, ' ');
        }
        if (hp7_ <= 0)
        {
            cout<<"Zombie 7 has no life left.";
            hp7_ = 0;
            board.setObject(x7_ ,y7_, ' ');
        }
        if (hp8_ <= 0)
        {
            cout<<"Zombie 8 has no life left.";
            hp8_ = 0;
            board.setObject(x8_ ,y8_, ' ');
        }
        if (hp9_ <= 0)
        {
            cout<<"Zombie 9 has no life left.";
            hp9_ = 0;
            board.setObject(x9_ ,y9_, ' ');
        }
    }

    if(hp <= 0)
    {
        cout<<endl<<"The zombies has no life left. Game Over."<<endl;
        cout<<"The game will terminate in 5 seconds."<<endl<<endl;
        cout<<"5"<<endl;
        usleep(1000000);
        cout<<"4"<<endl;
        usleep(1000000);
        cout<<"3"<<endl;
        usleep(1000000);
        cout<<"2"<<endl;
        usleep(1000000);
        cout<<"1"<<endl;
        usleep(1000000);
        abort();
    }
    alien.main();
}

int main()
{
    Board board;
    Alien alien;
    string command;
    srand(4); // use this for fixed board during testing
    // srand(time(NULL)); // this for random board
    settings();
    //system("cls"); //undo before launch
    alien.main();
}

//!DONE
// *1. User health system
// *2. User attack system
//!2.1 pod (untested) (infinite loop)
//!2.2 close range (untested)
// !3. Damage system (untested)
// 4. Zombie positioning
// 5. User positioning
// !6. Zombie attack system (untested)
// *9. Quitting game
// *10. Help option

//TODO
// 7. Game saving
// 8. Game load