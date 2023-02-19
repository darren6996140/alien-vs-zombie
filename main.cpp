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
int Xa, Ya, HP = 100, DMG = 0;
int X1, Y1, HP1 = (rand() % 3 + 1) * 100, DMG1 = (rand() % 5 + 1) * 5, RNG1 = rand() % 4 + 1;
int X2, Y2, HP2 = (rand() % 3 + 1) * 100, DMG2 = (rand() % 5 + 1) * 5, RNG2 = rand() % 4 + 1;
int X3, Y3, HP3 = (rand() % 3 + 1) * 100, DMG3 = (rand() % 5 + 1) * 5, RNG3 = rand() % 4 + 1;
int X4, Y4, HP4 = (rand() % 3 + 1) * 100, DMG4 = (rand() % 5 + 1) * 5, RNG4 = rand() % 4 + 1;
int X5, Y5, HP5 = (rand() % 3 + 1) * 100, DMG5 = (rand() % 5 + 1) * 5, RNG5 = rand() % 4 + 1;
int X6, Y6, HP6 = (rand() % 3 + 1) * 100, DMG6 = (rand() % 5 + 1) * 5, RNG6 = rand() % 4 + 1;
int X7, Y7, HP7 = (rand() % 3 + 1) * 100, DMG7 = (rand() % 5 + 1) * 5, RNG7 = rand() % 4 + 1;
int X8, Y8, HP8 = (rand() % 3 + 1) * 100, DMG8 = (rand() % 5 + 1) * 5, RNG8 = rand() % 4 + 1;
int X9, Y9, HP9 = (rand() % 3 + 1) * 100, DMG9 = (rand() % 5 + 1) * 5, RNG9 = rand() % 4 + 1;

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
        int x_, y_;
        int x_, y_;
        char heading_,alien_;
        
    public:
        Alien();
        void landinit(Board &board);
        void land(Board &board);
        void land(Board &board);
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

    public:
        Zombie();
        void landinit(Board &board);
        void land(Board &board, int zombie);
        int getX(int zombie);
        int getY(int zombie);
        void land(Board &board, int zombie);
        int getX(int zombie);
        int getY(int zombie);
        void status();
        void up(int zombie);
        void down(int zombie);
        void left(int zombie);
        void right(int zombie);
        void damage(int zombie, int hp);
        void damage(int zombie, int hp);
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
    cout << "8. load     - Load a saved game" << endl;
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
}

void Alien::landinit(Board &board)
{
    x_ = board.getBoardX() / 2 + 1;
    y_ = board.getBoardY() / 2 + 1;
    heading_ = '^';
    alien_ = 'A';
    board.setObject(x_, y_, alien_);
}

