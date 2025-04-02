#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>

#define ull unsigned long long

using namespace std;

class LoginSystem{
private:
    struct User{
        string hashed_username;     //Username sau khi được băm thành mã hex
        string hashed_password;     //Password sau khi được băm thành mã hex 
        string salt_username;       //Một chuỗi ngẫu nhiên của username để tăng tính bảo mật
        string salt_password;       //Một chuỗi ngẫu nhiên của password để tăng tính bảo mật
        bool isActive;              //Đánh dấu trị trí trong hash table đã được sử dụng chưa
    };

    const int SIZE_HASH_TABLE = 10007;
    const int MAX_LONGLONG = 1000000007;
    const int SIZE_SALT = 16;

    vector<User> hashTableUser;     //Bảng băm dạng mảng

    //Chuyển đổi số nguyên thành chuỗi hex
    string ll_to_hex(ull hash){
        string hex_str = "";
        const string hex_strs = "123456789abcdef";
        while(hash > 0){
            hex_str = hex_strs[hash % 16] + hex_str;
            hash /= 16;
        }

        while(hex_str.size() < 16){
            hex_str = "0" + hex_str;
        }

        return hex_str;
    }

    //Chuyển đổi hex thành số nguyên
    ull hex_to_ll(const string &hex_str){
        ull value = 0;
        for(char s : hex_str){
            if(s >= '0' && s <= '9'){
                value = value * 16 + (s - '0');
            } else if(s >= 'a' && s <= 'f'){
                value = value * 16 + (s - 'a' + 10);
            } else if(s >= 'A' && s <= 'F'){
                value = value * 16 + (s - 'A' + 10);
            }
        }

        return value;
    }

    //Hàm tạo salt ngẫu nhiên để tăng tính bảo mật
    string create_salt(){
        srand(time(0));
        string charAll = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
        string salt;
        for(int i = 0; i < SIZE_SALT; i++){
            salt += charAll[rand() % charAll.size()];
        }

        return salt;
    }

    //Hàm băm username ra một chuỗi số (số như thế nào là phụ thuộc vào cách băm)
    //Ví dụ băm minhbiminh ra một chuỗi số "423413437" rồi chuyển sang mã HEX
    string hash_username(const string &username, const string &salt){
        string data = username + salt;
        ull hash = 0;           //Tạo một biến để lưu dữ liệu sau khi hash
        for(char c : data){     //Lấy từng kí tự ra và hash
            hash = (hash * 37 + c) % MAX_LONGLONG; 
        }

        return ll_to_hex(hash);     //Chuyển đổi số sang dạng mã hex
    }

    //Hàm băm chính username (băm ra một số trong khoảng SIZE_HASH_TABLE)
    int hash_to_index(const string &username){
        ull hash = 0;                
        for(char c : username){     //Lấy từng kí tự ra và hash
            hash = (hash * 37 + c) % MAX_LONGLONG; 
        }          
        return hash % SIZE_HASH_TABLE;          //Lấy index để truy cập
    }

    //Hàm băm phụ nhằm tìm kiếm step đến ô khác nếu index hiện tại đã có
    //Hàm băm phụ này lun trả về số lẻ vì để tránh LẶP VÔ TẬN
    int hash_to_step(const string &username){
        ull hash = 0;  
        for(char c : username){     //Lấy từng kí tự ra và hash
            hash = (hash * 37 + c) % MAX_LONGLONG; 
        } 

        int step = hash % (SIZE_HASH_TABLE - 1);
        if(step % 2 == 0){
            step += 1;
        }

        return step;
    }

    //Hàm băm mật khẩu
    string hash_password(const string &password, const string &salt){
        string data = password + salt;
        ull hash = 0;
        for(char s : data){
            hash = (hash * 37 + s) % SIZE_HASH_TABLE;
        }

        return ll_to_hex(hash);
    }

    //LƯU THÔNG TIN VAO FILE BINARY

    //Hàm lưu chuỗi string vào
    void save_string(ofstream &file, const string &str){
        size_t length = str.size();
        file.write((char*)&length, sizeof(length));     //Ghi độ dài trước
        file.write(str.data(), length);
    }

    
    //LẤY THÔNG TIN TỪ FILE BINARY RA

