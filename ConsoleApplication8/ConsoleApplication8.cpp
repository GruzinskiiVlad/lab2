#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Time {
private:
	int hour;
	int minute;
	int second;
	int time;
public:
	void set_time(int hour, int minute, int second) {
		this->hour = hour;
		this->minute = minute;
		this->second = second;
		time = hour * 10000 + minute * 100 + second;
	}
	void show_time() {
		cout << hour << ":" << minute << ":" << second;
	}
	int get_time() {
		return time;
	}
};

class Date {
private:
	int day;
	int month;
	int year;
	int date;
public:
	void set_date(int day, int month, int year) {
		this->day = day;
		this->month = month;
		this->year = year;
		date = year * 10000 + month * 100 + day;
	}
	void show_date() {
		cout << day << "." << month << "." << year;
	}
	int get_date() {
		return date;
	}
};

void new_call(int id, vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time);
void show_journal(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time);
void del_call(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time);
void sort_journal(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time);
void search_user(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time);
void from_date_to_date(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time);

int main() {
	setlocale(LC_ALL, "Russian");
	vector<int> ID;
	vector<string> From;
	vector<string> To;
	vector<Date> list_date;
	vector<Time> list_time;
	cout << "Добро пожаловать в базу данных" << "\n1. Добавить новую запись;\n2. Удалить запись из журнала;\n3. Отсортировать по дате и времени;\n4. ";
	cout << "Вывести журнал звонков на экран;\n5. Вывести звонки конкретного пользователя;\n6. Вывести записи от даты до даты.\n";
	int number;
	int id = 0;
	int main_flag = 1;
	cout << "\n";
	while (main_flag != 0) {
		cout << "Укажите номер действий:";
		cin >> number;
		if (number == 1) {
			int flag = 1;
			while (flag != 0) {
				cin.ignore();
				id++;
				new_call(id, ID, From, To, list_date, list_time);
				cout << "\nХотите продолжить заполнение журнала?(да - любая другая цифра; нет = 0)";
				cin >> flag;
			}
		}
		if (number == 2) {
			del_call(ID, From, To, list_date, list_time);
		}
		if (number == 3) {
			sort_journal(ID, From, To, list_date, list_time);
		}
		if (number == 4) {
			if (From.size() == 0) cout << "\nЖурнал пуст!!!\n";
			show_journal(ID, From, To, list_date, list_time);
		}
		if (number == 5) {
			search_user(ID, From, To, list_date, list_time);
		}
		if (number == 6) from_date_to_date(ID, From, To, list_date, list_time);
		cout << "\nХотите выполнить другое действие?(да - 1; нет = 0)";
		cin >> main_flag;
		cout << "\n";
	}
	return 0;
}

void new_call(int id, vector <int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time) {
	ID.push_back(id);
	cout << "\nУкажите, от кого поступил звонок:     ";
	string from;
	getline(cin, from);
	From.push_back(from);
	cout << "Укажите, кому поступил звонок:     ";
	string to;
	getline(cin, to);
	To.push_back(to);
	cout << "Укажите дату звонка(день месяц год):     ";
	int day, month, year;
	cin >> day >> month >> year;
	Date date_call;
	date_call.set_date(day, month, year);
	list_date.push_back(date_call);
	cout << "Укажите время звонка(час минута секунда):     ";
	int hour, minute, second;
	cin >> hour >> minute >> second;
	Time time_call;
	time_call.set_time(hour, minute, second);
	list_time.push_back(time_call);
	cin.ignore();
}

void show_journal(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time) {
	int size = From.size();
	for (int i = 0; i<size; i++) {
		if (From[i] == "") continue;
		cout << ID[i] << "\t" << From[i] << "\t" << To[i];
		cout << "\t";
		list_date[i].show_date();
		cout << "\t";
		list_time[i].show_time();
		cout << endl;
	}
}

void del_call(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time) {
	cout << "Введите ID звонка, который вы хотите удалить!!!\n";
	int id;
	int flag = 0;
	cin >> id;
	if (find(ID.begin(), ID.end(), id) == ID.end()) cout << "Звонка с таким ID не существует!!\n"; else flag = 1;
	if (flag == 1) {
		From[find(ID.begin(), ID.end(), id) - ID.begin()] = "";
		To[find(ID.begin(), ID.end(), id) - ID.begin()] = "";
		list_date[find(ID.begin(), ID.end(), id) - ID.begin()].set_date(0, 0, 0);
		list_time[find(ID.begin(), ID.end(), id) - ID.begin()].set_time(0, 0, 0);
	}
}

void sort_journal(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time) {
	int min_d, min_t, i_min;
	for (int i = 0; i<ID.size(); i++) {
		min_d = list_date[i].get_date();
		min_t = list_time[i].get_time();
		i_min = i;
		if (list_date[i].get_date() == 0) continue;
		for (int j = 0; j<ID.size(); j++) {
			if (j <= i) continue;
			if (list_date[j].get_date() == 0) continue;
			if (list_date[j].get_date()<min_d) {
				min_d = list_date[j].get_date();
				min_t = list_time[j].get_time();
				i_min = j;
			}
			else if (list_date[j].get_date() == min_d) {
				if (list_time[j].get_time()<min_t) {
					min_d = list_date[j].get_date();
					min_t = list_time[j].get_time();
					i_min = j;
				}
			}
			else continue;
		}
		swap(ID[i], ID[i_min]);
		swap(From[i], From[i_min]);
		swap(To[i], To[i_min]);
		swap(list_date[i], list_date[i_min]);
		swap(list_time[i], list_time[i_min]);
	}
}

void search_user(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time) {
	string name;
	cout << "Введите имя пользовалеля!!!\n";
	cin.ignore();
	getline(cin, name);
	int flag = 0;
	for (int i = 0; i<ID.size(); i++) {
		if (From[i] != name) continue;
		if (From[i] == name) {
			cout << ID[i] << "\t" << From[i] << "\t" << To[i];
			cout << "\t";
			list_date[i].show_date();
			cout << "\t";
			list_time[i].show_time();
			cout << endl;
			flag++;
		}
	}
	if (flag == 0) cout << "Звонков от данного пользователя не поступало!!!\n";
}

void from_date_to_date(vector<int> &ID, vector<string> &From, vector<string> &To, vector<Date> &list_date, vector<Time> &list_time) {
	int date1, date2;
	cout << "Введите 2 даты в форме 'годмесяцдень' через пробел: ";
	cin >> date1 >> date2;
	for (int i = 0; i<ID.size(); i++) {
		cout << " " << list_date[i].get_date();
		if ((list_date[i].get_date() >= date1) && (list_date[i].get_date() <= date2)) {
			cout << ID[i] << "\t" << From[i] << "\t" << To[i];
			cout << "\t";
			list_date[i].show_date();
			cout << "\t";
			list_time[i].show_time();
			cout << endl;
		}
	}
}