void Alien::land(Board &board)
void Alien::land(Board &board)
{
    Alien alien;
    alien_ = 'A';
    board.setObject(Xa, Ya, alien_);
    alien_ = 'A';
    board.setObject(Xa, Ya, alien_);
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
    cout<<"Alien : Health - "<<HP<<", Damage - "<<DMG<<endl<<endl;
    cout<<"Alien : Health - "<<HP<<", Damage - "<<DMG<<endl<<endl;
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
            HP = HP + 20;
            HP = HP + 20;

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
        HP = HP + 20;
        HP = HP + 20;
    }

    else if (item == 'p')
    {
        cout<<"Alien finds a pod."<<endl;
        while (true)
        {
            //todo int zomX [9] = {zombie.getX(1), zombie.getX(2), zombie.getX(3), zombie.getX(4), zombie.getX(5), zombie.getX(6), zombie.getX(7), zombie.getX(8), zombie.getX(9)};
            //todo int zomY[9] = {zombie.getY(1), zombie.getY(2), zombie.getY(3), zombie.getY(4), zombie.getY(5), zombie.getY(6), zombie.getY(7), zombie.getY(8), zombie.getY(9)};
            //todo int zomX [9] = {zombie.getX(1), zombie.getX(2), zombie.getX(3), zombie.getX(4), zombie.getX(5), zombie.getX(6), zombie.getX(7), zombie.getX(8), zombie.getX(9)};
            //todo int zomY[9] = {zombie.getY(1), zombie.getY(2), zombie.getY(3), zombie.getY(4), zombie.getY(5), zombie.getY(6), zombie.getY(7), zombie.getY(8), zombie.getY(9)};
            int distance[9];
            int closest[2] = {100, 0};

            for (int i = 0; i < Z; ++i)
            {
                //distance[i] = zomX[i] + zomY[i];
                //distance[i] = zomX[i] + zomY[i];
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
        DMG = DMG + 20;
        DMG = DMG + 20;
        heading_ = '^';
    }

    else if (item == 'v')
    {
        cout<< "Alien finds a down arrow, alien will move down."<<endl<<"Alien's damage will increase by 20."<<endl;
        DMG = DMG + 20;
        DMG = DMG + 20;
        heading_ = 'v';
    }

    else if (item == '>')
    {
        cout<< "Alien finds a right arrow, alien will move right."<<endl<<"Alien's damage will increase by 20."<<endl;
        DMG = DMG + 20;
        DMG = DMG + 20;
        heading_ = '>';
    }

    else if (item == '<')
    {
        cout<< "Alien finds a left arrow, alien will move left."<<endl<<"Alien's damage will increase by 20."<<endl;
        DMG = DMG + 20;
        DMG = DMG + 20;
        heading_ = '<';
    }

    else if(item == '1' || item == '2' || item == '3' || item == '4' || item == '5' || item == '6' || item == '7' || item == '8' || item == '9')
    {
        if (item == '1')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(1, DMG);
            zombie.damage(1, DMG);
        }
        else if (item == '2')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(2, DMG);
            zombie.damage(2, DMG);
        }
        else if (item == '3')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(3, DMG);
            zombie.damage(3, DMG);
        }
        else if (item == '4')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(4, DMG);
            zombie.damage(4, DMG);
        }
        else if (item == '5')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(5, DMG);
            zombie.damage(5, DMG);
        }
        else if (item == '6')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(6, DMG);
            zombie.damage(6, DMG);
        }
        else if (item == '7')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(7, DMG);
            zombie.damage(7, DMG);
        }
        else if (item == '8')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(8, DMG);
            zombie.damage(8, DMG);
        }
        else if (item == '9')
        {
            cout<< "Alien attacks Zombie "<<item<<" ."<<endl;
            zombie.damage(9, DMG);
            zombie.damage(9, DMG);
        }
    }
    else
    {
    }
    return item;
}

void Alien::damage(int hp)
{
    HP = HP - hp;
    HP = HP - hp;
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
}

void Zombie::landinit(Board &board)
{
    X1 = rand() % X + 1; Y1 = rand() % Y + 1;
    X2 = rand() % X + 1; Y2 = rand() % Y + 1;
    X3 = rand() % X + 1; Y3 = rand() % Y + 1;
    X4 = rand() % X + 1; Y4 = rand() % Y + 1;
    X5 = rand() % X + 1; Y5 = rand() % Y + 1;
    X6 = rand() % X + 1; Y6 = rand() % Y + 1;
    X7 = rand() % X + 1; Y7 = rand() % Y + 1;
    X8 = rand() % X + 1; Y8 = rand() % Y + 1;
    X9 = rand() % X + 1; Y9 = rand() % Y + 1;
    X1 = rand() % X + 1; Y1 = rand() % Y + 1;
    X2 = rand() % X + 1; Y2 = rand() % Y + 1;
    X3 = rand() % X + 1; Y3 = rand() % Y + 1;
    X4 = rand() % X + 1; Y4 = rand() % Y + 1;
    X5 = rand() % X + 1; Y5 = rand() % Y + 1;
    X6 = rand() % X + 1; Y6 = rand() % Y + 1;
    X7 = rand() % X + 1; Y7 = rand() % Y + 1;
    X8 = rand() % X + 1; Y8 = rand() % Y + 1;
    X9 = rand() % X + 1; Y9 = rand() % Y + 1;

    if (Z == 1)
    if (Z == 1)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X1, Y1, '1');
    }

    else if (Z == 2)
    else if (Z == 2)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
    }

    else if (Z == 3)
    else if (Z == 3)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
    }

    else if (Z == 4)
    else if (Z == 4)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
    }

    else if (Z == 5)
    else if (Z == 5)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
    }

    else if (Z == 6)
    else if (Z == 6)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
    }

    else if (Z == 7)
    else if (Z == 7)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
    }
    
    else if (Z == 8)
    else if (Z == 8)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
    }

    else if (Z == 9)
    else if (Z == 9)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
        board.setObject(X9, Y9, '9');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
        board.setObject(X9, Y9, '9');
    }
}

