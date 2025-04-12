#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Init.h"
#include "GameState.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

#define ull unsigned long long

using namespace std;

class Login {
private:
	struct User {
		string hashed_username;     //Username sau khi được băm thành mã hex
		string hashed_password;     //Password sau khi được băm thành mã hex 
		string salt_username;       //Một chuỗi ngẫu nhiên của username để tăng tính bảo mật
		string salt_password;       //Một chuỗi ngẫu nhiên của password để tăng tính bảo mật
		bool isActive;              //Đánh dấu trị trí trong hash table đã được sử dụng chưa
	};

	const int SIZE_HASH_TABLE = 100;
	const int MAX_LONGLONG = 1000000007;
	const int SIZE_SALT = 16;
	const int MAX_SIZE_USERNAME = 16;
	const int MAX_SIZE_PASSWORD = 20;


	sf::RenderWindow* window;
	//Lưu các chữ: username, password, checkpassword, đăng nhập, đăng kí
	sf::Text text[6];
	/*
		..
		text[2]: nút check pass word
		text[3]: nút đăng nhập
		text[4]: nút đăng kí
		text[5]: đăng nhập(quay lại trạng trái đăng nhập)
		text[6]: đăng kí(đổi sang chế độ đăng kí)
	*/

	sf::RectangleShape rec[6];
	/*
		rec[0]: username
		rec[1]: password
		rec[2]: checkpassword
		rec[3]: đăng nhập
		rec[4]: đăng kí
		rec[5]: đổi đăng nhập
		rec[6]: đổi đăng ký

	*/

	sf::Event event;
	sf::Font font;
	GameState& gamestate;

	sf::Text userNameText;          //Biến hiện chữ trên đồ họa
	sf::Text passWordText;          //Biến hiện mật khẩu
	sf::Text checkPassWordText;     //Biến hiện mật khẩu check

	sf::Text registerStatusText;    //Biến thông báo là đăng kí như thế nào


	bool shouldRegister = false;
	bool shouldLogin = false;




	string curWindow;
	string preWindow;

	//Các biến để lưu giá trị nhập vào
	string inputUserName;
	string inputPassWorld;
	string inputCheck_PassWorld;

	//check để coi là đang ghi ở ô nào
	bool userNameActive = false;
	bool passWordActive = false;
	bool checkPassWordActive = false;
	//Có shown pass word không
	bool isPasswordShown = false;

	bool isRegistering = false;
	//Biến tham chiếu đến username để lấy username ra game.cpp
	string& refUserName;


	/*GAMESTATE gameState;*/
	Init init;
	vector<User> hashTableUser;

	void initFont();
	void initAllText();
	void initAllRec();

	string ll_to_hex(ull hash);
	string create_salt();
	string hash_username(const string& username, const string& salt);
	int hash_to_index(const string& username);
	int hash_to_step(const string& username);
	string hash_password(const string& password, const string& salt);
	void save_string(ofstream& file, const string& str);
	string load_string(ifstream& file);

	void register_account(const string& username, const string& password, const string& password_check);
	bool loginUser(const string& username, const string& password);
	bool change_password(const string& username, const string& old_password, const string& new_password);
	void save_to_file(const string& fileName);
	void load_from_file(const string& fileName);

public:

	Login(sf::RenderWindow* window, string& userName, GameState& gamestate);
	void updateEvent(sf::Event event);
	void render();
};



