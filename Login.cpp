#include "Login.h"

void Login::initFont() {
	font.loadFromFile("Dosis-VariableFont_wght.ttf");
}

void Login::initAllText() {
	init.initText(text[0], font, 24, rec[0].getPosition().x, rec[0].getPosition().y - 30.f, sf::Color::Black, "User Name");
	init.initText(text[1], font, 24, rec[1].getPosition().x, rec[1].getPosition().y - 30.f, sf::Color::Black, "Password");
	init.initText(text[2], font, 24, rec[2].getPosition().x, rec[2].getPosition().y - 30.f, sf::Color::Black, "Check Password");

	// Gộp nút "Sign in" và "Register" thành text[3]
	init.initText(text[3], font, 24, 0, 0, sf::Color::Black, isRegistering ? "Register" : "Sign in");
	sf::FloatRect bounds3 = text[3].getLocalBounds();
	text[3].setOrigin(bounds3.left + bounds3.width / 2.f, bounds3.top + bounds3.height / 2.f);
	text[3].setPosition(
		rec[3].getPosition().x + rec[3].getSize().x / 2.f,
		rec[3].getPosition().y + rec[3].getSize().y / 2.f
	);


	// Tạo text cho nút chuyển chế độ
	init.initText(text[4], font, 20, 0, 0, sf::Color::Black, isRegistering ? "To Login" : "To Register");

	sf::FloatRect bounds5 = text[4].getLocalBounds();
	text[4].setOrigin(bounds5.left, bounds5.top + bounds5.height / 2.f);

	float space = 20.f;
	text[4].setPosition(
		rec[3].getPosition().x + rec[3].getGlobalBounds().width + space,
		rec[3].getPosition().y + rec[3].getGlobalBounds().height / 2.f
	);

	// rec[5] dùng làm vùng click cho text[5]
	sf::FloatRect text5Bounds = text[4].getGlobalBounds();
	rec[4].setPosition(text5Bounds.left, text5Bounds.top);
	rec[4].setSize(sf::Vector2f(text5Bounds.width, text5Bounds.height));


	// Tạo nút hiện/ẩn mật khẩu bên cạnh rec[1]
	init.initText(text[5], font, 18, 0, 0, sf::Color::Black, "show");

	// Căn giữa chiều cao, đặt bên phải rec[1] một chút
	sf::FloatRect showBounds = text[5].getLocalBounds();
	text[5].setOrigin(showBounds.left, showBounds.top + showBounds.height / 2.f);

	float paddingRight = 10.f; // khoảng cách từ rec[1] đến nút "Hiện"
	text[5].setPosition(
		rec[1].getPosition().x + rec[1].getSize().x + paddingRight,
		rec[1].getPosition().y + rec[1].getSize().y / 2.f
	);

	// Nếu muốn click được thì tạo một hình chữ nhật ẩn tương ứng để check va chạm
	sf::FloatRect toggleBounds = text[5].getGlobalBounds();
	rec[5].setPosition(toggleBounds.left, toggleBounds.top);
	rec[5].setSize(sf::Vector2f(toggleBounds.width, toggleBounds.height));




	init.initText(userNameText, font, 24, rec[0].getPosition().x + 10, rec[0].getPosition().y + 10, sf::Color::Black, "");
	init.setInputTextPosition(userNameText, rec[0], 10.f, 10.f);
	init.initText(passWordText, font, 24, rec[1].getPosition().x + 10, rec[1].getPosition().y + 10, sf::Color::Black, "");
	init.setInputTextPosition(passWordText, rec[1], 10.f, 10.f);

	init.initText(checkPassWordText, font, 24, rec[2].getPosition().x + 10, rec[2].getPosition().y + 10, sf::Color::Black, "");
	init.setInputTextPosition(checkPassWordText, rec[2], 10.f, 10.f);

	init.initText(registerStatusText, font, 20, rec[2].getPosition().x, rec[2].getPosition().y + rec[2].getSize().y + 2.f, sf::Color::Black, "");
}

