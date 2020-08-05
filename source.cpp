#include <iostream>
#include "graph.h"
using namespace std;


int main() {
	Graph <Vertex<string>, Edge<Vertex<string>, string>>*G;
	Graph <Vertex<string>, Edge<Vertex<string>, string>>::Task1* T1;
	Graph <Vertex<string>, Edge<Vertex<string>, string>>::Task2* T2;

	setlocale(LC_ALL, "rus");
	int menu;

	cout << "1. Создать пустой L-граф с нулевым числом вершин и ребер" << endl;
	cout << "2. Создать граф с V вершинами, без ребер, типа D, формы представления F" << endl;
	cout << "3. Создать граф с V вершинами, с E случайными ребрами, типа D , формы F" << endl;
	cout << "0. Выход" << endl << endl;
	cout << "4. Тестовый граф без отрицательного цикла" << endl;
	cout << "5. С отрицательным циклом" << endl;
	while (true) {
		cout << "-> ";
		cin >> menu;
		switch (menu) {
		case 1: {	
			G = new Graph <Vertex<string>, Edge<Vertex<string>, string>>;
			break;
		};
		case 2: {	
			int v, directed; char F;
			cout << "Количество вершин: ";
			cin >> v;
			cout << "Ориентированный граф (0 - нет, 1 - да): ";
			cin >> directed;
			cout << "Форма графа (L - список, M - матрица): ";
			cin >> F;
			G = new Graph <Vertex<string>, Edge<Vertex<string>, string>>(v, directed, F);
			break;
		};
		case 3: {
			int v, e, directed; char F;
			cout << "Количество вершин: ";
			cin >> v;
			cout << "Количество ребер: ";
			cin >> e;
			cout << "Ориентированный граф (0 - нет, 1 - да): ";
			cin >> directed;
			cout << "Форма графа (L - список, M - матрица): ";
			cin >> F;
			G = new Graph <Vertex<string>, Edge<Vertex<string>, string>>(v, e, directed, F);
			break;
		};
		case 0: {
			return 0;
		};
		case 4: {
			cout << "Форма представления (L - список. M - матрица)";
			char F;
			cin >> F;
			G = new Graph <Vertex<string>, Edge<Vertex<string>, string>>(4, false, F);
			(G->InsertE(G->GetVertex(0), G->GetVertex(1)))->setW(-2);
			(G->InsertE(G->GetVertex(0), G->GetVertex(2)))->setW(5);
			(G->InsertE(G->GetVertex(0), G->GetVertex(3)))->setW(7);

			(G->InsertE(G->GetVertex(1), G->GetVertex(2)))->setW(6);
			(G->InsertE(G->GetVertex(1), G->GetVertex(3)))->setW(8);

			(G->InsertE(G->GetVertex(2), G->GetVertex(0)))->setW(-1);

			(G->InsertE(G->GetVertex(3), G->GetVertex(1)))->setW(3);
			(G->InsertE(G->GetVertex(3), G->GetVertex(2)))->setW(-4);
			break;
		}
		case 5: {
			cout << "Форма представления (L - список. M - матрица)";
			char F;
			cin >> F;
			G = new Graph <Vertex<string>, Edge<Vertex<string>, string>>(3, false, F);
			(G->InsertE(G->GetVertex(0), G->GetVertex(1)))->setW(-4);
			(G->InsertE(G->GetVertex(1), G->GetVertex(0)))->setW(2);
			(G->InsertE(G->GetVertex(1), G->GetVertex(2)))->setW(1);
			break;
		}
		default: {
			continue;
		};
		}
		system("cls"); 
		break;
	}
	T1 = new Graph <Vertex<string>, Edge<Vertex<string>, string>>::Task1(G);
	T2 = new Graph <Vertex<string>, Edge<Vertex<string>, string>>::Task2(G);
	while (true) {
		system("cls");
		cout << "Vertex\tEdges\tOriented\tForm\tK\n";
		cout << G->V() << "\t" << G->E() << "\t" << G->Directed() << "\t\t" << G->Dense() << "\t" << G->K() << endl<<endl;
		cout << "  1. Показать граф" << endl;
		cout << "  2. Преобразовать к L-форме" << endl;//Доделать
		cout << "  3. Преобразовать к M-форме" << endl;//Доделать
		cout << "  4. Добавить вершину" << endl;
		cout << "  5. Удалить вершину" << endl;
		cout << "  6. Вставить ребро" << endl;
		cout << "  7. Удалить ребро" << endl;
		cout << "  8. Показать вершину" << endl;
		cout << "  9. Изменить вершину" << endl;
		cout << " 10. Показать ребро" << endl;
		cout << " 11. Изменить ребро" << endl;

		cout << " 12. Итератор вершин" << endl;
		cout << " 13. Итератор ребер" << endl;
		cout << " 14. Кратчайшие пути между всеми парами вершин" << endl;
		cout << " 15. Приведение отрицательных весовых функций" << endl;
		cout << "  0. Выход" << endl;
		cout << endl << "-> ";
		cin >> menu;
		switch (menu) {
		case 1: {
			G->print();
			break;
		}
		case 2: {
			
			break;
		}
		case 3: {
			
			break;
		}
		case 4: {
			auto v = G->InsertV();
			string* data = new string;
			cout << "Data: ";
			cin >> *data;
			v->setData(data);
			break;
		}
		case 5: {
			cout << "ID: ";
			int n;
			cin >> n;
			auto v = G->GetVertex(n);
			if (!G->DeleteV(v))
				cout << "Can't find this vertex\n";
			system("pause");
			break;
		}
		case 6: {
			cout << "From: ";
			int v1, v2, w;
			cin >> v1;
			cout << "To: ";
			cin >> v2;
			cout << "W: ";
			cin >> w;
			auto e = G->InsertE(G->GetVertex(v1), G->GetVertex(v2));
			if (e != nullptr) {
				e->setW(w);
				cout << "Success\n";
			}
			else
				cout << "Possible Errors: \n1)Already exist 2)Loop 3)Can't find received vertices\n";
			system("pause");
			break;
		}
		case 7: {
			cout << "From: ";
			int v1, v2;
			cin >> v1;
			cout << "To: ";
			cin >> v2;
			if (G->DeleteE(G->GetVertex(v1), G->GetVertex(v2)))
				cout << "Success\n";
			else
				cout << "Possible Errors: \n1)Already exist 2)Loop 3)Can't find received vertices\n";
			system("pause");
			break;
		}
		case 8: {
			cout << "ID: ";
			int id;
			cin >> id;
			auto v = G->GetVertex(id);
			if (v != nullptr)
				v->print();
			else
				cout << "Error, can't find\n";
			system("pause");
			break;
		}
		case 9: {
			cout << "ID: ";
			int id;
			cin >> id;
			auto v = G->GetVertex(id);
			if (v != nullptr) {
				string* data = new string;
				cout << "Data: ";
				cin >> *data;
				v->setData(data);
			}
			else
				cout << "Error, can't find\n";
			system("pause");
			break;
		}
		case 10: {
			cout << "From: ";
			int v1, v2;
			cin >> v1;
			cout << "To: ";
			cin >> v2;
			auto e = G->GetEdge(G->GetVertex(v1), G->GetVertex(v2));
			if (e != nullptr) {
				e->print();
			}
			else
				cout << "Error, can't find\n";
			system("pause");
			break;
		}
		case 11: {
			cout << "From: ";
			int v1, v2, w;
			cin >> v1;
			cout << "To: ";
			cin >> v2;
			auto e = G->GetEdge(G->GetVertex(v1), G->GetVertex(v2));
			if (e != nullptr) {
				cout << "W: ";
				cin >> w;
				e->setW(w);
			}
			else
				cout << "Error, can't find\n";
			system("pause");
			break;
		}
		case 12: {
			system("cls");
			auto it = G->GetVertexIterator();
			for (int count = 0; count < G->V(); count++) {
				cout << count + 1 << "/" << G->V() << endl;
				(*it)->print();
				system("pause");
				system("cls");
				++it;
			}	
			break;
		}
		case 13: {
			system("cls");
			cout << "Enter Vertex ID (or -1): ";
			int id;
			cin >> id;
			auto v = G->GetVertex(id);
			system("cls");
			if (v == nullptr) {
				auto it = G->GetEdgeIterator();
				for (int count = 0; count < G->E(); count++) {
					cout << count + 1 << "/" << G->E() << endl;
					(*it)->print();
					system("pause");
					system("cls");
					++it;
				}
			}
			else {
				auto it = G->GetEdgeIterator(v);
				int count = it.count();
				for (int i = 0; i < count;i++) {
					cout << i + 1 << "/" << count<<endl;
					(*it)->print();
					system("pause");
					system("cls");
					++it;
				}
			}
			break;
		}
		case 14: {
			system("cls");
			cout << "Restart ? (y/n)\n->";
			char c;
			cin >> c;
			if (c == 'y') 
				T1->restart();
			T1->Result();
			cout << "\nWay showed in reverse order !!!" << endl<< endl;
			system("pause");
			break;
		}
		case 15: {
			system("cls");
			cout << "Restart ? (y/n)\n->";
			char c;
			cin >> c;
			if (c == 'y')
				T2->restart();
			T2->print();
			system("pause");
			break;
		}
		case 0: {
			delete G;
			delete T1;
			delete T2;
			return 0;
		}
		}
	}
	delete G;
	delete T1;
	delete T2;
	return 0;
}

