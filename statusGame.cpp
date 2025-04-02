#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

#define ull unsigned long long

using namespace std;

class GameStateSystem{
private:
    struct PlayerState{
        string username;
        int now_score;
        int size;
        int **matrixGame;
        bool isContinue;
        bool isActive;
    };

    const int SIZE_HASH_TABLE = 10007;
    const int MAX_LONGLONG = 1000000007;

    vector<PlayerState> hashTable;

    int hash_username(const string &username){
        ull hash = 0;
        for(char c : username){
            hash = (hash * 31 + c) % MAX_LONGLONG;
        }

        return hash;
    }

    int hash_to_index(const string &username){
        return hash_username(username) % SIZE_HASH_TABLE;
    }

    int hash_to_step(const string &username){
        int step = hash_username(username) % (SIZE_HASH_TABLE - 1);
        if(step % 2 == 0){
            step += 1;
        }

        return step;
    }

    void save_string(ofstream &file, const string &str){
        size_t length = str.size();
        file.write((char*)&length, sizeof(length));     //Ghi độ dài trước
        file.write(str.data(), length);
    }

    string load_string(ifstream &file){
        size_t length;
        file.read((char*)&length, sizeof(length));

        string str(length, ' ');
        file.read(&str[0], length);

        return str;
    }

    void save_matrix(ofstream &file, int **matrixGame, int size){
        file.write((char*)&size, sizeof(size));

        for(int i = 0; i < size; i++){
            file.write((char*)matrixGame[i], size * sizeof(int));
        }
    }

    void load_matrix(ifstream &file, int **&matrixGame, int size){
        file.read((char*)&size, sizeof(size));
        matrixGame = new int*[size];
        for(int i = 0; i < size; i++){
            matrixGame[i] = new int[size];
            file.read((char*)matrixGame[i], size * sizeof(int));
        }
    }
public:
    GameStateSystem() : hashTable(SIZE_HASH_TABLE, {"", 0, 0, NULL, false, false}){};

    void updateGameState(const string &username, int score, int **matrixGame, int size, bool isContinue){
        int index = hash_to_index(username);
        int step = hash_to_step(username);
        int i = 0;

        while(hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive == true){
            int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
            PlayerState &player = hashTable[checkIndex];
            if(player.username == username){
                player.now_score = score;
                //Xóa dữ liệu ma trận cũ
                for(int j = 0; j < player.size; j++){
                    delete []player.matrixGame[j];
                }

                delete []player.matrixGame;
                //Cập nhật size mới
                player.size = size;
                //Cập nhật dữ liệu ma trận mới
                player.matrixGame = new int*[size];
                for(int j = 0; j < size; j++){
                    player.matrixGame[j] = new int[size];
                    for(int k = 0; k < size; k++){
                        player.matrixGame[j][k] = matrixGame[j][k];
                    }
                }
                //Cập nhật trạng thái game còn chơi không
                player.isContinue = isContinue;

                cout << "cap nhat thanh cong" << endl;
                return;
            }
            ++i;
        }
    }

    void save_to_file(const string &fileName){
        ofstream file(fileName, ios::binary);
        if(!file.is_open()){
            cout << "Khong the mo file ghi" << endl;
            return;
        }

        for(const PlayerState &player : hashTable){
            save_string(file, player.username);
            file.write((char*)&player.now_score, sizeof(player.now_score));
            save_matrix(file, player.matrixGame, player.size);
            file.write((char*)&player.isContinue, sizeof(player.isContinue));
            file.write((char*)&player.isActive, sizeof(player.isActive));
        }

        file.close();
        cout << "Luu file thanh cong" << endl;
    }

    void load_from_file(const string &fileName){
        ifstream file(fileName, ios::binary);
        if(!file.is_open()){
            cout << "Khong the tai file ghi" << endl;
            return;
        }

        for(PlayerState &player : hashTable){
            player.username = load_string(file);
            file.read((char*)&player.now_score, sizeof(player.now_score));
            load_matrix(file, player.matrixGame, player.size);
            file.read((char*)&player.isContinue, sizeof(player.isContinue));
            file.read((char*)&player.isActive, sizeof(player.isActive));
        }

        file.close();
        cout << "Tai du lieu thanh cong" << endl;
    }



};