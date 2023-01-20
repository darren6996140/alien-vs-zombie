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
using namespace std;

int zombies = 1;

void resetScreen(){

}

int gameSettings(){
    int boardX = 10;
    int boardY = 5;
    char selection;

    while(true){
        cout << "Default game settings: " << endl;
        cout << "Board Rows: " <<  boardX << endl;
        cout << "Board Columns:  " << boardY << endl;
        cout << "Number of Zombies: "<< zombies << endl;
        cout <<"Would You like to change the settings? (y/n)"<<endl;
        cin >> selection;
        cout <<endl;
        
        if (selection == 'Y' || selection == 'y'){

            cout << "New Board Rows: " ;
            cin >> boardX;
            while (true){
                if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Board Rows: " ;
                    cin>>boardX;
                }
                else{
                    break;
                }
            }

            cout << "New Board Columns:  " ;
            cin >> boardY;
            while (true){
                if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Board Columns:  " ;
                    cin>>boardY;
                }
                else{
                    break;
                }
            }

            cout << "New Number of Zombies: ";
            cin >> zombies;
            while (true){
                if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    cout<<"You have entered wrong input, enter again: "<<endl;
                    cout << "New Number of Zombies: ";
                    cin>>zombies;
                }
                else{
                    break;
                }
            }

            cout << "New settings saved"<< endl;
        }

        else if (selection == 'N' || selection == 'n'){
            cout << "no";
            break;
        }

        else{
            cout << "Invalid Selection"<<endl<<endl;
        }
    }

    //int board[][];
    //return board;
}
void quitGame(){

}

int main(){
    gameSettings();
}