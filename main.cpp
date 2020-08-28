#include <iostream>

void greetAndInstruct();
void displayBoard(char board[]);
bool checkIfLegal (int cellNbre, char board[]);
bool checkWinner(char board[]);
void computerMove(char board[]);
using namespace std;

//Tianyi Zhang 260883657
int getUserInput()
{
    string input;
    cin>>input;
    if(input.compare("quit")==0)
        return -1; //-1 meaning the program should exit
    for(int i=0;i<input.size();i++)
    {
        if(!isdigit(input[i]))
        {return -2;} //-2 meaning illegal input
    }
    int convertedInput = stoi(input);
    return convertedInput;

}
int main() {
    greetAndInstruct(); //greet user
    char myBoard[28];
    for (int i=1;i<28;i++)
    {
        myBoard[i] = 'E';
    }
    cout << "Player starts first." << endl;
    bool firstLoop = true;
    while (true) {
        if (!firstLoop)
        {
            computerMove(myBoard);
            if (checkWinner(myBoard)) //check if there is a winner, before making a move or allowing the user to make a move
            {
                cout<<"The final situation of the board is"<<endl;
                displayBoard(myBoard);
                exit(0);
            }
        }
        firstLoop = false;
        cout << "The current status of the board is:" << endl; //show the current status of the board
        displayBoard(myBoard);
        cout << endl;
        cout << "Please enter the place where you would like to put 'X'"
             << endl; //prompt user to enter the place to put X; or quit to exit the game
        int input = 0;
        while (input < 1) //check if valid input, if input not valid then continue to ask the user
        {
            input = getUserInput();
            if (input == -1) //getUserInput() returns -2 when the user typed 'quit'
                exit(0);
            else if (input == -2)
                cout << "You have not entered a number. Please enter a number between 1 and 27" << endl;
            else if (!checkIfLegal(input, myBoard))
                cout
                        << "You have entered a place where you cannot put an 'X'. It may be occupied or out of range. Please enter a valid number"
                        << endl;
        }
        myBoard[input] = 'X';
        if (checkWinner(myBoard)) //if a winner has been found, then display the final situation and exit
        {
            cout<<"The final situation of the board is"<<endl;
            displayBoard(myBoard);
            exit(0);
        }
    }

}