void Zombie::land(Board &board, int zombie)
void Zombie::land(Board &board, int zombie)
{
    if (zombie == 1)
    if (zombie == 1)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X1, Y1, '1');
    }

    else if (zombie == 2)
    else if (zombie == 2)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
    }

    else if (zombie == 3)
    else if (zombie == 3)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
    }

    else if (zombie == 4)
    else if (zombie == 4)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
    }

    else if (zombie == 5)
    else if (zombie == 5)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
    }

    else if (zombie == 6)
    else if (zombie == 6)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
    }

    else if (zombie == 7)
    else if (zombie == 7)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
    }
    
    else if (zombie == 8)
    else if (zombie == 8)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
    }

    else if (zombie == 9)
    else if (zombie == 9)
    {
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
        board.setObject(X9, Y9, '9');
        board.setObject(X1, Y1, '1');
        board.setObject(X2, Y2, '2');
        board.setObject(X3, Y3, '3');
        board.setObject(X4, Y4, '4');
        board.setObject(X5, Y5, '5');
        board.setObject(X6, Y6, '6');
        board.setObject(X7, Y7, '7');
        board.setObject(X8, Y8, '8');
        board.setObject(X9, Y9, '9');
    }
}

=======
>>>>>>> Stashed changes
void Zombie::status()
{
    if (Z == 1)
    if (Z == 1)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
    }

    else if (Z == 2)
    else if (Z == 2)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
    }

    else if (Z == 3)
    else if (Z == 3)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
    }

    else if (Z == 4)
    else if (Z == 4)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
    }

    else if (Z == 5)
    else if (Z == 5)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
    }

    else if (Z == 6)
    else if (Z == 6)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
    }

    else if (Z == 7)
    else if (Z == 7)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<HP7<<", Damage - "<<DMG7<<", Range - "<<RNG7<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<HP7<<", Damage - "<<DMG7<<", Range - "<<RNG7<<endl<<endl;
    }
    
    else if (Z == 8)
    else if (Z == 8)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<HP7<<", Damage - "<<DMG7<<", Range - "<<RNG7<<endl<<endl;
        cout<<"Zombie 8 : Health - "<<HP8<<", Damage - "<<DMG8<<", Range - "<<RNG8<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<HP7<<", Damage - "<<DMG7<<", Range - "<<RNG7<<endl<<endl;
        cout<<"Zombie 8 : Health - "<<HP8<<", Damage - "<<DMG8<<", Range - "<<RNG8<<endl<<endl;
    }

    else if (Z == 9)
    else if (Z == 9)
    {
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<HP7<<", Damage - "<<DMG7<<", Range - "<<RNG7<<endl<<endl;
        cout<<"Zombie 8 : Health - "<<HP8<<", Damage - "<<DMG8<<", Range - "<<RNG8<<endl<<endl;
        cout<<"Zombie 9 : Health - "<<HP9<<", Damage - "<<DMG9<<", Range - "<<RNG9<<endl<<endl;
        cout<<"Zombie 1 : Health - "<<HP1<<", Damage - "<<DMG1<<", Range - "<<RNG1<<endl<<endl;
        cout<<"Zombie 2 : Health - "<<HP2<<", Damage - "<<DMG2<<", Range - "<<RNG2<<endl<<endl;
        cout<<"Zombie 3 : Health - "<<HP3<<", Damage - "<<DMG3<<", Range - "<<RNG3<<endl<<endl;
        cout<<"Zombie 4 : Health - "<<HP4<<", Damage - "<<DMG4<<", Range - "<<RNG4<<endl<<endl;
        cout<<"Zombie 5 : Health - "<<HP5<<", Damage - "<<DMG5<<", Range - "<<RNG5<<endl<<endl;
        cout<<"Zombie 6 : Health - "<<HP6<<", Damage - "<<DMG6<<", Range - "<<RNG6<<endl<<endl;
        cout<<"Zombie 7 : Health - "<<HP7<<", Damage - "<<DMG7<<", Range - "<<RNG7<<endl<<endl;
        cout<<"Zombie 8 : Health - "<<HP8<<", Damage - "<<DMG8<<", Range - "<<RNG8<<endl<<endl;
        cout<<"Zombie 9 : Health - "<<HP9<<", Damage - "<<DMG9<<", Range - "<<RNG9<<endl<<endl;
    }
}

