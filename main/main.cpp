#include <vector>
#include <iostream>
#include <thread>
#include <random>

using namespace std;


class TwenyOne {
public:
    int COMPUTER = 0;
    int Player_Sum = 0;
    vector <int> fullDeck = {
    6,6,6,6,
    7,7,7,7,
    8,8,8,8,
    9,9,9,9,
    10,10,10,10,
    2,2,2,2,
    3,3,3,3,
    4,4,4,4,
    1,1,1,1,

    };
    int random_num() {
        return rand() % 36;
    }

    void menu() {
        auto key = 0;
        cout << "WELCOME IN OCHKO!" << endl;
        cout << "Enter any number to start a game!" << endl;
        cin >> key;
        start();
    }
    void check_abs() {
        if (COMPUTER > 21) {
            cout << "U won!" << endl;
        }
        if (Player_Sum > 21) {
            cout << "U lost!" << endl;
        }
    }

    void end() {
 
        
        if (COMPUTER == 21 and Player_Sum != 21) {
            cout << "you lost" << endl;
        }
        if ((COMPUTER > 21 and Player_Sum < 21) or Player_Sum == 21) {
            cout << "you won" << endl;
        }
        if (COMPUTER < 21 and COMPUTER < Player_Sum) {
            cout << "you won" << endl;
        }
        else {
            cout << "computer won";
        }
        if (Player_Sum == 21) {
            cout << "you won" << endl;
        }
    }

    void start() {
        check_abs();
        int a = 18;
        int b = 24;
        int COMPUTER = a + rand() % (b - a + 1);
        int num = random_num();
        int choosed_num;
        cout << "Oh u got a new card with value " << fullDeck[num] << endl;
        if (fullDeck[num] == 1) {
            cout << "choose between 11 and 1, you got a toose" << endl;
            cin >> choosed_num;
            if (choosed_num == 1) {
                Player_Sum += 1;
            }
            else {
                Player_Sum += 11;
            }
        }
        else {
            Player_Sum += fullDeck[num];
        }
        cout << "Your current sum is " << Player_Sum <<endl;
        cout << "Are u want to continue? 1/2" << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            start();
        }
        else {
            end();
        }
        
    }

};

int main()
{
    srand(time(0));
    TwenyOne sex;
    sex.menu();
}