    //Hàm load chuỗi string ra
    string load_string(ifstream &file){
        size_t length;
        file.read((char*)&length, sizeof(length));

        string str(length, ' ');
        file.read(&str[0], length);

        return str;
    }
public:
    LoginSystem() : hashTableUser(SIZE_HASH_TABLE, {"", "", "", "", false}){};

    //Đăng kí tài khoản mới
    void register_account(const string &username, const string &password){
        string username_salt = create_salt();
        string hashed_username = hash_username(username, username_salt);
        int index = hash_to_index(username);
        int step = hash_to_step(username);

        int i = 0;      //Có chỉ số i để bội lần step dịch ô không trùng

        while(hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true){
            if(hashTableUser[(index + i * step) % SIZE_HASH_TABLE].hashed_username == hashed_username){
                cout << "Tai khoan da ton tai" << endl;
                return;                
            }

            ++i;
        }

        //Khi xuống được tới đây tức là ĐÃ tìm được Ô TRỐNG và KHÔNG TỒN TẠI tài khoản trùng
        int indexOfEmpty = (index + i * step) % SIZE_HASH_TABLE;
        string password_salt = create_salt();
        string hashed_password = hash_password(password, password_salt); 
        hashTableUser[indexOfEmpty] = {hashed_username, hashed_password, username_salt, password_salt, true};
        cout << "Dang ky thanh cong" << endl;
    }

    //Đăng nhập tài khoản
    bool loginUser(const string &username, const string &password){
        int index = hash_to_index(username);
        int step = hash_to_step(username);
        int i = 0;    
        while(hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true){
            int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
            User &user = hashTableUser[checkIndex];

            if(user.hashed_username == hash_username(username, hashTableUser[checkIndex].salt_username)){
                if(user.hashed_password == hash_password(password, hashTableUser[checkIndex].salt_password)){
                    cout << "Dang nhap thanh cong" << endl;
                    return true;
                }
            }
            
            ++i;
        }

        cout << "Tai khoan khong ton tai" << endl;
        return false;
    }

    //Thay đổi mật khẩu
    bool change_password(const string &username, const string &old_password, const string &new_password){
        int index = hash_to_index(username);
        int step = hash_to_step(username);

        int i = 0;

        while(hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true){
            int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
            User &user = hashTableUser[checkIndex];

            if(user.hashed_username == hash_username(username, hashTableUser[checkIndex].salt_username)){
                if(user.hashed_password == hash_password(old_password, hashTableUser[checkIndex].salt_password)){
                    user.salt_password = create_salt();
                    user.hashed_password = hash_password(new_password, user.salt_password);
                    
                    cout << "Doi mat khau thanh cong" << endl;
                    return true;
                } else{
                    cout << "Sai mat khau cu" << endl;
                    return false;
                }
            }
            ++i;
        }

        cout << "Tai khoan khong ton tai" << endl;
        return false;


    }

    //Hàm lưu hash table vào binary file
    void save_to_file(const string &fileName){
        ofstream file(fileName, ios::binary);
        if(!file.is_open()){
            cout << "Khong the mo file ghi" << endl;
            return;
        }

        for(const User& user : hashTableUser){
            save_string(file, user.hashed_username);
            save_string(file, user.hashed_password);
            save_string(file, user.salt_username);
            save_string(file, user.salt_password);

            file.write((char*)&user.isActive, sizeof(user.isActive));
        }

        file.close();
        cout << "Luu du lieu thanh cong" << endl;
    }

    //Hàm load dữ liệu từ binary file vào hashtable
    void load_to_file(const string &fileName){
        ifstream file(fileName, ios::binary);
        if(!file.is_open()){
            cout << "Khong the mo file doc" << endl;
            return;
        }
        
        for(User &user : hashTableUser){
            user.hashed_username = load_string(file);
            user.hashed_password = load_string(file);
            user.salt_username = load_string(file);
            user.salt_password = load_string(file);

            file.read((char*)&user.isActive, sizeof(user.isActive));
        }

        file.close();
        cout << "Tai du lieu thanh cong" << endl;
    }


    
    
};