void Zombie::up(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(X1, Y1, ' ');
        Y1++;
        board.setObject(X1, Y1, ' ');
        Y1++;
    }

    else if (zombie == 2)
    {
        board.setObject(X2, Y2, ' ');
        Y2++;
        board.setObject(X2, Y2, ' ');
        Y2++;
    }

    else if (zombie == 3)
    {
        board.setObject(X3, Y3, ' ');
        Y3++;
        board.setObject(X3, Y3, ' ');
        Y3++;
    }

    else if (zombie == 4)
    {
        board.setObject(X4, Y4, ' ');
        Y4++;
        board.setObject(X4, Y4, ' ');
        Y4++;
    }

    else if (zombie == 5)
    {
        board.setObject(X5, Y5, ' ');
        Y5++;
        board.setObject(X5, Y5, ' ');
        Y5++;
    }

    else if (zombie == 6)
    {
        board.setObject(X6, Y6, ' ');
        Y6++;
        board.setObject(X6, Y6, ' ');
        Y6++;
    }

    else if (zombie == 7)
    {
        board.setObject(X7, Y7, ' ');
        Y7++;
        board.setObject(X7, Y7, ' ');
        Y7++;
    }
    
    else if (zombie == 8)
    {
        board.setObject(X8, Y8, ' ');
        Y8++;
        board.setObject(X8, Y8, ' ');
        Y8++;
    }

    else if (zombie == 9)
    {
        board.setObject(X9, Y9, ' ');
        Y9++;
        board.setObject(X9, Y9, ' ');
        Y9++;
    }
}

void Zombie::down(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(X1, Y1, ' ');
        Y1--;
        board.setObject(X1, Y1, ' ');
        Y1--;
    }

    else if (zombie == 2)
    {
        board.setObject(X2, Y2, ' ');
        Y2--;
        board.setObject(X2, Y2, ' ');
        Y2--;
    }

    else if (zombie == 3)
    {
        board.setObject(X3, Y3, ' ');
        Y3--;
        board.setObject(X3, Y3, ' ');
        Y3--;
    }

    else if (zombie == 4)
    {
        board.setObject(X4, Y4, ' ');
        Y4--;
        board.setObject(X4, Y4, ' ');
        Y4--;
    }

    else if (zombie == 5)
    {
        board.setObject(X5, Y5, ' ');
        Y5--;
        board.setObject(X5, Y5, ' ');
        Y5--;
    }

    else if (zombie == 6)
    {
        board.setObject(X6, Y6, ' ');
        Y6--;
        board.setObject(X6, Y6, ' ');
        Y6--;
    }

    else if (zombie == 7)
    {
        board.setObject(X7, Y7, ' ');
        Y7--;
        board.setObject(X7, Y7, ' ');
        Y7--;
    }
    
    else if (zombie == 8)
    {
        board.setObject(X8, Y8, ' ');
        Y8--;
        board.setObject(X8, Y8, ' ');
        Y8--;
    }

    else if (zombie == 9)
    {
        board.setObject(X9, Y9, ' ');
        Y9--;
        board.setObject(X9, Y9, ' ');
        Y9--;
    }
}

void Zombie::left(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(X1, Y1, ' ');
        X1--;
        board.setObject(X1, Y1, ' ');
        X1--;
    }

    else if (zombie == 2)
    {
        board.setObject(X2, Y2, ' ');
        X2--;
        board.setObject(X2, Y2, ' ');
        X2--;
    }

    else if (zombie == 3)
    {
        board.setObject(X3, Y3, ' ');
        X3--;
        board.setObject(X3, Y3, ' ');
        X3--;
    }

    else if (zombie == 4)
    {
        board.setObject(X4, Y4, ' ');
        X4--;
        board.setObject(X4, Y4, ' ');
        X4--;
    }

    else if (zombie == 5)
    {
        board.setObject(X5, Y5, ' ');
        X5--;
        board.setObject(X5, Y5, ' ');
        X5--;
    }

    else if (zombie == 6)
    {
        board.setObject(X6, Y6, ' ');
        X6--;
        board.setObject(X6, Y6, ' ');
        X6--;
    }

    else if (zombie == 7)
    {
        board.setObject(X7, Y7, ' ');
        X7--;
        board.setObject(X7, Y7, ' ');
        X7--;
    }
    
    else if (zombie == 8)
    {
        board.setObject(X8, Y8, ' ');
        X8--;
        board.setObject(X8, Y8, ' ');
        X8--;
    }

    else if (zombie == 9)
    {
        board.setObject(X9, Y9, ' ');
        X9--;
        board.setObject(X9, Y9, ' ');
        X9--;
    }
}

