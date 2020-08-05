#include <iostream>
#include "graph.h"
using namespace std;


int main() {
	Graph <Vertex<string>, Edge<Vertex<string>, string>>*G;
	Graph <Vertex<string>, Edge<Vertex<string>, string>>::Task1* T1;
	Graph <Vertex<string>, Edge<Vertex<string>, string>>::Task2* T2;

	setlocale(LC_ALL, "rus");
	int menu;

	cout << "1. ������� ������ L-���� � ������� ������ ������ � �����" << endl;
	cout << "2. ������� ���� � V ���������, ��� �����, ���� D, ����� ������������� F" << endl;
	cout << "3. ������� ���� � V ���������, � E ���������� �������, ���� D , ����� F" << endl;
	cout << "0. �����" << endl << endl;
	cout << "4. �������� ���� ��� �������������� �����" << endl;
	cout << "5. � ������������� ������" << endl;
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
			cout << "���������� ������: ";
			cin >> v;
			cout << "��������������� ���� (0 - ���, 1 - ��): ";
			cin >> directed;
			cout << "����� ����� (L - ������, M - �������): ";
			cin >> F;
			G = new Graph <Vertex<string>, Edge<Vertex<string>, string>>(v, directed, F);
			break;
		};
		case 3: {
			int v, e, directed; char F;
			cout << "���������� ������: ";
			cin >> v;
			cout << "���������� �����: ";
			cin >> e;
			cout << "��������������� ���� (0 - ���, 1 - ��): ";
			cin >> directed;
			cout << "����� ����� (L - ������, M - �������): ";
			cin >> F;
			G = new Graph <Vertex<string>, Edge<Vertex<string>, string>>(v, e, directed, F);
			break;
		};
		case 0: {
			return 0;
		};
		case 4: {
			cout << "����� ������������� (L - ������. M - �������)";
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
			cout << "����� ������������� (L - ������. M - �������)";
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
		cout << "  1. �������� ����" << endl;
		cout << "  2. ������������� � L-�����" << endl;//��������
		cout << "  3. ������������� � M-�����" << endl;//��������
		cout << "  4. �������� �������" << endl;
		cout << "  5. ������� �������" << endl;
		cout << "  6. �������� �����" << endl;
		cout << "  7. ������� �����" << endl;
		cout << "  8. �������� �������" << endl;
		cout << "  9. �������� �������" << endl;
		cout << " 10. �������� �����" << endl;
		cout << " 11. �������� �����" << endl;

		cout << " 12. �������� ������" << endl;
		cout << " 13. �������� �����" << endl;
		cout << " 14. ���������� ���� ����� ����� ������ ������" << endl;
		cout << " 15. ���������� ������������� ������� �������" << endl;
		cout << "  0. �����" << endl;
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

