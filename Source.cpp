#include <iostream>
#include <fstream>

#include <clocale>

#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");	// Смена страницы кодировки

	//	first node neighbour === True (yes answer)
	//	second node neighbour === False (no answer)

	Graph graph;
	string start_point("Данные структурированы?");

	ifstream in("map_choise_DB_graph_data.txt");	// Считывание графа с файла (Файл обязательно в кодировке ANSII)
	if (!in.is_open())
	{
		cout << "Error with open file" << endl;
		return -1;
	}

	in >> graph;
	in.close();

	Node* now_node = graph.find(start_point);	// Задаем отправную точку
	char choice;
	while (true)	// Основной цикл
	{
		cout << now_node->getName() << endl << ">> ";	// Задаем вопрос (хранится в имени вершины графа)

	enter_choice:
		cin >> choice;	// Получаем ответ

		if (cin.fail())	// Если вдруг ошибка ввода - обрабатываем
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Error input. Try again!\n>> ";
			goto enter_choice;
		}

		if (cin.rdbuf()->in_avail())	// Лишние символы отбрасываем
			cin.ignore(999, '\n');

		if (choice == 'y')	// Обрабатываем ответ
			now_node = now_node->yes;
		else
			now_node = now_node->no;

		if (now_node->is_end())	// Проверяем, не конец ли схемы
			break;
	}

	cout << "\nВам подходит: "<<now_node->getName() << endl;	// Выввод ответа

	return 0;
}