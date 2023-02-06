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
#include <algorithm>
using namespace std;

int X = 10, Y = 5, Z = 1;

void settings()
{
    char selection;

    while(true){
        cout << "Default game settings: " << endl;
        cout << "Board Rows: " <<  X <<" (Minimum of 1 row and maximum of 50 rows.)"<<endl;
        cout << "Board Columns:  " << Y <<" (Minimum of 1 columns and maximum of 50 columns.)" <<endl;
        cout << "Number of Zombies: "<< Z <<" (Minimum of 1 zombies and maximum of 9 zombies.)"<< endl;
        cout <<"Would You like to change the settings? (y/n)"<<endl;
        cin >> selection;
        cout <<endl;
        
        if (selection == 'Y' || selection == 'y'){
            cout << "New Board Rows: " ;
            cin >> X;
            while (true){
                if(cin.fail() || X > 50 || X <1){
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Board Rows: " ;
                    cin>>X;
                }
                else{
                    break;
                }
            }

            cout << "New Board Columns:  " ;
            cin >> Y;
            while (true){
                if(cin.fail() || Y >50 || Y <1){
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Board Columns:  " ;
                    cin>>Y;
                }
                else{
                    break;
                }
            }

            cout << "New Number of Zombies: ";
            cin >> Z;
            while (true){
                if(cin.fail() || Z>9 || Z<1){
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Number of Zombies: ";
                    cin>>Z;
                }
                else{
                    break;
                }
            }

            cout << "New settings saved"<< endl <<endl;
        }

        else if (selection == 'N' || selection == 'n'){
            break;
        }

        else{
            cout << "Invalid Selection"<<endl<<endl;
        }
    }
}

class Board
{
    private:
        vector<vector<char>> board_; // convention to put trailing underscore
        int boardX_, boardY_, zombies_;// to indicate private data

    public:
        Board(int boardX = X, int boardY = Y);
        void settings(int boardX, int boardY, int zombies);
        void init(int boardX, int boardY);
        void display() const;
        int getBoardX() const;
        int getBoardY() const;
        char getObject(int x, int y) const;
        void setObject(int x, int y, int ch);
        bool isEmpty(int x, int y, char ch);
        bool isInsideMap(int x, int y, int maxX, int maxY);
};

Board::Board(int boardX, int boardY)
{
    init(boardX, boardY);
}

bool Board::isEmpty(int x, int y, char ch)
{
    return x, y, (isblank(ch));
}

bool Board::isInsideMap(int x, int y, int maxX, int maxY)
{
    return (1<=x &&1<=y) && (x<=maxX && y<=maxY);
}

char Board::getObject(int x, int y) const
{
    return board_[boardY_-y][x-1];
}

void Board::setObject(int x, int y, int ch)
{
    board_[boardY_-y ][x-1 ] = ch;
}

void Board::init(int boardX,int boardY)
{
    boardX_ = boardX;
    boardY_ = boardY;
   
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'h', 'p', 'r', ' '};
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

    int numZombies;
    numZombies = Z;

    while (numZombies > 0)
    {
        cout<< "Zombie " <<numZombies<<" : "<<endl<<endl;
        numZombies--;
    }

}

int Board::getBoardX() const
{
    return boardX_;
}

int Board::getBoardY() const
{
    return boardY_;
}

class Alien
{
    private:
        int x_, y_;
        char heading_,alien_; // either '^', '>', '<' or 'v'
        
    public:
        Alien();
        void land(Board &board);
        int getX() const;
        int getY() const;
        char getHeading() const;
        void move(Board &board);
        void reverse(Board &board);
        void left(Board &board);
        void right(Board &board);
};

Alien::Alien()
{
}

void Alien::land(Board &board)
{
    x_ = board.getBoardX() / 2 + 1;
    y_ = board.getBoardY() / 2 + 1;
    heading_ = '^';
    alien_ = 'A';
    board.setObject(x_, y_, alien_);
}

int Alien::getX() const
{
    return x_;
}

int Alien::getY() const
{
    return y_;
}

char Alien::getHeading() const
{
    return heading_;
}

void Alien::move(Board &board)
{
    board.setObject(x_, y_, ' ');
        y_++;
    board.setObject(x_, y_, alien_);
}

void Alien::reverse(Board &board)
{
    board.setObject(x_, y_, ' ');
        y_--;
    board.setObject(x_, y_, alien_);
}

void Alien::left(Board &board)
{
    board.setObject(x_, y_, ' ');
        x_--;
    board.setObject(x_, y_, alien_);
}

void Alien::right(Board &board)
{
    board.setObject(x_, y_, ' ');
        x_++;
    board.setObject(x_, y_, alien_);
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
    alien.land(board);
    board.display();
    cout << "Status of the alien:" << endl
    << " Location: (" << alien.getX() << ", " << alien.getY() << ")"

    << endl

    << " Heading: " << alien.getHeading() << endl;
}

void test2_2()
{
    Board board;
    Alien alien;

    alien.land(board);
    board.display();
    cin.get(); //system("pause");

    alien.left(board);
    board.display();
    cin.get(); //system("pause");

    alien.move(board);
    board.display();
    cin.get(); //system("pause");

    alien.move(board);
    board.display();
    cin.get(); //system("pause");

    alien.right(board);
    board.display();
    cin.get(); //system("pause");

    alien.move(board);
    board.display();
}

void test2_3()
{
    Board board;
    Alien alien;
    string dir;

    alien.land(board);
    board.display();
    while(true){
        cout<<"Please enter a command(up/down/left/right): ";
        cin >>dir;
        transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
        if (dir == "up" || dir == "down" || dir == "left" || dir == "right"){
            break;
        }
        else
        {
            cout << "Entered wrong input, please try again." << endl<<endl;
        }
    }

    while (true)
    {

        if (dir == "left")
        {
            alien.left(board);
            board.display();

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y){
                cout<< "Alien has reached the edge, it will stop moving now.";
                break;
            }
        }

        else if (dir == "right")
        {
            alien.right(board);
            board.display();           

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y){
                cout<< "Alien has reached the edge, it will stop moving now.";
                break;
            }
        }

        else if (dir == "up")
        {
            alien.move(board);
            board.display(); 

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y){
                cout<< "Alien has reached the edge, it will stop moving now.";
                break;
            }
        }

        else
        {
            alien.reverse(board);
            board.display();

            if (alien.getX() == 1 || alien.getY() == 1 ||alien.getX() == X || alien.getY() == Y){
                cout<< "Alien has reached the edge, it will stop moving now.";
                break;
            }
        }
    }
}

int main(){
    srand(1); // use this for fixed board during testing
    // srand(time(NULL)); // this for random board
    //settings();
    test2_3();
}