void Zombie::right(int zombie)
{
    Board board;
    if (zombie == 1)
    {
        board.setObject(X1, Y1, ' ');
        X1++;
        board.setObject(X1, Y1, ' ');
        X1++;
    }

    else if (zombie == 2)
    {
        board.setObject(X2, Y2, ' ');
        X2++;
        board.setObject(X2, Y2, ' ');
        X2++;
    }

    else if (zombie == 3)
    {
        board.setObject(X3, Y3, ' ');
        X3++;
        board.setObject(X3, Y3, ' ');
        X3++;
    }

    else if (zombie == 4)
    {
        board.setObject(X4, Y4, ' ');
        X4++;
        board.setObject(X4, Y4, ' ');
        X4++;
    }

    else if (zombie == 5)
    {
        board.setObject(X5, Y5, ' ');
        X5++;
        board.setObject(X5, Y5, ' ');
        X5++;
    }

    else if (zombie == 6)
    {
        board.setObject(X6, Y6, ' ');
        X6++;
        board.setObject(X6, Y6, ' ');
        X6++;
    }

    else if (zombie == 7)
    {
        board.setObject(X7, Y7, ' ');
        X7++;
        board.setObject(X7, Y7, ' ');
        X7++;
    }
    
    else if (zombie == 8)
    {
        board.setObject(X8, Y8, ' ');
        X8++;
        board.setObject(X8, Y8, ' ');
        X8++;
    }

    else if (zombie == 9)
    {
        board.setObject(X9, Y9, ' ');
        X9++;
        board.setObject(X9, Y9, ' ');
        X9++;
    }
}

void Zombie::damage(int zombie, int hp)
void Zombie::damage(int zombie, int hp)
{
    if (zombie == 1)
    {
        HP1 = HP1 - hp;
    }
        HP1 = HP1 - hp;
    }

    else if (zombie == 2)
    {
        HP2 = HP2 - hp;
    }
        HP2 = HP2 - hp;
    }

    else if (zombie == 3)
    {
        HP3 = HP3 - hp;
    }
        HP3 = HP3 - hp;
    }

    else if (zombie == 4)
    {
        HP4 = HP4 - hp;
    }
        HP4 = HP4 - hp;
    }

    else if (zombie == 5)
    {
        HP5 = HP5 - hp;
    }
        HP5 = HP5 - hp;
    }

    else if (zombie == 6)
    {
        HP6 = HP6 - hp;
    }
        HP6 = HP6 - hp;
    }

    else if (zombie == 7)
    {
        HP7 = HP7 - hp;
    }

        HP7 = HP7 - hp;
    }

    else if (zombie == 8)
    {
        HP8 = HP8 - hp;
    }
        HP8 = HP8 - hp;
    }

    else if (zombie == 9)
    {
        HP9 = HP9 - hp;
    }
}
        HP9 = HP9 - hp;
    }
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
        alien.land(board);
        zombie.land(board, Z);
        alien.land(board);
        zombie.land(board, Z);
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
                DMG = 0;
                DMG = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                DMG = 0;
                DMG = 0;
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
                DMG = 0;
                DMG = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                DMG = 0;
                DMG = 0;
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
                DMG = 0;
                DMG = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                DMG = 0;
                DMG = 0;
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
                DMG = 0;
                DMG = 0;
                alien.reset();
                break;
            }

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y)
            {
                cout<< "Alien has reached the edge, it's turn will stop now."<<endl<<"Trail has been resetted."<<endl<<endl;
                DMG = 0;
                DMG = 0;
                alien.reset();
                break;
            }
        }
    }

    if(HP <= 0)
    if(HP <= 0)
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

    else if(Z == 0)
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

    x_ = alien.getX(); y_ = alien.getY();
    Xa = x_; Ya = y_;
    Xa = x_; Ya = y_;
    zombie.main();
}

