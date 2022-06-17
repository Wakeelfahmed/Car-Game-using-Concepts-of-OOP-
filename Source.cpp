#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<string.h>
#include<string>
#include<windows.h>
using namespace std;
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define Ultra_Fast_Speed 0
#define Fast_Speed 10000
#define Normal_Speed 500000
#define Slow_Speed 90000000
HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
char Input_char;
class SUPERADMIN {
private:
	int Password; //To Allow ADMIN TO ACCESS Special Features.
	COORD Coins;
	COORD Score;
	COORD High_Score;
	COORD Lives;
public:
	SUPERADMIN() {
		Password = 1234;
		Coins = { 100,6 };
		Score = { 87,10 };
		High_Score = { 80, 7 };
		Lives = { 103 , 4 };
	}
	COORD Coins_Settings() const { return Coins; }
	COORD High_Score_Settings() const { return High_Score; }
	COORD Lives_Setting()const { return Lives; };

};
class Car
{
protected:
	string car;
	COORD Position_Cordinates;		//Cordinates cordinates;
	bool Collsion;
	int Car_Color;
	int Car_Width;
public:
	Car() {
		Position_Cordinates.X = 0;		Position_Cordinates.Y = 0;
		Car_Width = 4;		Collsion = 0;		Car_Color = 0;
	}
	void set_Position_COORDS(int x, int y) { Position_Cordinates.X = x;		Position_Cordinates.Y = y; }
	bool get_Collision_Status() const { return Collsion; }
	COORD get_Player_Position() const { return Position_Cordinates; }
	int getPosition_X() const { return Position_Cordinates.X; }
	int getPosition_Y() const { return Position_Cordinates.Y; }
	void setPosition_Y(int Y) { Position_Cordinates.Y = Y; }
	void Update_Position_X(int x) { Position_Cordinates.X = x; }
	void Update_Position_Y(int y) { Position_Cordinates.Y = y; }
	virtual void Draw_Car(int Speed) = 0;
	void EraseCar(int Speed)
	{
		COORD X_and_Y;
		SetConsoleCursorPosition(Console, Position_Cordinates);
		X_and_Y.X = Position_Cordinates.X;
		X_and_Y.Y = Position_Cordinates.Y;
		SetConsoleTextAttribute(Console, Car_Color);
		for (int i = 0; i < 25; i++)
		{
			if (i % 5 == 0)
			{
				X_and_Y.Y++;
				SetConsoleCursorPosition(Console, X_and_Y);
			}
			for (int i = 0; i < Speed; i++) {}
			cout << " ";
		}
	}
	int get_Car_width() { return Car_Width; }
};
class Driver
{
protected:
	char Driver_Name[50] = "";
	int high_score;
	char Items_Owned_Names[51][50];
	bool items_owned[10];
	char Cars_Owned_shapes[10][50];
	bool Cars_Owned[10];
	int Car_Width[10];
	int Coins;
	static int No_of_Player_Profiles1;
	bool isActive;
public:
	Driver() : Coins(4000), high_score(0), items_owned{ false }, Cars_Owned{ false }, isActive(false){}
	bool get_IsActive_Status()const { return isActive; }
	int static No_of_Player_Profiles() {
		return No_of_Player_Profiles1;
	}
	void set_Player_Details() { isActive = true; cout << "Enter Name: "; cin.getline(Driver_Name, 50, '\n'); }
	char* get_name() { return Driver_Name; }
	void buy_item_in_char_array(char Name[], int Item_Index) {
		strcpy_s((Items_Owned_Names[Item_Index]), Name);
		items_owned[Item_Index] = true;
	}
	void buy_Car(char Name[], int Item_number, int Spec) {
		strcpy_s((Cars_Owned_shapes[Item_number]), Name);
		Cars_Owned[Item_number] = true;
		Car_Width[Item_number] = Spec;
	}
	int Number_of_cars_Owned()
	{
		int Counter = 0;
		for (int i = 0; i < 10; i++)
			if (Cars_Owned[i] == true)
				Counter++;
		return Counter;
	}
	void operator-(int price) { Coins -= price; }
	void static Increment_No_of_Profiles() { No_of_Player_Profiles1++; }
	static void reset_Number_ofProfiles() {
		No_of_Player_Profiles1 = -1;
	}
	void update_high_Score(int new_high_score) { high_score = high_score + (new_high_score - high_score); }
	int get_high_score() const { return high_score; }
	char* get_item_Owned_Name(int index) {
		if (items_owned[index] == 1 || items_owned[index] == true)
			return Items_Owned_Names[index];
	}
	bool get_Car_owned(int Index) const { return Cars_Owned[Index]; }
	void Display_items_Owned()
	{
		short position = 12;
		for (int i = 0; i < 4; i++)
			if (items_owned[i] == true || items_owned[i] == 1) {
				SetConsoleCursorPosition(Console, { 55, position++ });
				cout << i << ". " << Items_Owned_Names[i];
			}
	}
	char* get_Car_Owned_Shape_Array(int index) { return Cars_Owned_shapes[index]; }
	int get_coins() const { return Coins; }
	bool check_if_Player_has_item(int item_Index) const { return items_owned[item_Index]; }
	bool check_if_Player_has_Car(int item_Index) const { return Cars_Owned[item_Index]; }
	void set_Car_Width(int newWidth, int index) { Car_Width[index] = newWidth; }
	int get_Car_width(int index) { return Car_Width[index]; }
	void Give_Coins() { Coins += 1; }
	~Driver()
	{
		Coins = 4000;
		if (!(No_of_Player_Profiles1 <= -1))
		{
			No_of_Player_Profiles1--;
		}
		isActive = 0;
		strcpy_s(Driver_Name, "");
		high_score = 0;
		for (int i = 0; i < 10; i++) {
			items_owned[i] = false;
			Cars_Owned[i] = false;
			strcpy_s(Items_Owned_Names[i], "");
			strcpy_s(Cars_Owned_shapes[i], "");
		}
	}
};
int Driver::No_of_Player_Profiles1 = -1;
class Player_Car : public Car	//Player car
{
protected:
	Driver Driver_of_Car;
	int Score;
	int Lives;
	//	bool items_available_to_use[4];
public:
	Player_Car() {
		for (int i = 0; i < 3; i++)
		{
			//items_available_to_use[i] = false;
		}
		Car_Width = 3;
		Car_Color = 10;
		Position_Cordinates = { 45,21 };
		Score = 0;
		Lives = 3;
	}
	void operator--() { if (!(Lives <= 0))Lives--; }
	void Draw_Car(int Speed) //PLAYER Car Drawer
	{
		COORD new_Position;
		new_Position.X = Position_Cordinates.X;
		new_Position.Y = Position_Cordinates.Y;
		SetConsoleTextAttribute(Console, Car_Color); //Green Color
		for (int i = 0; i < car.size(); i++)
		{
			if (i % 4 == 0)
			{
				new_Position.Y++;
				SetConsoleCursorPosition(Console, new_Position);
			}
			for (int i = 0; i < Speed; i++) {}	//show Animation
			cout << car[i];
		}
	}
	void operator++() { Score++; }
	void display_score() {
		COORD Score_Position = { 83,4 };
		SetConsoleTextAttribute(Console, 14);
		SetConsoleCursorPosition(Console, Score_Position);
		cout << "Score:" << Score;
		return;
	}
	void reset_Score() { Score = 0; }
	void set_Car(string Car) { car = Car; }
	/*void Set_items_available_to_use(Driver Driver) {
		for (int i = 0; i < 4; i++)
			items_available_to_use[i] = Driver.check_if_Player_has_item(i);
	}*/
	/*bool Get_items_available_to_use(int Index) const {
		return items_available_to_use[Index];
	}*/
	bool get_items_Availabe_fr_Driv(int Index4) {
		if (Driver_of_Car.check_if_Player_has_item(Index4)) {
			return true;
		}
			
		return false;
		
	}
	void Move_Player_Car(char ch) {
		if (ch == 'a' || ch == 'A' || ch == 75)//left
		{
			if (!(getPosition_X() < 3))
			{
				EraseCar(Ultra_Fast_Speed);
				Update_Position_X(getPosition_X() - 4);
				Draw_Car(Ultra_Fast_Speed);
			}
		}
		else if (ch == 'd' || ch == 'D' || ch == 77)//right
		{
			if (!(getPosition_X() > (WIN_WIDTH))) {
				EraseCar(Ultra_Fast_Speed);
				Update_Position_X(getPosition_X() + 4);
				Draw_Car(Ultra_Fast_Speed);
			}
		}
		else if (ch == 'w' || ch == 'W' || ch == 72)//Up
		{
			if (!(getPosition_Y() < 4))
			{
				EraseCar(Ultra_Fast_Speed);
				Update_Position_Y(getPosition_Y() - 4);
				Draw_Car(Ultra_Fast_Speed);
			}
		}
		else if (ch == 's' || ch == 'S' || ch == 80)//down
		{
			if (!(getPosition_Y() > (SCREEN_HEIGHT - 8)))
			{
				EraseCar(Ultra_Fast_Speed);
				Update_Position_Y(getPosition_Y() + 4);
				Draw_Car(Ultra_Fast_Speed);
			}
		}
	}
	void Set_Car_Width(int Width) { Car_Width = Width; }
	void set_Driver_of_Car(Driver DriverofCar) { Driver_of_Car = DriverofCar; }
	int get_score() const { return Score; }
	int get_Lives() const { return Lives; }
	void DisplayLives(COORD Lives_Setting) {
		SetConsoleCursorPosition(Console, { Lives_Setting.X,short(Lives_Setting.Y - 1) });
		SetConsoleTextAttribute(Console, 13);
		cout << "Lives";
		for (int i = 0; i < Lives; i++)
		{
			SetConsoleCursorPosition(Console, Lives_Setting);
			cout << char(3) << "  ";
			Lives_Setting.X += 2;

		}
	}
	void Reset_Lives() { Lives = 3; }
};
class Gun {
protected:
	int bullet_color = 9;
	string bullet = "\x18";
	COORD Bullet_Position;
	bool Active_Bullet_Status;
	bool Bullet_Collision_wh_Enemy_car_status;
public:
	static int Gun_Maganize;
	static int Number_of_Active_Bullets;
	static int Maganize_Counter;
	static bool Maganize_Reload[10];
	Gun()
	{
		Maganize_Counter = 0;
		Number_of_Active_Bullets = 0;
		bullet = "\x18";
		Active_Bullet_Status = 1;
		Bullet_Collision_wh_Enemy_car_status = 0;
		Gun_Maganize = 5;
		for (int i = 0; i < 3; i++)
		{
			Maganize_Reload[i];
		}
	}
	static void update_Gun_Maganize(int newMaganize) { Gun_Maganize = newMaganize; }
	static int get_Gun_Maganize() { return  Gun_Maganize; }
	void Fire_Bullet(Player_Car Player, int Signal)
	{
		Maganize_Counter++;
		cout << "\a";
		Active_Bullet_Status = 1;
		Number_of_Active_Bullets++;
		Bullet_Position = Player.get_Player_Position();
		if (Player.get_items_Availabe_fr_Driv(2) && Signal == 1)
		{
			if (Player.get_Car_width() == 3) {
				//cout << Player.get_Car_width();
				Bullet_Position.X += 1;
			}
			if (Player.get_Car_width() == 4) {
				//cout << Player.get_Car_width();
				//Bullet_Position.X = Bullet_Position.X+1;
			}
		}
		if (Player.get_items_Availabe_fr_Driv(2) && Signal == 2)
		{
			Bullet_Position.X += 3;

		}
		if (Player.get_items_Availabe_fr_Driv(0) && Player.get_items_Availabe_fr_Driv(2) == false)
		{
			Bullet_Position.X += 2;
		}
		SetConsoleTextAttribute(Console, bullet_color);
		SetConsoleCursorPosition(Console, Bullet_Position);
		cout << "\x18";
		//cout << bullet;
	}
	void Move_Bullet(Gun bullets[])
	{
		if (!(Bullet_Position.Y < 2))
		{
			bullet = "\x18";
			Bullet_Position.Y--;
			SetConsoleTextAttribute(Console, bullet_color);
			SetConsoleCursorPosition(Console, Bullet_Position);
			cout << bullet;
			SetConsoleCursorPosition(Console, { Bullet_Position.X, short(Bullet_Position.Y + 1) });
			cout << " ";
		}
		if ((Bullet_Position.Y < 2))
		{
			SetConsoleCursorPosition(Console, { Bullet_Position.X, short((Bullet_Position.Y)) });
			cout << " ";
			Active_Bullet_Status = 0;
		}
	}
	COORD get_Bullet_Position() const { return Bullet_Position; }
	int get_Bullet_Position_Y() const { return Bullet_Position.Y; }
	int get_Bullet_Position_X() const { return Bullet_Position.X; }
	bool get_Active_Bullet_Status() const { return Active_Bullet_Status; }
	void set_Bullet_Collision_wh_Enemy_car_status(bool truefalse) { Bullet_Collision_wh_Enemy_car_status = truefalse; }
	bool get_Bullet_Collision_wh_Enemy_car_status() const { return Bullet_Collision_wh_Enemy_car_status; }
	static void Jamm_Gun_till_reload() {
		SetConsoleCursorPosition(Console, { 34,28 });
		SetConsoleTextAttribute(Console, 9);

			cout << Maganize_Counter << " / " << Gun::Gun_Maganize << " ";

		if ((Maganize_Reload[0] == false))
		{
			Maganize_Reload[0] = true;
			return;
		}
		if ((Maganize_Reload[1] == false && Maganize_Reload[0] == true))
		{
			Maganize_Reload[1] = true;
			return;
		}
		if (Maganize_Reload[2] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true)
		{
			Maganize_Reload[2] = true;
			return;
		}
		if (Maganize_Reload[3] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true && Maganize_Reload[2] == true)
		{
			Maganize_Reload[3] = true;
			return;
		}
		if (Maganize_Reload[4] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true && Maganize_Reload[2] == true && Maganize_Reload[3] == true)
		{
			Maganize_Reload[4] = true;
			Gun::Maganize_Counter = 0;
			SetConsoleTextAttribute(Console, 9);
			SetConsoleCursorPosition(Console, { 42,28 });
			cout << "     Fire     ";
			return;
		}
	}
	static bool get_Maganize_Reload(int index) { return Maganize_Reload[index]; }
	~Gun() {
		bullet = "\x18";
		Bullet_Position = { 0 ,0 };
		Active_Bullet_Status = 0;
		if (Number_of_Active_Bullets != 0)
		{
			Number_of_Active_Bullets--;
		}
	}
};
int Gun::Gun_Maganize = 5;
int Gun::Number_of_Active_Bullets = 0; // static initialization
int Gun::Maganize_Counter = 0; // static initialization
bool Gun::Maganize_Reload[10] = { true };
class Enemy_car : public Car		//***** Enemy Car *****//
{
protected:
	bool Enemy_car_Active;
public:
	Enemy_car() {
		Position_Cordinates.X = generate_Enemy_X_coordinate();
		Position_Cordinates.Y = 4;	//Starting point of Enemy
		Car_Color = 12;	//Red Color
		car = " -- *±±*±±±±*±±* vv ";//20
	}
	int generate_Enemy_X_coordinate() { return 0 + (rand() % WIN_WIDTH + 2); }
	void resetEnemy() {
		Position_Cordinates.X = generate_Enemy_X_coordinate();
		Position_Cordinates.Y = 4;
	}
	bool get_Enemy_Alive_Status() const { return Enemy_car_Active; }
	void Draw_Car(Player_Car& Player) //Enemy Car 
	{
		if (get_Collision_Status())
		{
			return;
		}
		COORD new_Position = { 0,0 }; //bullet_Position;
		{
			if (!(Position_Cordinates.Y > SCREEN_HEIGHT + 2) && !get_Collision_Status())
			{
				Position_Cordinates.Y++;
				SetConsoleCursorPosition(Console, Position_Cordinates);
				int count = 0;
				new_Position = Position_Cordinates;
				int counter = 0;
				for (int i = 19; i >= 0; i--)
				{
					counter++;
					if (counter == 5)
					{
						counter = 1;
						new_Position.Y--;
						SetConsoleCursorPosition(Console, new_Position);
					}
					//	for (int i = 0; i < Ultra_Fast_Speed; i++) {}	//show Animation
					SetConsoleTextAttribute(Console, Car_Color);
					if (!(new_Position.Y > SCREEN_HEIGHT - 1)) {
						cout << car[i];
					}
				}
				if (new_Position.Y > SCREEN_HEIGHT - 2)
				{
					Enemy_car_Active = 0;
					++Player;
					Player.display_score();
				}
				int minus = 0;
				if (Player.get_items_Availabe_fr_Driv(2))
					minus = 2000;
				for (int i = 0; i < 988999 - minus; i++) {}	//HOW FAST ENEMY WILL MOVE
			//	for (int i = 0; i < 918080 - minus; i++) {}	//HOW FAST ENEMY WILL MOVE

				EraseEnemyTrail();
				if (new_Position.Y > SCREEN_HEIGHT - 2)
					resetEnemy();
			}
			else
				return;
		}
	}
	//void Erase_Enemy_Car(int speed) { Car::EraseCar(speed); }
	void EraseEnemyTrail() {
		SetConsoleTextAttribute(Console, Car_Color);
		COORD Old_Position;
		Old_Position.X = Position_Cordinates.X;
		Old_Position.Y = (Position_Cordinates.Y - 4);
		SetConsoleCursorPosition(Console, Old_Position);
		//for (int i = 0; i < Ultra_Fast_Speed; i++) {}
		cout << "    ";
	}
	~Enemy_car() {
		Enemy_car_Active = 1;
		car = " ";
		Position_Cordinates = { 0, 4 };
	}
	void Draw_Car(int Speed) {}
	void update_Collision_Status(bool new_Collision) { Collsion = new_Collision; }
};
class shop
{
protected:
	char Item_Name[50] = "";
	int Specs_or_quantity;
	int price;
	bool has_any_specs_or_quantity;
public:
	shop() : price(0), has_any_specs_or_quantity(false), Specs_or_quantity(0) {}
	shop(char item_name[], int price) : price(price) {}
	void set_Item_Name(string Name) { strcpy_s(Item_Name, Name.c_str()); }
	void set_Item_Price(int price) { this->price = price; }
	void set_Item_Specs_or_quantity(int Specs_or_quantity) {
		this->Specs_or_quantity = Specs_or_quantity;	has_any_specs_or_quantity = true;
	}
	void set_Char_Item_Name(char myarray[]) {
		strcpy_s(Item_Name, myarray);
	}
	char* get_Char_Item_Name() { return Item_Name; }
	int get_Item_Specs_or_quantity() const {

		return Specs_or_quantity;
	}
	int get_price() const { return price; }
	void User_Input()
	{
		cin.ignore();		cout << "Enter Name of item:";			cin.getline(Item_Name, 50, '\n');
		cout << "Enter Price:"; 			cin >> price;
	}
	void Print_Details() { cout << "\nName of item: "; cout << Item_Name;	cout << "\tPrice: "; cout << price; }
};
void Validate_Input(int start, int& Input, int end) {
	while (Input < start || Input > end)
	{
		//cout << "Invalid Input\tReenter plz";
		Input = _getch() - '0';
	}
}
bool Gun_jammed_Status() {
	int Counter = 0;
	for (int i = 0; i < 3; i++) {
		if (Gun::get_Maganize_Reload(i) == true)
			Counter++;
	}
	if (Counter == 3)
	{
		//cout << "  FIRE!!  ";
		return true;
	}
	//cout << "  !NO FIRE  ";
	return false;
}
void Print_Car_Char_Array(shop Cars[], COORD& position, int i, bool signal) {
	//int Car_Width = Cars[i].get_Item_Specs_or_quantity();
	SetConsoleCursorPosition(Console, { short(position.X - 3), short(position.Y + 2) });
	cout << i << ". ";
	int yincrease = position.Y;
	char* car = Cars[i].get_Char_Item_Name();	//	" ^^ [±±] ±± [±±] -- ";  " ^^ \n[±±]\n ±± \n[±±]\n -- "
	//position.X -= 3;
	SetConsoleCursorPosition(Console, { position.X,position.Y });
	for (int j = 0; j < strlen(car); j++)
	{
		if (j % (4) == 0)
			SetConsoleCursorPosition(Console, { position.X,short(yincrease++) });
		cout << car[j];
	}

	if (signal) {
		SetConsoleCursorPosition(Console, { short(position.X - 2),short(position.Y + 5) });
		cout << "Price" << Cars[i].get_price() << endl;
	}
	position.X += 13; //position.Y -= 4;
}
void Read_Player_Profile_From_file(Driver Player_profile[]) {
	ifstream ifstream_ob;
	ifstream_ob.open("Player_profile.txt", ios::in);
	//cout << "\nReading the object from a file : \n";
	ifstream_ob.read((char*)&Player_profile, sizeof(Player_profile));
	ifstream_ob.close();
}
void Write_Player_Profile_to_File(Driver Player_Profile[]) {
	ofstream ofstream_ob;
	ofstream_ob.open("Player_profile.txt", ios::out);
	for (int i = 0; i < 2; i++)
	{
		ofstream_ob.write((char*)&Player_Profile, sizeof(Player_Profile));
	}
	//cout << "Congrats! Your object is successfully written to the file \n";
	ofstream_ob.close();
}
void Read_Items_From_File(shop items[]) {
	ifstream ifstream_ob;
	ifstream_ob.open("Items_Inventory.txt", ios::in);
	cout << "\nReading the object from a file : \n";
	ifstream_ob.read((char*)&items, sizeof(items));
	ifstream_ob.close();
}
int main()
{
	HWND hWnd = GetConsoleWindow();		ShowWindow(hWnd, SW_SHOWMAXIMIZED);	//Make Console open in Maximized window.
	Player_Car Car1;
	/*while (1) {
		//SetConsoleTextAttribute(Console, 255);
		COORD Genederight = { 15,15 };
		COORD Genedeleft = { 15,15 }; //Player.get_Player_Position()
		for (int i = 0; i < 8; i++)
		{
			if (i == 0) {
				SetConsoleCursorPosition(Console, { short(Genederight.X + 1),Genederight.Y });
				cout << "*";
			}
			else
			{
				SetConsoleCursorPosition(Console, Genederight);
				cout << "*";
				if (i % 2 == 0) {
					//	cout << " ";
					Genederight.Y++;
				}
				if (i > 3)
				{
					Genederight.X;
				}
				else
					Genederight.X++;

				for (int i = 0; i < 9999999; i++) {}
			}
		}
		for (int i = 0; i < 8; i++)
		{
			if (i == 0) {
				SetConsoleCursorPosition(Console, { short(Genedeleft.X + 1),Genedeleft.Y });
				cout << "*";
			}
			else
			{
				SetConsoleCursorPosition(Console, Genedeleft);
				cout << "*";
				if (i % 2 == 0) {
					//	cout << " ";
					Genedeleft.Y++;
				}
				if (i > 3)
				{
					Genedeleft.X;
				}
				else
					Genedeleft.X--;


				for (int i = 0; i < 9999999; i++) {}
			}
		}
	}*/
	shop items[10];
	//for (int i = 0; i < 3; i++){items[i].Print_Details();}
	ifstream ifstream_ob;
	ifstream_ob.open("Items_Inventory.txt", ios::in);
	//cout << "\nReading the object from a file : \n";
	ifstream_ob.read((char*)&items, sizeof(items));
	ifstream_ob.close();
	hidecursor();

	SUPERADMIN ADMIN;
	int input;
	//items[0].set_Item_Name("Gun"); items[0].set_Item_Price(800);	items[1].set_Item_Name("Extended Maganize");items[1].set_Item_Price(800); items[2].set_Item_Name("Double Gun");	items[2].set_Item_Price(1500);
	//items[3].set_Item_Name("Quick Reload");	items[3].set_Item_Price(600);
	cout << "Intentory Read() Wirte()\n0.View Exisiting Data\t1.Enter Data\t2.Write to File\t\n(any other key to leave)";
	input = _getch() - '0';
	while (input >= 0 && input < 3) {
		if (input == 0)
			for (int i = 0; i < 3; i++)
				items[i].Print_Details();

		if (input == 1)
			for (int i = 0; i < 3; i++)
				items[i].User_Input();

		if (input == 2)
		{
			ofstream ofstream_ob;
			ofstream_ob.open("Items_Inventory.txt", ios::out);
			ofstream_ob.write((char*)&items, sizeof(items));
			//cout << "Congrats! Your object is successfully written to the file \n";
			ofstream_ob.close();
		}
		cout << "\n0.View Data\t 1.Enter Data\t2.Write to File\t\n(any other key to leave)";
		input = _getch() - '0';
		////////  READING FROM FILE  /////////
	}
	int y;
	int const No_of_Enemies = 4;
	Driver Player_profile[15];
	cout << "\nDo you want to Read Players Records\?\nPress 1 to Read (any other key to leave)";
	y = _getch() - '0';
	if (y == 1)
	{
		ifstream ifstream_ob1;
		ifstream_ob1.open("Player_profile.txt", ios::in);
		//	cout << "\nReading the object from a file : \n";
		ifstream_ob1.read((char*)&Player_profile, sizeof(Player_profile));
		ifstream_ob1.close();
		for (int i = 0; i < 15; i++)
			if (Player_profile[i].get_IsActive_Status())
				Player_profile->Increment_No_of_Profiles();
	}

	int Profile_Selected, Car_Selected;
	int Input[3];	//shop items[10];
	shop Cars[10];
	{char myarray[50] = " ^^ *±±* ±± *±±* -- ";
	//Cars[0].set_Char_Item_Name(myarray);
	Cars[0].set_Item_Name(" ^^ *±±* ±± *±±* -- ");
	Cars[0].set_Item_Specs_or_quantity(4);
	Cars[0].set_Item_Price(100);
	Cars[1].set_Item_Name(" ^^ [±±] ±± [±±] -- ");
	Cars[1].set_Item_Price(100);
	Cars[1].set_Item_Specs_or_quantity(4);
	Cars[2].set_Item_Name("  \xEF  \xC9\xCB\xbb \xCC\xCE\xB9 \xC8\xCA\xBC \xCF\xCF\xCF");
	Cars[2].set_Item_Price(100);
	Cars[2].set_Item_Specs_or_quantity(3);
	Cars[3].set_Item_Name(" ±± ±**± ** ±**±");
	Cars[3].set_Item_Price(100);
	Cars[3].set_Item_Specs_or_quantity(4);
	Cars[4].set_Item_Name(" ** ±**± ** ±**±");
	Cars[4].set_Item_Price(100);
	Cars[4].set_Item_Specs_or_quantity(4);
	Cars[5].set_Item_Name(" ^^ ±±±± ±± ±\xEF\xEF±");
	Cars[5].set_Item_Price(100);
	Cars[5].set_Item_Specs_or_quantity(4);
	Cars[6].set_Item_Name(" 00 0**0 ** 0**0");
	Cars[6].set_Item_Price(100);
	Cars[6].set_Item_Specs_or_quantity(4);
	Cars[7].set_Item_Name(" ^±^ ±±± *±* *±* ---");
	Cars[7].set_Item_Price(100);
	Cars[7].set_Item_Specs_or_quantity(3);
	Cars[8].set_Item_Name("  \36  |±| ±±± ---");
	Cars[8].set_Item_Price(100);
	Cars[8].set_Item_Specs_or_quantity(3);

	}
	short position1 = 7;
	short position = 12;
	hidecursor();

	system("CLS");
	Player_Car Player;		//Player.set_Position_COORDS(20, 20);		//Player.Draw_Car();
	if (Driver::No_of_Player_Profiles() >= 0)
	{
		SetConsoleCursorPosition(Console, { 53,6 });
		SetConsoleTextAttribute(Console, 15);
		cout << "1. Career/Profile";
	}
	else
	{
		SetConsoleCursorPosition(Console, { 53,6 });
		SetConsoleTextAttribute(Console, 8);
		cout << "1. Career/Profile";
	}
	SetConsoleTextAttribute(Console, 15);
	SetConsoleCursorPosition(Console, { 53,7 });	cout << "2. Create Profile";
	SetConsoleCursorPosition(Console, { 53,8 });	cout << "3. View instructions";
	SetConsoleCursorPosition(Console, { 53,9 });	cout << "4. Exit App";
	Input[0] = _getch() - '0';
	if (Driver::No_of_Player_Profiles() <= -1)
		Validate_Input(2, Input[0], 4);
	else
		Validate_Input(1, Input[0], 4);
	Driver Selected_Driver;
	while (Input[0] == 1 || Input[0] == 2 || Input[0] == 3)
	{
		short position2 = 7;
		short position = 0;
		char chcheck = 't';
		int pausecheck = 0;
		switch (Input[0])
		{
		case 1:		//Select Profile
			system("CLS");
			position = 12;
			SetConsoleCursorPosition(Console, { 53,5 });	//Select Profile
			cout << "Select your Profile";
			for (int i = 0; i <= Driver::No_of_Player_Profiles(); i++) {
				SetConsoleCursorPosition(Console, { 50,position++ });
				if (Player_profile[i].get_IsActive_Status())
				{
					cout << i << ". " << Player_profile[i].get_name();
				}
			}
			Profile_Selected = _getch() - '0';
			Validate_Input(0, Profile_Selected, Driver::No_of_Player_Profiles());
			system("CLS");
			SetConsoleTextAttribute(Console, 15);

			SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
			Selected_Driver = Player_profile[Profile_Selected];
			Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
		
			cout << "Coins " << Player_profile[Profile_Selected].get_coins();

			position = 10;
			SetConsoleCursorPosition(Console, { 50,5 });
			cout << "Welcome back " << Player_profile[Profile_Selected].get_name() << " !";
			SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
			cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
			SetConsoleTextAttribute(Console, 15);
			SetConsoleCursorPosition(Console, { 50,position++ }); cout << "1. Select Car and Play";
			SetConsoleCursorPosition(Console, { 50,position++ }); cout << "2. Buy Car";
			SetConsoleCursorPosition(Console, { 50,position++ }); cout << "3. Display Owned Cars";
			SetConsoleCursorPosition(Console, { 50,position++ }); cout << "4. Shop items";
			SetConsoleCursorPosition(Console, { 50,position++ }); cout << "5. View Items in Inventory";
			SetConsoleCursorPosition(Console, { 50,position++ }); cout << "6. Delete Profile";
			SetConsoleCursorPosition(Console, { 50,position++ }); cout << "7. Exit Profile";
		
			Input[1] = _getch() - '0';
			SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
			cout << "Coins " << Player_profile[Profile_Selected].get_coins();
			while (Input[1] >= 1 || Input[1] <= 7)
			{
				if (Input[1] == 1)				//Select Car and Play
				{
					if (Player_profile[Profile_Selected].Number_of_cars_Owned() == 0)
					{
						system("CLS");
						SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
						cout << "Coins " << Player_profile[Profile_Selected].get_coins();
						SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
						cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
						SetConsoleCursorPosition(Console, { 50,short(position - 8) });
						cout << "You don't have any Car";
						SetConsoleCursorPosition(Console, { 50,short(position - 7) });
						cout << "Buy Car first !!";
						for (int i = 0; i < 454400000; i++) {}
					}
					else
					{
						system("CLS");
						position = 5;
						SetConsoleCursorPosition(Console, { 55,0 });	cout << "Select your Car";
						COORD Printing_Cords = { 33 ,7 };
						int Counter = 0;
						for (int i = 0; i < 10; i++)
							if (Player_profile[Profile_Selected].get_Car_owned(i))
							{
								if (Counter == 5) {
									Printing_Cords = { 33 ,14 };
								}
								Print_Car_Char_Array(Cars, Printing_Cords, i, 0);
								Counter++;
							}
						Car_Selected = _getch() - '0';
						while (!Player_profile[Profile_Selected].check_if_Player_has_Car(Car_Selected))
						{
							cout << "Select Car from your owned Car list only";
							Car_Selected = _getch() - '0';
						}
						Player.Set_Car_Width(Player_profile[Profile_Selected].get_Car_width(Car_Selected));
						Player.set_Car(Player_profile[Profile_Selected].get_Car_Owned_Shape_Array(Car_Selected));
						char ch1;
						SetConsoleCursorPosition(Console, { 47,22 });
						SetConsoleTextAttribute(Console, 15);
						cout << " Press Spacebar to start Game!";
						//Player.Set_items_available_to_use(Player_profile[Profile_Selected]);
						ch1 = _getch();
						Player.reset_Score();
						int Score_Coins_Counter = 0;
						if (ch1 == 32)
						{
							Player.Reset_Lives();
							system("CLS");
							Player.DisplayLives((ADMIN.Lives_Setting()));
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							SetConsoleTextAttribute(Console, 11);
							cout << "Coins " << Player_profile[Profile_Selected].get_coins();
							srand(unsigned int(time(0)));
							COORD Position;	Position.X = WIN_WIDTH;	Position.Y = SCREEN_HEIGHT;
							Gun bullets[50];
							position2 = 8;
							Enemy_car  Enemy2[No_of_Enemies];
							Player.Draw_Car(Ultra_Fast_Speed);
							Player.display_score();
							if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
							{
								Player_profile[Profile_Selected].update_high_Score(Player.get_score());
								Score_Coins_Counter++;
								if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
								{
									Player_profile[Profile_Selected].Give_Coins();
									Score_Coins_Counter = 0;
								}
							}
							SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
							cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << "  ";
							SetConsoleCursorPosition(Console, { 100,position2++ });
							cout << "Instruction:";
							SetConsoleCursorPosition(Console, { 100,position2++ });
							cout << "\'A\' - Left";
							SetConsoleCursorPosition(Console, { 100,position2++ });
							cout << "\'D\' - Right";
							SetConsoleCursorPosition(Console, { 100,position2++ });
							cout << "\'W\' - Up";
							SetConsoleCursorPosition(Console, { 100,position2++ });
							cout << "\'S\' - Down";
							SetConsoleCursorPosition(Console, { 100,position2++ });
							cout << "\'P\' - Pause Game";
							if (Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2)) {
								SetConsoleCursorPosition(Console, { 100,position2++ });
								cout << "\'R\' - Reload";
								SetConsoleCursorPosition(Console, { 100,position2++ });
								cout << "Space - Fire";
							}
							SetConsoleCursorPosition(Console, { 98,position2++ });
							cout << "Q - Quit Gameplay";
							bool Game_Running = true;
							static int Counter = 0;
							Counter = 0;
							Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
							while (ch1 != 'q' && Game_Running)
							{
								SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
								SetConsoleTextAttribute(Console, 11);
								cout << "Coins " << Player_profile[Profile_Selected].get_coins();
								if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
								{
									Player_profile[Profile_Selected].Give_Coins();
									Score_Coins_Counter = 0;
								}
								if (Player.get_items_Availabe_fr_Driv(1)) { Gun::Gun_Maganize = 10; }
								if (Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2))
								{
									Gun::Jamm_Gun_till_reload();
								}
								if (_kbhit()) {
									ch1 = _getch();
									if (ch1 == 'a' || ch1 == 'A' || ch1 == 75 || ch1 == 'd' || ch1 == 'D' || ch1 == 77 || ch1 == 'w' || ch1 == 'W' || ch1 == 72 || ch1 == 's' || ch1 == 'S' || ch1 == 80)
									{
										Player.Move_Player_Car(ch1);
									}
									else if (ch1 == 'r' || ch1 == 'R')	//Reload
									{
										SetConsoleCursorPosition(Console, { 44,28 });
										cout << "RELOADING!!!";
										for (int i = 0; i < 5; i++)
											Gun::Maganize_Reload[i] = false;
									}
									else if (ch1 == 32 && Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2) && Gun_jammed_Status() && ch1 == 32)
									{

										if (Gun_jammed_Status())
										{
											bullets[Gun::Number_of_Active_Bullets].Fire_Bullet(Player, 1);
										}
										if (Gun::Maganize_Counter % Gun::get_Gun_Maganize() == 0 && Gun::Maganize_Counter != 0)
										{
											SetConsoleCursorPosition(Console, { 44,28 });
											cout << "RELOADING!!!";
											for (int i = 0; i < 5; i++)
												Gun::Maganize_Reload[i] = false;
										}
										if (Player.get_items_Availabe_fr_Driv(2) && Gun_jammed_Status()) {

											bullets[Gun::Number_of_Active_Bullets].Fire_Bullet(Player, 2);
											if (Gun::Maganize_Counter % Gun::get_Gun_Maganize() == 0 && Gun::Maganize_Counter != 0)
											{
												SetConsoleCursorPosition(Console, { 42,28 });
												cout << "RELOADING!!!";
												for (int i = 0; i < 5; i++)
													Gun::Maganize_Reload[i] = false;
											}
										}
									}
									/*else if (ch1 == 'x' || ch1 == 'X') {
										COORD Genederight = { 15,15 };
										COORD Genedeleft = { 15,15 }; //Player.get_Player_Position()
										int Counter = 0;
										for (int i = 0; i < 10; i++)
										{
											SetConsoleCursorPosition(Console, Genederight);
											cout << "@";
											Genederight.X++;
											if (Counter == 1) {
												Genederight.Y++;
												Counter = 0;
											}
											for (int i = 0; i < 9999999; i++) {}
											Counter++;
										}
										for (int i = 0; i < 10; i++)
										{
											SetConsoleCursorPosition(Console, Genedeleft);
											cout << "#";
											for (int i = 0; i < 9999999; i++) {}

											Genedeleft.X--; Genedeleft.Y++;
										}

									}*/
									else if (ch1 == 'p' || ch1 == 'P') {
										/*pausecheck++;
										if (pausecheck >1) {
											cout << "Pause unlocked";
											pausecheck = 0;
											chcheck = 'p';
											bool pause = true;
										}*/
										while (chcheck != 'p' )
										{
											//for(int i = 0;i<1;i++){}
											chcheck = _getch();
										}
										chcheck = 't';
									}
									else if (ch1 == 'q') {
										break;
									}
								}
								for (int enemy_loop = 0; enemy_loop < No_of_Enemies; enemy_loop++)
								{
									if (!Enemy2[enemy_loop].get_Collision_Status())
									{
										Enemy2[enemy_loop].Draw_Car(Player);
										if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
										{
											Player_profile[Profile_Selected].update_high_Score(Player.get_score());
											Score_Coins_Counter++;
											if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
											{
												Player_profile[Profile_Selected].Give_Coins();
												Score_Coins_Counter = 0;
											}
										}
										SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
										cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
										COORD Position_Cordinates = Enemy2[enemy_loop].get_Player_Position(); // Enemy CAR Position
										COORD Player_Position = Player.get_Player_Position();
										//if ((Position_Cordinates.Y - 1) >= Player_Position.Y && (Position_Cordinates.Y - 10) <= Player_Position.Y)
										if ((Position_Cordinates.Y - 1) >= Player_Position.Y && (Position_Cordinates.Y - 11) <= Player_Position.Y)//(//Position_Cordinates.Y - 1) == Player_Position.Y 
										//	|| (Position_Cordinates.Y - 2) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 3) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 4) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 5) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 6) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 7) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 8) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 9) == Player_Position.Y
										//	|| (Position_Cordinates.Y - 10) == Player_Position.Y)
										{
											if (Position_Cordinates.X == Player_Position.X
												|| Position_Cordinates.X + 1 == Player_Position.X		//player right by one, enemy left(pos).
												|| Position_Cordinates.X + 2 == Player_Position.X	//// player right by two, enemy left(pos).
												|| Player.get_Car_width() == 4 && Position_Cordinates.X + 3 == Player_Position.X //(pos)player right ,enemy left.   player most left collision with enemy most right(disable in thinner car)
												|| Position_Cordinates.X - 3 == Player_Position.X	//(pos)player left ,enemy right.   player most right collision with enemy most left
												|| Position_Cordinates.X - 2 == Player_Position.X	// player left by two, enemy right(pos).
												|| Position_Cordinates.X - 1 == Player_Position.X)	// player left by one, enemy right(pos).			
											{
												//Counter++;
												COORD collision_Indicator = ADMIN.Lives_Setting();
												SetConsoleCursorPosition(Console, { collision_Indicator.X,short(collision_Indicator.Y + 2) });
												//cout << " Collision";
												--Player;
												Player.DisplayLives((ADMIN.Lives_Setting()));
												if (Player.get_Lives() == 0) {
													Game_Running = false;
												}
												Enemy2[enemy_loop].Update_Position_Y(Position_Cordinates.Y - 5);
												Enemy2[enemy_loop].EraseCar(Ultra_Fast_Speed);
												Player.Draw_Car(Ultra_Fast_Speed);
												Enemy2[enemy_loop].resetEnemy(); //for checking
											}
										}
										else
											Enemy2[enemy_loop].update_Collision_Status(0);

										for (int i = 0; i < Gun::Number_of_Active_Bullets; i++)
										{
											if (bullets[i].get_Active_Bullet_Status() == 0)
											{
												bullets[i].~Gun();
												for (int j = i; j < Gun::Number_of_Active_Bullets; j++) {
													bullets[j] = bullets[j + 1];
												}
											}
											if (Enemy2[enemy_loop].getPosition_Y() == bullets[i].get_Bullet_Position_Y())
											{
												if (Enemy2[enemy_loop].getPosition_X() == bullets[i].get_Bullet_Position_X()		//left most (1st col)
													|| (Enemy2[enemy_loop].getPosition_X() + 1) == bullets[i].get_Bullet_Position_X()	// 2nd column
													|| (Enemy2[enemy_loop].getPosition_X() + 2) == bullets[i].get_Bullet_Position_X()	//3rd col
													|| (Enemy2[enemy_loop].getPosition_X() + 3) == bullets[i].get_Bullet_Position_X())	//4th col, right most
												{
													bullets[i].~Gun();
													for (int j = i; j < Gun::Number_of_Active_Bullets; j++)
													{
														bullets[j] = bullets[j + 1];
													}
													Enemy2[enemy_loop].setPosition_Y(Enemy2[enemy_loop].getPosition_Y() - 4);
													Enemy2[enemy_loop].EraseCar(Ultra_Fast_Speed);
													Enemy2[enemy_loop].resetEnemy();
													++Player;
													Player.display_score();
													if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
													{
														Player_profile[Profile_Selected].update_high_Score(Player.get_score());
														Score_Coins_Counter++;
														if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
														{
															Player_profile[Profile_Selected].Give_Coins();
															Score_Coins_Counter = 0;
														}
													}
													SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
													cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << "  ";
													bullets[i].set_Bullet_Collision_wh_Enemy_car_status(1);
												}
											}
										}
									}
								}
								for (int i = 0; i < Gun::Number_of_Active_Bullets; i++) //now changed
								{//
									bullets[i].Move_Bullet(bullets);
									if (bullets[i].get_Active_Bullet_Status() == 0)
									{
										bullets[i].~Gun();
										for (int j = i; j < Gun::Number_of_Active_Bullets; j++) {
											bullets[j] = bullets[j + 1];
										}
									}
									for (int Enemy_loop = 0; Enemy_loop < No_of_Enemies; Enemy_loop++)
									{
										if (Enemy2[Enemy_loop].getPosition_Y() == bullets[i].get_Bullet_Position_Y())
										{
											if (Enemy2[Enemy_loop].getPosition_X() == bullets[i].get_Bullet_Position_X()			//left most (1st col)
												|| (Enemy2[Enemy_loop].getPosition_X() + 1) == bullets[i].get_Bullet_Position_X()	// 2nd column
												|| (Enemy2[Enemy_loop].getPosition_X() + 2) == bullets[i].get_Bullet_Position_X()	//3rd col
												|| (Enemy2[Enemy_loop].getPosition_X() + 3) == bullets[i].get_Bullet_Position_X())	//4th col, right most
											{
												SetConsoleCursorPosition(Console, bullets[i].get_Bullet_Position());
												SetConsoleTextAttribute(Console, 15);
												bullets[i].~Gun();
												for (int j = i; j < Gun::Number_of_Active_Bullets; j++)
												{
													bullets[j] = bullets[j + 1];
												}
												Enemy2[Enemy_loop].setPosition_Y(Enemy2[Enemy_loop].getPosition_Y() - 4);
												Enemy2[Enemy_loop].EraseCar(Ultra_Fast_Speed);
												Enemy2[Enemy_loop].resetEnemy();
												++Player;
												if (Player.get_score() > Player_profile[Profile_Selected].get_high_score()) {
													Player_profile[Profile_Selected].update_high_Score(Player.get_score());
													Score_Coins_Counter++;
													if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
													{
														Player_profile[Profile_Selected].Give_Coins();
														Score_Coins_Counter = 0;
													}
												}
												SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
												cout << "High Score " << Player_profile[Profile_Selected].get_high_score();
												bullets[i].set_Bullet_Collision_wh_Enemy_car_status(1);
											}
										}
									}
								}
							}
							system("CLS");
							SetConsoleTextAttribute(Console, 10);
							SetConsoleCursorPosition(Console, { 57,9 });
							cout << "-----------";
							SetConsoleCursorPosition(Console, { 58,10 });
							cout << "GAME OVER";
							SetConsoleCursorPosition(Console, { 57,11 });
							cout << "-----------";
							SetConsoleCursorPosition(Console, { 55,12 });
							cout << "Score:" << Player.get_score();
							SetConsoleCursorPosition(Console, { 55,13 });
							cout << "Press any key";
							for (int i = 0; i < 99999; i++) {}
							_getch();
							

						}
					}
				}
				else if (Input[1] == 2) {	//Buy Car
					system("CLS");
					SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
					cout << "Coins " << Player_profile[Profile_Selected].get_coins();
					short position1 = 7;
					COORD Printing_Cords = { 33 ,7 };
					SetConsoleCursorPosition(Console, { 59,5 }); cout << "BUY CAR";
					for (int i = 0; i < 9; i++)
					{
						if (i == 5)
							Printing_Cords = { 33 ,14 };
						//Printing_Cords.Y += 10;
						Print_Car_Char_Array(Cars, Printing_Cords, i, 1);
					}
					Input[2] = _getch() - '0';
					if (!(Player_profile[Profile_Selected].check_if_Player_has_Car(Input[2])))
					{
						if (Player_profile[Profile_Selected].get_coins() >= Cars[Input[2]].get_price())
						{
							Player_profile[Profile_Selected].buy_Car(Cars[Input[2]].get_Char_Item_Name(), Input[2], Cars[Input[2]].get_Item_Specs_or_quantity());
							Player_profile[Profile_Selected] - Cars[Input[2]].get_price();
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							cout << "Coins " << Player_profile[Profile_Selected].get_coins();
							Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
						}
						else {
							cout << "Need More Coins!";
							for (int i = 0; i < 454400000; i++) {}
						}
					}
					else
					{
						SetConsoleCursorPosition(Console, { 55,24 });
						SetConsoleTextAttribute(Console, 15);
						cout << "Already owned";
						for (int i = 0; i < 454400000; i++) {}
					}
				}
				else if (Input[1] == 3)
				{
					system("CLS");
					SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
					cout << "Coins " << Player_profile[Profile_Selected].get_coins();
					short position1 = 7;
					COORD Printing_Cords = { 33 ,7 };
					int Counter = 0;
					SetConsoleCursorPosition(Console, { 57,5 }); cout << "CAR GARAGE";
					for (int i = 0; i < 9; i++)
					{
						if (Counter == 5) {
							Printing_Cords = { 33 ,14 };
						}
						if (Player_profile[Profile_Selected].check_if_Player_has_Car(i)) {
							Print_Car_Char_Array(Cars, Printing_Cords, i, 1);
							Counter++;
						}
					}
					SetConsoleCursorPosition(Console, { 50,23 });
					cout << "5.    Leave Garage";
					Input[2] = _getch() - '0';
				}
				else if (Input[1] == 4)	//BUY ITEMS
				{
					system("CLS");
					SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
					cout << "Coins " << Player_profile[Profile_Selected].get_coins();
					SetConsoleCursorPosition(Console, { 58,5 }); cout << "BUY ITEMS";
					position = 7;
					SetConsoleCursorPosition(Console, { 45,position++ });
					for (int i = 0; i < 4; i++)
					{
						cout << i << ". ";
						cout << "Item: " << items[i].get_Char_Item_Name();
						SetConsoleCursorPosition(Console, { 75,short(position - 1) });
						cout << "Price" << items[i].get_price();
						SetConsoleCursorPosition(Console, { 45,position++ });
					}
					Input[2] = _getch() - '0';
					if (!(Player_profile[Profile_Selected].check_if_Player_has_item(Input[2])))
					{
						if (Player_profile[Profile_Selected].get_coins() >= items[Input[2]].get_price())
						{
							Player_profile[Profile_Selected].buy_item_in_char_array(items[Input[2]].get_Char_Item_Name(), Input[2]);
							//Player_profile[Profile_Selected].buy_items(items[Input[1]].get_Char_Item_Name(), Input[1]);
							Player_profile[Profile_Selected] - items[Input[2]].get_price();
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							cout << "Coins " << Player_profile[Profile_Selected].get_coins();
							//	Player.Set_items_available_to_use(Player_profile[Profile_Selected]);
							if (Input[2] == 1)Gun::update_Gun_Maganize(10);
						}
						else {
							cout << "Need More Coins!";
							for (int i = 0; i < 454400000; i++) {}
						}
					}
					else {
						cout << "Already owned";
						for (int i = 0; i < 454400000; i++) {}
					}
				}
				else if (Input[1] == 5)
				{
					system("CLS");
					SetConsoleCursorPosition(Console, { 58,5 }); cout << "Items Owned";
					short position = 12;
					for (int i = 0; i < 4; i++)
					{
						Player_profile[Profile_Selected].Display_items_Owned();
					}
					for (int i = 0; i < 454400000; i++) {}
				}
				else if (Input[1] == 6)
				{
					system("CLS");
					SetConsoleCursorPosition(Console, { 55,0 });	cout << "Delete Profile ?";
					SetConsoleCursorPosition(Console, { 54,5 });	cout << "1. Yes, Delete Profile.";
					SetConsoleCursorPosition(Console, { 54,6 });	cout << "2. No, Don\'t Delete Profile.";
					Input[2] = _getch() - '0';
					if (Input[2] == 1) {
						Player_profile[Profile_Selected].~Driver();

						for (int j = Profile_Selected; j <= Driver::No_of_Player_Profiles(); j++)
						{
							Player_profile[j] = Player_profile[j + 1];
						}
					}

					//break;
				}
				if (Input[1] == 7)
				{
					break;
				}
				//for (int i = 0; i < 9000000; i++) {}
				system("CLS");
				SetConsoleTextAttribute(Console, 15);

				SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
				cout << "Coins " << Player_profile[Profile_Selected].get_coins();
				if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
					Player_profile[Profile_Selected].update_high_Score(Player.get_score());
				SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
				cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
				position = 12;
				SetConsoleTextAttribute(Console, 15);
				SetConsoleCursorPosition(Console, { 51,position++ }); cout << "1. Select Car and Play";
				SetConsoleCursorPosition(Console, { 51,position++ }); cout << "2. Buy Car";
				SetConsoleCursorPosition(Console, { 51,position++ }); cout << "3. Display Owned Cars";
				SetConsoleCursorPosition(Console, { 51,position++ }); cout << "4. Shop items";
				SetConsoleCursorPosition(Console, { 51,position++ }); cout << "5. View Items in Inventory";
				SetConsoleCursorPosition(Console, { 51,position++ }); cout << "6. Delete Profile";
				SetConsoleCursorPosition(Console, { 51,position++ }); cout << "7. Exit Profile";

				Input[1] = _getch() - '0';
				if (Input[1] == 7)
				{
					break;
				}
			}
			break;
		case 2:
		{
			system("CLS");
			SetConsoleCursorPosition(Console, { 54,5 });
			cout << "Profile Creation";
			Driver::Increment_No_of_Profiles();
			SetConsoleCursorPosition(Console, { 50,7 });
			Player_profile[Driver::No_of_Player_Profiles()].set_Player_Details();
			break;
		}
		case 3:
			system("CLS");
			position2 = 7;
			SetConsoleCursorPosition(Console, { 57,5 });
			cout << "Instruction:";
			SetConsoleCursorPosition(Console, { 58,position2++ });
			cout << "\'A\' - Left";
			SetConsoleCursorPosition(Console, { 58,position2++ });
			cout << "\'D\' - Right";
			SetConsoleCursorPosition(Console, { 58,position2++ });
			cout << "\'W\' - Up";
			SetConsoleCursorPosition(Console, { 58,position2++ });
			cout << "\'S\' - Down";
			SetConsoleCursorPosition(Console, { 58,position2++ });
			cout << "\'R\' - Reload";
			SetConsoleCursorPosition(Console, { 58,position2++ });
			cout << "\'P\' - Pause Game";
			SetConsoleCursorPosition(Console, { 58,position2++ });
			cout << "Space - Fire";

			SetConsoleCursorPosition(Console, { 56,position2++ });
			cout << "Q - Quit Gameplay";

			for (int i = 0; i < 454400000; i++) {}
			break;
		}
		system("CLS");
		Player_profile->reset_Number_ofProfiles();
		for (int i = 0; i < 15; i++)
			if (Player_profile[i].get_IsActive_Status())
				Player_profile->Increment_No_of_Profiles();
		SetConsoleTextAttribute(Console, 15);
		if (Driver::No_of_Player_Profiles() >= 0)
		{
			SetConsoleCursorPosition(Console, { 53,6 });
			SetConsoleTextAttribute(Console, 15);
			cout << "1. Career/Profile";
		}
		else
		{
			SetConsoleCursorPosition(Console, { 53,6 });
			SetConsoleTextAttribute(Console, 8);
			cout << "1. Career/Profile";
		}
		SetConsoleTextAttribute(Console, 15);
		SetConsoleCursorPosition(Console, { 53,7 });	cout << "2. Create Profile";
		SetConsoleCursorPosition(Console, { 53,8 });	cout << "3. View Instructions";
		SetConsoleCursorPosition(Console, { 53,9 });	cout << "4. Exit App (Player Progress will be Saved)";
		Input[0] = _getch() - '0';
		if (Driver::No_of_Player_Profiles() <= -1)
			Validate_Input(2, Input[0], 4);
		else
			Validate_Input(1, Input[0], 4);
	}

	ofstream ofstream_ob2;
	ofstream_ob2.open("Player_profile.txt", ios::out);
	ofstream_ob2.write((char*)&Player_profile, sizeof(Player_profile));
	ofstream_ob2.close();
}//End of Main