void Login::initAllRec()
{
	init.initRectangle(rec[0], (window->getSize().x - static_cast<float>(300)) / 2, 200.0, sf::Color(230, 124, 93), 300, 50);
	init.initRectangle(rec[1], (window->getSize().x - static_cast<float>(300)) / 2, 280.0, sf::Color(230, 124, 93), 300, 50);
	init.initRectangle(rec[2], (window->getSize().x - static_cast<float>(300)) / 2, 360.0, sf::Color(230, 124, 93), 300, 50);
	init.initRectangle(rec[3], (window->getSize().x - static_cast<float>(200)) / 2, 440.0, sf::Color(239, 197, 85), 200, 50);
	

	init.initRectangle(rec[4], 0.f, 0.f, sf::Color::Transparent, 10, 10);
	init.initRectangle(rec[5], 0.f, 0.f, sf::Color::Transparent, 10, 10);

}

string Login::ll_to_hex(ull hash) {
	string hex_str = "";
	const string hex_strs = "123456789abcdef";
	while (hash > 0) {
		hex_str = hex_strs[hash % 16] + hex_str;
		hash /= 16;
	}

	while (hex_str.size() < 16) {
		hex_str = "0" + hex_str;
	}

	return hex_str;
}

//Hàm tạo salt ngẫu nhiên để tăng tính bảo mật
string Login::create_salt() {
	string charAll = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
	string salt;
	for (int i = 0; i < SIZE_SALT; i++) {
		salt += charAll[rand() % charAll.size()];
	}

	return salt;
}

//Hàm băm username ra một chuỗi số (số như thế nào là phụ thuộc vào cách băm)
//Ví dụ băm minhbiminh ra một chuỗi số "423413437" rồi chuyển sang mã HEX
string Login::hash_username(const string& username, const string& salt) {
	string data = username + salt;
	ull hash = 0;           //Tạo một biến để lưu dữ liệu sau khi hash
	for (char c : data) {     //Lấy từng kí tự ra và hash
		hash = (hash * 37 + c) % MAX_LONGLONG;
	}

	return ll_to_hex(hash);     //Chuyển đổi số sang dạng mã hex
}

//Hàm băm chính username (băm ra một số trong khoảng SIZE_HASH_TABLE)
int Login::hash_to_index(const string& username) {
	ull hash = 0;
	for (char c : username) {     //Lấy từng kí tự ra và hash
		hash = (hash * 37 + c) % MAX_LONGLONG;
	}
	return hash % SIZE_HASH_TABLE;          //Lấy index để truy cập
}

//Hàm băm phụ nhằm tìm kiếm step đến ô khác nếu index hiện tại đã có
//Hàm băm phụ này lun trả về số lẻ vì để tránh LẶP VÔ TẬN
int Login::hash_to_step(const string& username) {
	ull hash = 0;
	for (char c : username) {     //Lấy từng kí tự ra và hash
		hash = (hash * 37 + c) % MAX_LONGLONG;
	}

	int step = hash % (SIZE_HASH_TABLE - 1);
	if (step % 2 == 0) {
		step += 1;
	}

	return step;
}

//Hàm băm mật khẩu
string Login::hash_password(const string& password, const string& salt) {
	string data = password + salt;
	ull hash = 0;
	for (char s : data) {
		hash = (hash * 37 + s) % SIZE_HASH_TABLE;
	}

	return ll_to_hex(hash);
}

//LƯU THÔNG TIN VAO FILE BINARY

//Hàm lưu chuỗi string vào
void Login::save_string(ofstream& file, const string& str) {
	size_t length = str.size();
	file.write((char*)&length, sizeof(length));     //Ghi độ dài trước
	cout << "[DEBUG] Reading string length: " << length << endl;
	file.write(str.data(), length);
}


//LẤY THÔNG TIN TỪ FILE BINARY RA

