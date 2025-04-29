
#include "includes.h"


using namespace std;

condition_variable cv_second, cv_third, cv_first, cv_fourth;

mutex mtx;


void first();
void second();
void third();
void fourth();


struct GameData {
    int random_num = 0;
    int first_player_sum = 0;
    int second_player_sum = 0;
    vector<int> first_player_nums;
    vector<int> second_player_nums;
    condition_variable cv_first, cv_second, cv_third, cv_fourth;
    mutex mtx;
    bool ready = false;
    bool stopthread = false;
    int games = 0;
    int WHOWINS = 0;
    int step = 2;
};

GameData gameData;

void check();

void first() {
    srand(time(0));
    int a = 1;
    int b = 11;
    while (!gameData.stopthread) {
        unique_lock<mutex> lock(mtx);

        gameData.random_num = a + rand() % (b - a + 1);
        if (gameData.step % 2 == 0) {
            cv_second.notify_one();
            cv_first.wait(lock, [] { return gameData.random_num == 0; });
        }
        if (gameData.step % 2 != 0) {
            cv_third.notify_one();
            cv_first.wait(lock, [] { return gameData.random_num == 0; });
        }
    }
}
void second() {
    while (!gameData.stopthread) {
        check();
        unique_lock<mutex> lock(mtx);
        cv_second.wait(lock, [] { return gameData.random_num != 0; });
        gameData.first_player_sum += gameData.random_num;
        gameData.first_player_nums.push_back(gameData.random_num);

        if (gameData.first_player_sum == 21) {
            cout << "first won with " << gameData.first_player_sum << endl;
            gameData.WHOWINS = 1;
            gameData.games++;
            gameData.ready = true;
            cv_fourth.notify_one();

        }
        else if (gameData.first_player_sum > 21) {
            if (gameData.second_player_sum > 21) {
                cout << "both player lost" << endl;
                gameData.WHOWINS = 0;
                gameData.games++;
                gameData.ready = true;
                cv_fourth.notify_one();

            }
            else {
                cout << "second won with " << gameData.second_player_sum << endl;
                gameData.WHOWINS = 2;
                gameData.games++;
                gameData.ready = true;
                cv_fourth.notify_one();

            }
        }
        gameData.random_num = 0;
        gameData.step++;
        cv_first.notify_one();
    }
}

void third() {
    while (!gameData.stopthread) {
        check();
        unique_lock<mutex> lock(mtx);
        cv_third.wait(lock, [] { return gameData.random_num != 0; });
        gameData.second_player_sum += gameData.random_num;
        gameData.second_player_nums.push_back(gameData.random_num);
        if (gameData.second_player_sum == 21) {
            cout << "second won with " << gameData.second_player_sum << endl;
            gameData.WHOWINS = 2;
            gameData.games++;
            gameData.ready = true;
            cv_fourth.notify_one();

        }
        else if (gameData.second_player_sum > 21) {
            if (gameData.first_player_sum > 21) {
                cout << "both player lost" << endl;
                gameData.WHOWINS = 0;
                gameData.games++;
                gameData.ready = true;
                cv_fourth.notify_one();

            }
            else {
                cout << "first won with " << gameData.first_player_sum << endl;
                gameData.WHOWINS = 1;
                gameData.games++;
                gameData.ready = true;
                cv_fourth.notify_one();

            }
        }
        gameData.random_num = 0;
        gameData.step++;
        cv_first.notify_one();
    }
}
void fourth() {
    while (!gameData.stopthread) {
        unique_lock<mutex> lock(mtx);
        cv_fourth.wait(lock, [] { return gameData.ready; });
        ofstream outFile("results.txt", std::ios::app);
        if (outFile.is_open()) {
            if (gameData.WHOWINS == 1) {
                outFile << "FIRST PLAYER WINS in game #" << gameData.games + 1 << endl;
                outFile << "FIRST PLAYER SUM " << gameData.first_player_sum << endl;
                outFile << "SECOND PLAYER SUM " << gameData.second_player_sum << endl;
                outFile << "FIRST PLAYER NUMS IS ";
                for (int i : gameData.first_player_nums) {
                    outFile << i << " ";
                }
                outFile << endl << "SECOND PLAYER NUMS IS ";
                for (int i : gameData.second_player_nums) {
                    outFile << i << " ";
                }
                outFile << endl << "------------" <<  endl;
            }
            else if (gameData.WHOWINS == 2) {
                outFile << "SECOND PLAYER WINS in game #" << gameData.games + 1 << endl;
                outFile << "FIRST PLAYER SUM " << gameData.first_player_sum << endl;
                outFile << "SECOND PLAYER SUM " << gameData.second_player_sum << endl;
                outFile << "FIRST PLAYER NUMS IS ";
                for (int i : gameData.first_player_nums) {
                    outFile << i << " ";
                }
                outFile << endl << "SECOND PLAYER NUMS IS ";
                for (int i : gameData.second_player_nums) {
                    outFile << i << " ";
                }
                outFile << endl << "------------" << endl;
            }
            else if (gameData.WHOWINS == 0) {
                outFile << "DRAW in game #" << gameData.games + 1 << endl;
                outFile << "FIRST PLAYER SUM " << gameData.first_player_sum << endl;
                outFile << "SECOND PLAYER SUM " << gameData.second_player_sum << endl;
                outFile << "FIRST PLAYER NUMS IS ";
                for (int i : gameData.first_player_nums) {
                    outFile << i << " ";
                }
                outFile << endl << "SECOND PLAYER NUMS IS ";
                for (int i : gameData.second_player_nums) {
                    outFile << i << " ";
                }
                outFile << endl << "------------" << endl;
            }
            outFile.close();
        }
        else {
            cerr << "Failed to open the file." << endl;
        }
        gameData.first_player_nums.clear();
        gameData.second_player_nums.clear();
        gameData.first_player_sum = 0;
        gameData.second_player_sum = 0;
        gameData.ready = false;
        cv_first.notify_one();
    }
}

void check() {
    try {
        if (gameData.games == 10000) {
            gameData.stopthread = true;
            exit(0);
        }
    }
    catch (const std::exception& e) { 
        exit(1); 
    }
    catch (...) { 
        exit(1); 
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    thread t1(first);
    thread t2(second);
    thread t3(third);
    thread t4(fourth);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}