void Zombie::main()
{
    Board board;
    Alien alien;
    Zombie zombie;
    int seed;

    alien.land(board);
    zombie.land(board, Z);
    alien.land(board);
    zombie.land(board, Z);
    board.display();
    alien.status();
    zombie.status();
    confirm();
    //system("cls"); //undo before launch

    if (Z == 1)
    if (Z == 1)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y1 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y1 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X1 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X1 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }
        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
    }

    else if (Z == 2)
    else if (Z == 2)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y2 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y2 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X2 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X2 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }

        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
    }

    else if (Z == 3)
    else if (Z == 3)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y3 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y3 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X3 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X3 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }
        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
        if (HP3 <= 0)
        if (HP3 <= 0)
        {
            cout<<"Zombie 3 has no life left."<<endl;
            Z = Z - 1;
            HP3 = 0;
            board.setObject(X3 ,Y3, ' ');
        }
    }

    else if (Z == 4)
    else if (Z == 4)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y4 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y4 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X4 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X4 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }

        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
        if (HP3 <= 0)
        if (HP3 <= 0)
        {
            cout<<"Zombie 3 has no life left."<<endl;
            Z = Z - 1;
            HP3 = 0;
            board.setObject(X3 ,Y3, ' ');
        }
        if (HP4 <= 0)
        if (HP4 <= 0)
        {
            cout<<"Zombie 4 has no life left."<<endl;
            Z = Z - 1;
            HP4 = 0;
            board.setObject(X4 ,Y4, ' ');
        }
    }

    else if (Z == 5)
    else if (Z == 5)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while(true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y5 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y5 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X5 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X5 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }

        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
        if (HP3 <= 0)
        if (HP3 <= 0)
        {
            cout<<"Zombie 3 has no life left."<<endl;
            Z = Z - 1;
            HP3 = 0;
            board.setObject(X3 ,Y3, ' ');
        }
        if (HP4 <= 0)
        if (HP4 <= 0)
        {
            cout<<"Zombie 4 has no life left."<<endl;
            Z = Z - 1;
            HP4 = 0;
            board.setObject(X4 ,Y4, ' ');
        }
        if (HP5 <= 0)
        if (HP5 <= 0)
        {
            cout<<"Zombie 5 has no life left."<<endl;
            Z = Z - 1;
            HP5 = 0;
            board.setObject(X5 ,Y5, ' ');
        }
    }

    else if (Z == 6)
    else if (Z == 6)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y6 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y6 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X6 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X6 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }

        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
        if (HP3 <= 0)
        if (HP3 <= 0)
        {
            cout<<"Zombie 3 has no life left."<<endl;
            Z = Z - 1;
            HP3 = 0;
            board.setObject(X3 ,Y3, ' ');
        }
        if (HP4 <= 0)
        if (HP4 <= 0)
        {
            cout<<"Zombie 4 has no life left."<<endl;
            Z = Z - 1;
            HP4 = 0;
            board.setObject(X4 ,Y4, ' ');
        }
        if (HP5 <= 0)
        if (HP5 <= 0)
        {
            cout<<"Zombie 5 has no life left."<<endl;
            Z = Z - 1;
            HP5 = 0;
            board.setObject(X5 ,Y5, ' ');
        }
        if (HP6 <= 0)
        if (HP6 <= 0)
        {
            cout<<"Zombie 6 has no life left."<<endl;
            Z = Z - 1;
            HP6 = 0;
            board.setObject(X6 ,Y6, ' ');
        }
    }

    else if (Z == 7)
    else if (Z == 7)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y7 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y7 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X7 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X7 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }

        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
        if (HP3 <= 0)
        if (HP3 <= 0)
        {
            cout<<"Zombie 3 has no life left."<<endl;
            Z = Z - 1;
            HP3 = 0;
            board.setObject(X3 ,Y3, ' ');
        }
        if (HP4 <= 0)
        if (HP4 <= 0)
        {
            cout<<"Zombie 4 has no life left."<<endl;
            Z = Z - 1;
            HP4 = 0;
            board.setObject(X4 ,Y4, ' ');
        }
        if (HP5 <= 0)
        if (HP5 <= 0)
        {
            cout<<"Zombie 5 has no life left."<<endl;
            Z = Z - 1;
            HP5 = 0;
            board.setObject(X5 ,Y5, ' ');
        }
        if (HP6 <= 0)
        if (HP6 <= 0)
        {
            cout<<"Zombie 6 has no life left."<<endl;
            Z = Z - 1;
            HP6 = 0;
            board.setObject(X6 ,Y6, ' ');
        }
        if (HP7 <= 0)
        if (HP7 <= 0)
        {
            cout<<"Zombie 7 has no life left."<<endl;
            Z = Z - 1;
            HP7 = 0;
            board.setObject(X7 ,Y7, ' ');
        }
    }
    
    else if (Z == 8)
    else if (Z == 8)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y8 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y8 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X8 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X8 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }

        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
        if (HP3 <= 0)
        if (HP3 <= 0)
        {
            cout<<"Zombie 3 has no life left."<<endl;
            Z = Z - 1;
            HP3 = 0;
            board.setObject(X3 ,Y3, ' ');
        }
        if (HP4 <= 0)
        if (HP4 <= 0)
        {
            cout<<"Zombie 4 has no life left."<<endl;
            Z = Z - 1;
            HP4 = 0;
            board.setObject(X4 ,Y4, ' ');
        }
        if (HP5 <= 0)
        if (HP5 <= 0)
        {
            cout<<"Zombie 5 has no life left."<<endl;
            Z = Z - 1;
            HP5 = 0;
            board.setObject(X5 ,Y5, ' ');
        }
        if (HP6 <= 0)
        if (HP6 <= 0)
        {
            cout<<"Zombie 6 has no life left."<<endl;
            Z = Z - 1;
            HP6 = 0;
            board.setObject(X6 ,Y6, ' ');
        }
        if (HP7 <= 0)
        if (HP7 <= 0)
        {
            cout<<"Zombie 7 has no life left."<<endl;
            Z = Z - 1;
            HP7 = 0;
            board.setObject(X7 ,Y7, ' ');
        }
        if (HP8 <= 0)
        if (HP8 <= 0)
        {
            cout<<"Zombie 8 has no life left."<<endl;
            Z = Z - 1;
            HP8 = 0;
            board.setObject(X8 ,Y8, ' ');
        }
    }

    else if (Z == 9)
    else if (Z == 9)
    {
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        int diffX, diffY, range;
        for (int i = 1; i<=Z; ++i)
        {
            cout<<"Zombie "<<i<<" turn starts."<<endl;
            while (true)
            {
                seed = (rand()%5) - 1;
                if (seed == 1 && Y9 != Y)
                {
                    zombie.up(i);
                    cout<<"Zombie "<<i<<" has moved up."<<endl<<endl;
                    break;
                }
                else if (seed == 2 && Y9 != 1)
                {
                    zombie.down(i);
                    cout<<"Zombie "<<i<<" has moved down."<<endl<<endl;
                    break;
                }
                else if (seed == 3 && X9 != 1)
                {
                    zombie.left(i);
                    cout<<"Zombie "<<i<<" has moved left."<<endl<<endl;
                    break;
                }
                else if (seed == 4 && X9 != X)
                {
                    zombie.right(i);
                    cout<<"Zombie "<<i<<" has moved right."<<endl<<endl;
                    break;
                }
            }
            board.display();
            alien.status();
            zombie.status();
            confirm();

            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            for (int j = 1; j<=Z; ++j)
            {
                if(i == 1)
                {
                    diffX = Xa - X1;
                    diffY = Ya - Y1;
                    range = RNG1;
                }

                else if(i == 2)
                {
                    diffX = Xa - X2;
                    diffY = Ya - Y2;
                    range = RNG2;
                }

                else if(i == 3)
                {
                    diffX = Xa - X3;
                    diffY = Ya - Y3;
                    range = RNG3;
                }

                else if(i == 4)
                {
                    diffX = Xa - X4;
                    diffY = Ya - Y4;
                    range = RNG4;
                }

                else if(i == 5)
                {
                    diffX = Xa - X5;
                    diffY = Ya - Y5;
                    range = RNG5;
                }

                else if(i == 6)
                {
                    diffX = Xa - X6;
                    diffY = Ya - Y6;
                    range = RNG6;
                }

                else if(i == 7)
                {
                    diffX = Xa - X7;
                    diffY = Ya - Y7;
                    range = RNG7;
                }

                else if(i == 8)
                {
                    diffX = Xa - X8;
                    diffY = Ya - Y8;
                    range = RNG8;
                }

                else if(i == 9)
                {
                    diffX = Xa - X9;
                    diffY = Ya - Y9;
                    range = RNG9;
                }
            }

            if (diffX <= range || diffX <= -range || diffY <= range || diffY <= -range)
            {
                cout<<"Alien is in range of Zombie "<<i<<"."<<endl;
                if (i == 1)
                {
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                    cout<<"Alien takes "<<DMG1<< " damage."<<endl<<endl;
                    alien.damage(DMG1);
                }
                else if (i == 2)
                {
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                    cout<<"Alien takes "<<DMG2<< " damage."<<endl<<endl;
                    alien.damage(DMG2);
                }
                else if (i == 3)
                {
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                    cout<<"Alien takes "<<DMG3<< " damage."<<endl<<endl;
                    alien.damage(DMG3);
                }
                else if (i == 4)
                {
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                    cout<<"Alien takes "<<DMG4<< " damage."<<endl<<endl;
                    alien.damage(DMG4);
                }
                else if (i == 5)
                {
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                    cout<<"Alien takes "<<DMG5<< " damage."<<endl<<endl;
                    alien.damage(DMG5);
                }
                else if (i == 6)
                {
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                    cout<<"Alien takes "<<DMG6<< " damage."<<endl<<endl;
                    alien.damage(DMG6);
                }
                else if (i == 7)
                {
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                    cout<<"Alien takes "<<DMG7<< " damage."<<endl<<endl;
                    alien.damage(DMG7);
                }
                else if (i == 8)
                {
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                    cout<<"Alien takes "<<DMG8<< " damage."<<endl<<endl;
                    alien.damage(DMG8);
                }
                else if (i == 9)
                {
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                    cout<<"Alien takes "<<DMG9<< " damage."<<endl<<endl;
                    alien.damage(DMG9);
                }
                board.display();
                alien.status();
                zombie.status();
                confirm();
            }
            cout<<"Zombie "<<i<<"'s round is over."<<endl<<endl;
        }

        if (HP1 <= 0)
        if (HP1 <= 0)
        {
            cout<<"Zombie 1 has no life left."<<endl;
            Z = Z - 1;
            HP1 = 0;
            board.setObject(X1 ,Y1, ' ');
        }
        if (HP2 <= 0)
        if (HP2 <= 0)
        {
            cout<<"Zombie 2 has no life left."<<endl;
            Z = Z - 1;
            HP2 = 0;
            board.setObject(X2 ,Y2, ' ');
        }
        if (HP3 <= 0)
        if (HP3 <= 0)
        {
            cout<<"Zombie 3 has no life left."<<endl;
            Z = Z - 1;
            HP3 = 0;
            board.setObject(X3 ,Y3, ' ');
        }
        if (HP4 <= 0)
        if (HP4 <= 0)
        {
            cout<<"Zombie 4 has no life left."<<endl;
            Z = Z - 1;
            HP4 = 0;
            board.setObject(X4 ,Y4, ' ');
        }
        if (HP5 <= 0)
        if (HP5 <= 0)
        {
            cout<<"Zombie 5 has no life left."<<endl;
            Z = Z - 1;
            HP5 = 0;
            board.setObject(X5 ,Y5, ' ');
        }
        if (HP6 <= 0)
        if (HP6 <= 0)
        {
            cout<<"Zombie 6 has no life left."<<endl;
            Z = Z - 1;
            HP6 = 0;
            board.setObject(X6 ,Y6, ' ');
        }
        if (HP7 <= 0)
        if (HP7 <= 0)
        {
            cout<<"Zombie 7 has no life left."<<endl;
            Z = Z - 1;
            HP7 = 0;
            board.setObject(X7 ,Y7, ' ');
        }
        if (HP8 <= 0)
        if (HP8 <= 0)
        {
            cout<<"Zombie 8 has no life left."<<endl;
            Z = Z - 1;
            HP8 = 0;
            board.setObject(X8 ,Y8, ' ');
        }
        if (HP9 <= 0)
        if (HP9 <= 0)
        {
            cout<<"Zombie 9 has no life left."<<endl;
            Z = Z - 1;
            HP9 = 0;
            board.setObject(X9 ,Y9, ' ');
        }
    }

    if(Z == 0)
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

    else if(HP <= 0)
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
// *3. Damage system
// *4. Zombie positioning
// *5. User positioning
// *6. Zombie attack system
// *9. Quitting game
// *10. Help option

//TODO
// 7. Game saving
// 8. Game load