//Hàm load chuỗi string ra
string Login::load_string(ifstream& file) {
	size_t length;
	file.read((char*)&length, sizeof(length));

	// Kiểm tra length không vượt quá ngưỡng cho phép
	if (length > 10000) { // Giả sử không có chuỗi nào dài hơn 10,000 ký tự
		throw runtime_error("[ERROR] Chuỗi trong file quá dài hoặc file bị hỏng.");
	}

	string str(length, ' ');
	file.read(&str[0], length);

	return str;
}

void Login::save_to_file(const string& fileName) {
	ofstream file(fileName, ios::binary);
	if (!file.is_open()) {
		cout << "Khong the mo file ghi" << endl;
		return;
	}

	for (const User& user : hashTableUser) {
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
void Login::load_from_file(const string& fileName) {
	ifstream file(fileName, ios::binary);
	if (!file.is_open()) {
		ofstream file_out(fileName, ios::binary);
		for (int i = 0; i < SIZE_HASH_TABLE; i++) {
			User emptyUser = {};
			save_string(file_out, "");
			save_string(file_out, "");
			save_string(file_out, "");
			save_string(file_out, "");
			file_out.write((char*)&emptyUser.isActive, sizeof(bool));
		}
		file_out.close();
		return;
	}

	int index = 0;
	while (index < SIZE_HASH_TABLE) {
		User user;
		
		user.hashed_username = load_string(file);
		user.hashed_password = load_string(file);
		user.salt_username = load_string(file);
		user.salt_password = load_string(file);
		file.read((char*)&user.isActive, sizeof(user.isActive));
		hashTableUser[index++] = user;
		/*cout << "[DEBUG] Read user " << index << ": " << user.hashed_username << endl;*/

	}

	file.close();
	cout << "Tai du lieu thanh cong" << endl;
}

void Login::register_account(const string& username, const string& password, const string& password_check) {
	cout << "[DEBUG] Username received: " << username << endl;
	load_from_file("users.dat");

	if (username.empty() || password.empty() || password_check.empty()) {
		registerStatusText.setString("Ten dang nhap va mat khau khong duoc de trong");
		return;
	}

	if (password != password_check) {
		registerStatusText.setString("Confirm password khong khop");
		// Reset lại chỉ trường confirm password
		inputCheck_PassWorld.clear();
		checkPassWordText.setString("");
		return;
	}

	
	int index = hash_to_index(username);
	int step = hash_to_step(username);

	int i = 0;      //Có chỉ số i để bội lần step dịch ô không trùng
	bool accountExists = false;

	while (i < SIZE_HASH_TABLE && hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		User& user = hashTableUser[checkIndex];

		string temp_userName = hash_username(username, user.salt_username);
		if (user.hashed_username == temp_userName) {
			accountExists = true;
			break;
		}

		++i;
		std::cout << "i = " << i << std::endl;
	}

	if (i == SIZE_HASH_TABLE) {
		registerStatusText.setString("Sever da day, khong the dang ki them");
		return;
	}

	if (accountExists) {
		registerStatusText.setString("Tai khoan da ton tai");
		// Reset lại tất cả các trường nhập liệu để người dùng nhập lại
		inputUserName.clear();
		inputPassWorld.clear();
		inputCheck_PassWorld.clear();
		userNameText.setString("");
		passWordText.setString("");
		checkPassWordText.setString("");
		return;
	}

	//Khi xuống được tới đây tức là ĐÃ tìm được Ô TRỐNG và KHÔNG TỒN TẠI tài khoản trùng
	int indexOfEmpty = (index + i * step) % SIZE_HASH_TABLE;
	string username_salt = create_salt();
	string password_salt = create_salt();
	string hashed_username = hash_username(username, username_salt);
	string hashed_password = hash_password(password, password_salt);

	hashTableUser[indexOfEmpty] = { hashed_username, hashed_password, username_salt, password_salt, true };
	registerStatusText.setString("Tao tai khoang thanh cong");
	cout << "Dang ky thanh cong" << endl;
	save_to_file("users.dat");


	// Reset các trường nhập liệu và chuyển về màn hình đăng nhập
	inputUserName.clear();
	inputPassWorld.clear();
	inputCheck_PassWorld.clear();
	userNameText.setString("");
	passWordText.setString("");
	checkPassWordText.setString("");
	isRegistering = false;


}

//Đăng nhập tài khoản
bool Login::loginUser(const string& username, const string& password) {
	load_from_file("users.dat");
	

	if (username.empty() || password.empty()) {
		registerStatusText.setString("Username va pass word khong duoc de trong");
		return false;
	}

	int index = hash_to_index(username);
	int step = hash_to_step(username);
	int i = 0;

	while (i < SIZE_HASH_TABLE && hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		User& user = hashTableUser[checkIndex];

		if (user.hashed_username == hash_username(username, hashTableUser[checkIndex].salt_username)) {
			if (user.hashed_password == hash_password(password, hashTableUser[checkIndex].salt_password)) {

				cout << "Dang nhap thanh cong" << endl;
				return true;
			}
			else {
				registerStatusText.setString("Sai mat khau, vui long nhap lai");
				inputPassWorld.clear();
				passWordText.setString("");
				return false;
			}
		}

		++i;
	}

	registerStatusText.setString("Chua co tai khoan");
	// Có thể reset lại username nếu muốn
	inputUserName.clear();
	userNameText.setString("");
	inputPassWorld.clear();
	passWordText.setString("");

	return false;
}

//Thay đổi mật khẩu
bool Login::change_password(const string& username, const string& old_password, const string& new_password) {
	int index = hash_to_index(username);
	int step = hash_to_step(username);

	int i = 0;

	while (i < SIZE_HASH_TABLE && hashTableUser[(index + i * step) % SIZE_HASH_TABLE].isActive == true) {
		int checkIndex = (index + i * step) % SIZE_HASH_TABLE;
		User& user = hashTableUser[checkIndex];

		if (user.hashed_username == hash_username(username, hashTableUser[checkIndex].salt_username)) {
			if (user.hashed_password == hash_password(old_password, hashTableUser[checkIndex].salt_password)) {
				user.salt_password = create_salt();
				user.hashed_password = hash_password(new_password, user.salt_password);
				save_to_file("users.dat");
				return true;
			}
			else {
				return false;
			}
		}
		++i;
	}
	return false;
}




Login::Login(sf::RenderWindow* window, string& username, GameState& gamestate) :
	window(window),
	hashTableUser(SIZE_HASH_TABLE, { "", "", "", "", false }),
	refUserName(username), gamestate(gamestate) {

	initFont();
	initAllRec();
	initAllText();
}



void Login::updateEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased) {
		sf::Vector2f mouPos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		for (int i = 0; i < 6; i++) {
			// BỎ QUA các rec không phù hợp với chế độ hiện tại
			if (i == 2 && !isRegistering) continue;

			sf::FloatRect bounds = rec[i].getGlobalBounds();
			if (bounds.contains(mouPos)) {
				switch (i) {
				case 0:
					userNameActive = true;
					passWordActive = false;
					checkPassWordActive = false;
					break;
				case 1:
					userNameActive = false;
					passWordActive = true;
					checkPassWordActive = false;
					break;
				case 2:
					if (isRegistering) {
						userNameActive = false;
						passWordActive = false;
						checkPassWordActive = true;
					}
					break;
				case 3:
					if (isRegistering) {
						register_account(inputUserName, inputPassWorld, inputCheck_PassWorld);
					}
					else {
						if (loginUser(inputUserName, inputPassWorld)) {
							gamestate = GameState::MAIN_MENU;
							refUserName = inputUserName;
						}
					}
					break;
				case 4:
					// Toggle chế độ
					isRegistering = !isRegistering;
					registerStatusText.setString("");
					inputUserName.clear();
					inputPassWorld.clear();
					inputCheck_PassWorld.clear();
					userNameText.setString("");
					passWordText.setString("");
					checkPassWordText.setString("");

					// Cập nhật nhãn nút đổi chế độ
					text[4].setString(isRegistering ? "To Login" : "To Register");
					text[3].setString(isRegistering ? "Register" : "Sign in");

					// Căn giữa lại text[3] so với rec[3]
					{
						sf::FloatRect bounds3 = text[3].getLocalBounds();
						text[3].setOrigin(bounds3.left + bounds3.width / 2.f, bounds3.top + bounds3.height / 2.f);
						text[3].setPosition(
							rec[3].getPosition().x + rec[3].getSize().x / 2.f,
							rec[3].getPosition().y + rec[3].getSize().y / 2.f
						);
					}
					

					// Cập nhật vị trí và kích thước rec[5]
					{
						sf::FloatRect newBounds = text[4].getGlobalBounds();
						rec[4].setPosition(newBounds.left, newBounds.top);
						rec[4].setSize(sf::Vector2f(newBounds.width, newBounds.height));
					}
					break;
				case 5:
					isPasswordShown = !isPasswordShown;

					// Cập nhật lại mật khẩu hiển thị
					if (isPasswordShown) {
						passWordText.setString(inputPassWorld);
						text[5].setString("Hide");
						
					}
					else {
						passWordText.setString(string(inputPassWorld.size(), '*'));
						text[5].setString("Show");	
					}
					//set lại vùng bao quanh chữ
					sf::FloatRect toggleBounds = text[5].getGlobalBounds();
					rec[5].setPosition(toggleBounds.left, toggleBounds.top);
					rec[5].setSize(sf::Vector2f(toggleBounds.width, toggleBounds.height));

				}
			}
		}
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
		if (isRegistering) {
			register_account(inputUserName, inputPassWorld, inputCheck_PassWorld);
		}
		else {
			if (loginUser(inputUserName, inputPassWorld)) {
				gamestate = GameState::MAIN_MENU;
				refUserName = inputUserName;
			}
		}
	}


	if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode == 8) {
			if (userNameActive == true && !inputUserName.empty())
				inputUserName.pop_back();
			if (passWordActive == true && !inputPassWorld.empty())
				inputPassWorld.pop_back();
			if (checkPassWordActive == true && !inputCheck_PassWorld.empty())
				inputCheck_PassWorld.pop_back();
		}
		else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
			if (userNameActive == true && inputUserName.size() < MAX_SIZE_USERNAME)
				inputUserName += static_cast<char>(event.text.unicode);
			if (passWordActive == true && inputPassWorld.size() < MAX_SIZE_PASSWORD)
				inputPassWorld += static_cast<char>(event.text.unicode);
			if (checkPassWordActive == true && inputCheck_PassWorld.size() < MAX_SIZE_PASSWORD)
				inputCheck_PassWorld += static_cast<char>(event.text.unicode);
		}

		userNameText.setString(inputUserName);
		passWordText.setString(isPasswordShown ? inputPassWorld : string(inputPassWorld.size(), '*'));
		checkPassWordText.setString(isPasswordShown ? inputCheck_PassWorld : string(inputCheck_PassWorld.size(), '*'));

		

	}
}


void Login::render()
{
	for (int i = 0; i < 6; i++) {
		if (i == 2 && isRegistering == false)
			continue;
		this->window->draw(rec[i]);
	}


	for (int i = 0; i < 6; i++) {
		if (i == 2 && isRegistering == false) {
			continue; // Ẩn ô "Check Password" khi không đăng ký
		}
		
		this->window->draw(text[i]);
	}

	this->window->draw(userNameText);
	this->window->draw(passWordText);
	if (isRegistering) {
		this->window->draw(checkPassWordText);
		
	}
	
		this->window->draw(registerStatusText);
	
}
