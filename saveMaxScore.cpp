#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

#define ull unsigned long long

using namespace std;

class HighScoreSystem{
private:
    struct Player_highScore{
        string username;
        vector<int> highScore;
        bool isActive;
    };

    const int SIZE_HASH_TABLE = 10007;
    const int MAX_LONGLONG = 1000000007;

    vector<Player_highScore> hashTable;

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

public:
    HighScoreSystem() : hashTable(SIZE_HASH_TABLE, {"", vector<int>(9 ,0), false}){};

    void update_high_score(const string &username, int gameMode, int score){
        int index = hash_to_index(username);
        int step = hash_to_step(username);
        int i = 0;

        while(hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive == true){
            int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
            Player_highScore &player = hashTable[checkIndex];
            if(player.username == username){
                if(score > player.highScore[gameMode]){
                    player.highScore[gameMode] = score;
                    cout << "Cap nhat diem thanh cong" << endl;  
                }
                return;
            }

            ++i;
        }

        //Nếu không tìm ra tức ở bên hash table này điểm người đó chưa được cập nhật
        int newIndex = (index + i * step) % SIZE_HASH_TABLE;
        hashTable[newIndex] = {username, vector<int>(9, 0), true};
        hashTable[newIndex].highScore[gameMode] = score;
        cout << "Tao moi va cap nhat diem thanh cong" << endl;
    }

    //Lấy điểm cao nhất của người đó trong file điểm cao nhất ra
    int getHighScore(const string &username, int gameMode){
        int index = hash_to_index(username);
        int step = hash_to_step(username);

        int i = 0;
        while(hashTable[(index + i * step) % SIZE_HASH_TABLE].isActive){
            int checkIdex = (index + i * step) % SIZE_HASH_TABLE;
            Player_highScore &player = hashTable[checkIdex];

            if(player.username == username){
                return player.highScore[gameMode];
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

        for(const Player_highScore &player : hashTable){
            save_string(file, player.username);
            file.write((char*)player.highScore.data(), player.highScore.size() * sizeof(int));
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

        for(Player_highScore &player : hashTable){
            player.username = load_string(file);
            file.read((char*)player.highScore.data(), player.highScore.size() * sizeof(int));
            file.read((char*)&player.isActive, sizeof(player.isActive));
        }

        file.close();
        cout << "Tai du lieu thanh cong" << endl;
    }
};

int main() {
    HighScoreSystem system;
    system.load_from_file("highscores.dat");

    system.update_high_score("player1", 0, 500);
    system.update_high_score("player2", 1, 300);
    system.update_high_score("player3", 1, 300);
    system.update_high_score("player4", 1, 300);
    system.update_high_score("player5", 1, 300);
    system.update_high_score("player6", 1, 300);
   
    system.save_to_file("highscores.dat");
    return 0;
}