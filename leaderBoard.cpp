#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class LeaderBoard{
private:
    struct PlayerNode{
        string name;
        int score;
        PlayerNode *left;
        PlayerNode *right;

        PlayerNode(string n, int s) : name(n), score(s), left(NULL), right(NULL){};

    };

    PlayerNode *root;
    const int MAX_PLAYER = 10;


    //Đếm số lượng người
    int countPlayer(PlayerNode *root){
        if(root == NULL){
            return 0;
        }

        return 1 + countPlayer(root->left) + countPlayer(root->right);
    }

    //Tìm + xóa người chơi có điểm thấp nhất
    PlayerNode *findMin(PlayerNode *root){
        while(root->left != NULL){
            root = root->left;
        }
        return root;
    }

    //Thêm người chơi và kiểm tra giới hạn
    PlayerNode *insertPlayer(PlayerNode *root, string name, int score){
        if(root == NULL){
            return new PlayerNode(name, score);
        }

        if(score < root->score){
            root->left = insertPlayer(root->left, name, score);
        } else if(score > root ->score){
            root->right = insertPlayer(root->right, name, score);
        }

        int countPlayers = countPlayer(root);

        if(countPlayers > MAX_PLAYER){
            root = deletePlayer(root, findMin(root)->score);
        }

        return root;
    }

    //Xoas theo điểm
    PlayerNode *deletePlayer(PlayerNode *root, int score){
        if(root == NULL){
            return NULL;
        }

        if(score < root->score){
            root->left = deletePlayer(root->left, score);
        } else if(score > root->score){
            root->right = deletePlayer(root->right, score);
        } else{
            //TH1: Don't child
            if(root->left == NULL && root->right == NULL){
                delete root;
                return NULL;
            }

            //TH2: Have one child
            else if(root->left == NULL){
                PlayerNode *temp = root->right;
                delete root;
                return temp;
            } else if(root->right == NULL){
                PlayerNode *temp = root->left;
                delete root;
                return temp;
            }
            //TH3: Have 2 leaves
            else{
                PlayerNode *temp = findMin(root->right);
                root->name = temp->name;
                root->score = temp->score;
                root->right = deletePlayer(root->left, temp->score); //Xóa node lớn nhất bên trái
            }
        }

        return root;
    } 

    //Hàm tìm kiếm người chơi theo tên (nhằm mục đích nếu tên có trong danh sách thì sẽ xóa tên rồi mới chèn tên mới vào)
    PlayerNode *search(PlayerNode *root, string name){
        if(root == NULL || root->name == name){
            return root;
        }
    
        PlayerNode *searchLeft = search(root->left, name);
        if(searchLeft != NULL){
            return searchLeft;
        }
        return search(root->right, name);
    }

    //Hàm lưu BXH vào file
    void saveToFile(ofstream &file, PlayerNode *root){
        if(root == NULL){
            return;
        }

        //Ghi dộ dài của tên vao
        size_t sizeName = root->name.size();
        file.write((char*)&sizeName, sizeof(sizeName));
        //Ghi tên vào
        file.write(root->name.c_str(), sizeName);   //Số byte ghi được bằng chính độ dài chuỗi
       
        //Ghi score vào 
        file.write((char*)&root->score, sizeof(root->score));
        
    
        saveToFile(file, root->left);
        saveToFile(file, root->right);
    }

    //Hàm load từ file ra ngoài
    PlayerNode *loadFromFile(ifstream &file){
        if(file.eof()){
            return NULL;
        }

        int sizeName;
        file.read((char*)&sizeName, sizeof(sizeName));
    
        string name(sizeName, ' '); //Khởi tạo một biến name với sizename khoảng cách
        file.read(&name[0], sizeName); //lấy địa chỉ đầu tiên của kí tự name để đưa vô
    
        int score;
        file.read((char*)&score, sizeof(score));
    
        PlayerNode *node = new PlayerNode(name, score);
        node->left = loadFromFile(file);
        node->right = loadFromFile(file);
        return node;
    }

    //Hàm in BXH
    void printBXH(PlayerNode *root){
        if(root == NULL){
            return;
        }
    
        printBXH(root->right);
        cout << root->name << " " << root->score << endl;
        printBXH(root->left);
    }

    
public:  
    LeaderBoard() : root(NULL){};
    
    void updateScoreOrAdd(string name, int newScore){
        PlayerNode *player = search(root, name);
        if(player != NULL ){
            if(newScore > player->score){
                root = deletePlayer(root, player->score);
                root = insertPlayer(root, name, newScore);
            }
        } else {
            root = insertPlayer(root, name, newScore);
        }
    }

    void printBXH(){
        printBXH(root);
    }

    // Hàm lưu BXH vào file
    void saveToFile(const string& filename){
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            cout << "Failed to open file for saving!" << endl;
            return;
        }
        saveToFile(file, root);
        file.close();
    }

    // Hàm load BXH từ file
    void loadFromFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cout << "Failed to open file for loading!" << endl;
            return;
        }
        root = loadFromFile(file);
        file.close();
    }
};





