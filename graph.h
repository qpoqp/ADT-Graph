#include <string>
#include <vector>
#include <list>
#include <set>//for Task1
#include <ctime>
using namespace std;
template <typename Tdata>class Vertex{
    Tdata* data;
	unsigned int index;

	//For Task1===============
	int source = -1;//Параметры ниже допустимы только для конкретной source 
	Vertex<Tdata>* prev = nullptr;//Предыдущая вершина кратчайшего пути
	int weight = -1;//кол-во ребер 
	//========================

	//For Task2===============
	int h = 0;

public:
	Vertex(int index = -1) {
		data = nullptr;
		this->index = index;
	}
    Vertex(string name, int index, Tdata* data){
		this->index = index;
		this->data = data;
    }
	Tdata* getData() {
		return this->data;
	}
	void setData(Tdata* data) {
		this->data = data;
	}
	int getIndex() {
		return index;
	}
	~Vertex() {
		cout << "~Vertex:" << this->index<<endl;
		delete data;
	}
	void print() {
		cout << "Index:\t" <<this->index << endl;
		cout << "Data:\t" << this->data << endl;
		cout << "H:\t" << this->h << endl;
	}
	//========================
	void setTask1(int source, int weight, Vertex<Tdata>* prev) {
		this->source = source;
		this->weight = weight;
		this->prev = prev;
	}
	int getW() {
		return this->weight;
	}
	int getS() {
		return source;
	}
	Vertex<Tdata>* getPrev() {
		return this->prev;
	}
	int getH() {
		return h;
	}
	void setH(int h) {
		this->h = h;
	}
};
template <typename Tvertex, typename Tdata> class Edge {
	Tvertex* v1;
	Tvertex* v2;
	int weight;
	Tdata* data;
public:
	Edge(Tvertex* v1, Tvertex* v2) {
		this->v1 = v1;
		this->v2 = v2;
		weight = 1;
	}
	Edge(Tvertex* v1, Tvertex* v2, int weight) {
		this->v1 = v1;
		this->v2 = v2;
		this->weight = weight;
	}
	Edge(Tvertex* v1, Tvertex* v2, int weight, Tdata* data) {
		this->v1 = v1;
		this->v2 = v2;
		this->weight = weight;
		this->data = data;
	}
	~Edge() {
		cout << "~Edge:\t" << v1->getIndex() << "\t" << v2->getIndex()<<"\n";
		delete data;
	}
	Tvertex* V1() {
		return v1;
	}
	Tvertex* V2() {
		return v2;
	}
	int getW() {
		return weight;
	}
	void setW(int W) {
		this->weight = W;
	}
	Tdata* getData() {
		return this->data;
	}
	void setData(Tdata * data) {
		this->data = data;
	}
	void print() {
		cout << "======<EDGE>======" << endl;
		v1->print();
		cout << "------------------" << endl;
		v2->print();
		cout << "------------------" << endl;
		cout << "Weight:\t" << this->weight << endl;
		cout << "Data:\t" << this->data << endl;
		cout << "======</EDGE>=====" << endl<<endl;
	}
};
template <typename Tedge> class graph_type {
public:
	virtual int DeleteV(int v1, int v2ID) = 0;
	virtual void InsertE(Tedge* edge, int v1, int v2ID) = 0;
	virtual void InsertV() = 0;
	virtual void DeleteE(int v1, int v2ID) = 0;
	virtual Tedge* hasEdge(int v1, int v2ID) = 0;
	virtual ~graph_type() {};

	virtual vector<list<Tedge*>*>* getList() = 0;
	virtual vector<vector<Tedge*>>* getMatrix() = 0;

};
template<typename Tedge> class Graph_List : public graph_type<Tedge> {
	vector<list<Tedge*>*>LIST;
	int position;
public:
	Graph_List(int VertexCount) {
		while (LIST.size() != VertexCount) {
			list<Tedge*>* node = new list<Tedge*>();
			LIST.push_back(node);
		}
	}
	void InsertE(Tedge* edge, int position, int v2) override {
		LIST[position]->push_back(edge);
	}
	Tedge* hasEdge(int position, int ID) override {
		for (auto i = LIST[position]->begin(); i != LIST[position]->end(); i++)
			if ((*i)->V2()->getIndex() == ID)
				return *i;
		return nullptr;
	}
	int DeleteV(int position, int ID) override {//возвращает кол-во удаленных ребер
		int count = 0;
		for (auto j : LIST) {
			auto i = j->begin();
			while (i != j->end()) {
				if ((*i)->V2()->getIndex() == ID || (*i)->V1()->getIndex() == ID) {//удаляем все ребра в которых упоминалась удаляемая вершина
					delete* i; // Удаляем ребро
					j->erase(i++);//Удаляем конкретный элемент списка
					count++;
				}
				else
					i++;
			}
		}
		LIST.erase(LIST.begin() + position);//удаляем позицию вершины в LIST
		return count;
	}
	void InsertV() override {
		list<Tedge*>* node = new list<Tedge*>();
		LIST.push_back(node);
	}
	void clear() {
		for (auto i : LIST) {
			while (!i->empty())
				delete i->front(), i->pop_front();
		}
	}
	void DeleteE(int position, int ID) override {
		auto i = LIST[position]->begin();
		while (i != LIST[position]->end()) {
			if ((*i)->V2()->getIndex() == ID) {
				delete* i;
				LIST[position]->erase(i);
				break;
			}
			i++;

		}
	}
	~Graph_List() override {
		this->clear();
		LIST.clear();
	}
	
	vector<list<Tedge*>*>* getList() override {
		return &this->LIST;
	}
	vector<vector<Tedge*>>* getMatrix() override {
		return nullptr;
	}
};
template<typename Tedge> class Graph_Matrix : public graph_type<Tedge> {
	vector<vector<Tedge*>> MATRIX;
public:
	Graph_Matrix(int VertexCount) {
		while (MATRIX.size() != VertexCount) {
			MATRIX.push_back(vector<Tedge*>());
			int i = MATRIX.size() - 1;
			while (MATRIX[i].size() != VertexCount) {
				MATRIX[i].push_back(nullptr);
			}
		}
	}
	void InsertE(Tedge* edge, int v1, int v2) override {
		MATRIX[v1][v2] = edge;
	}
	Tedge* hasEdge(int v1, int v2) override {
		return MATRIX[v1][v2];
	}
	int DeleteV(int v1, int v2 = 0) override {
		int count = 0;
		for (auto i = 0; i < MATRIX.size(); i++) {
			if (v1 != i) {
				delete MATRIX[v1][i];//удаляем ребра по столбцу
				delete MATRIX[i][v1];//удаляем ребра по строке
				MATRIX[i].erase(MATRIX[i].begin() + v1);//Удаляем вершину из строк
				count++;
			}
		}
		MATRIX[v1].clear();
		MATRIX.erase(MATRIX.begin() + v1);//удаляем столбец
		return count;
	}
	void InsertV() override {
		MATRIX.push_back(vector<Tedge*>());
		for (int i = 0; i < MATRIX.size(); i++) {
			MATRIX[i].push_back(nullptr);
		}
	}
	void DeleteE(int v1, int v2) override {
		delete MATRIX[v1][v2];
	}
	~Graph_Matrix() override {
		int size = MATRIX.size();
		for (int i = 0; i < size; i++)
			DeleteV(0);
	}

	vector<vector<Tedge*>>* getMatrix() {
		return &this->MATRIX;
	}
	vector<list<Tedge*>*>* getList() override {
		return nullptr;
	}
};
template <typename Tvertex, typename Tedge> class Graph
{
	graph_type<Tedge>* body;
	vector<Tvertex*> VERTEX;
	bool directed;
	char F;
	int edgeCount;
	int vertexCount;
	int findVertexPosition(int left, int right, int ID) {
		if (left == right)
			return -1;
		int middle = left + (right - left) / 2;
		if (VERTEX[middle]->getIndex() == ID)
			return middle;
		if (VERTEX[middle]->getIndex() > ID)
			return findVertexPosition(left, middle, ID);
		else
			return findVertexPosition(middle + 1, right, ID);//+1 т.к middle 100% не подходит
	}
public:
	class EdgeIterator;
	class VertexIterator;
	Graph()
	{
		body = new Graph_List<Tedge>(0);
		this->F = 'L';
		this->edgeCount = 0;
		this->vertexCount = 0;
		this->directed = true;
	}
	Graph(int _v, bool directed, char F) {
		if (F == 'L')
			body = new Graph_List<Tedge>(_v);
		else
			body = new Graph_Matrix<Tedge>(_v);
		this->F = F;
		this->directed = directed;
		for (int i = 0; i < _v; i++) {
			Tvertex* vertexPtr = new Tvertex(vertexCount++);
			VERTEX.push_back(vertexPtr);
		}
	}
	Graph(int _v, int _e, bool directed, char F) {
		if (F == 'L')
			body = new Graph_List<Tedge>(_v);
		else
			body = new Graph_Matrix<Tedge>(_v);
		this->F = F;
		for (int i = 0; i < _v; i++) {
			Tvertex* vertexPtr = new Tvertex(vertexCount++);
			VERTEX.push_back(vertexPtr);
		}
		this->directed = directed;
		if (_e <= 0) return;
		if (directed)
			if (_e > _v * (_v - 1))
				_e = _v * (_v - 1);
			else
				if (_e > (_v * (_v - 1)) / 2)
					_e = (_v * (_v - 1)) / 2;
		srand((unsigned)time(NULL));
		int count = 0;
		int v1, v2;
		while (count < _e) {
			v1 = rand() % _v;
			v2 = rand() % _v;
			if (v1 == v2)
				continue;
			if (body->hasEdge(v1, v2) != nullptr)
			{
				continue;
			}
			Tedge* edgePtr = new Tedge(VERTEX[v1], VERTEX[v2]);
			edgePtr->setW(rand() % 100 + 1);
			body->InsertE(edgePtr, v1, v2);
			count++;
			edgeCount++;
		}
	}
	//Graph(&Graph G){}
	~Graph() {
		delete body;
		for (auto i : VERTEX)
			delete i;
		VERTEX.clear();
	}
	int V() {
		return VERTEX.size();
	}
	int E() {
		return edgeCount;
	}
	bool Directed() {
		return directed;
	}
	char Dense() {
		return F;
	}
	double K() {
		int max = VERTEX.size() * (VERTEX.size() - 1);
		if (!directed) {
			max /= 2;
		}
		if (max == 0) {
			return -1;
		}
		else {
			return (double)edgeCount / (double)max;
		}
	}
	//ToListGraph() преобразует граф к L - графу,
	//ToMatrixGraph() преобразует граф к M - графу,
	Tvertex* InsertV() {
		Tvertex* v = new Tvertex(vertexCount++);
		body->InsertV();
		VERTEX.push_back(v);
		return v;
	}
	bool DeleteV(Tvertex* removable) {
		if (removable != nullptr) {
			int position = findVertexPosition(0, VERTEX.size(), removable->getIndex());
			if (position >= 0) {
				edgeCount = edgeCount - body->DeleteV(position, VERTEX[position]->getIndex());//Возвращает кол-во удаленных ребер
				delete VERTEX[position];
				VERTEX.erase(VERTEX.begin() + position);
				return true;
			}
		}
		return false;
	}
	Tedge* InsertE(Tvertex* v1, Tvertex* v2) {
		if (v1 != nullptr && v2 != nullptr) {
			int _v1 = findVertexPosition(0, VERTEX.size(), v1->getIndex());
			int _v2 = findVertexPosition(0, VERTEX.size(), v2->getIndex());
			if (_v1 < 0 || _v2 < 0 || _v1 == _v2)// Вершины v1 или v2 нет в векторе вершин или петля
				return nullptr;
			if (body->hasEdge(_v1, v2->getIndex()) == nullptr) { // Ребро ранее не добавляли
				Tedge* node = new Tedge(v1, v2);
				body->InsertE(node, _v1, _v2);
				this->edgeCount++;
				return node;
			}
		}
		return nullptr;
	}
	bool DeleteE(Tvertex* v1, Tvertex* v2) {
		if (v1 != nullptr && v2 != nullptr) {
			int position = findVertexPosition(0, VERTEX.size(), v1->getIndex());
			if (position >= 0) {
				body->DeleteE(position, v2->getIndex());
				edgeCount--;
				return true;
			}
		}
		return false;
	}
	Tedge* GetEdge(Tvertex* v1, Tvertex* v2) {
		if (v1 != nullptr && v2 != nullptr) {
			int position = findVertexPosition(0, VERTEX.size(), v1->getIndex());
			if (position >= 0) {
				return body->hasEdge(position, v2->getIndex());
			}
		}
		return nullptr;
	}
	Tvertex* GetVertex(int ID) {
		int position = findVertexPosition(0, VERTEX.size(), ID);
		if (position < 0)
			return nullptr;
		return VERTEX[position];
	}
	//int GetVertexPosition(int ID) {
	//	return findVertexPosition(0, VERTEX.size(), ID);;
	//}
	void print() {
		system("cls");
		cout << "+-------------------------" << endl;
		cout << "| From: | To + weight:\n";
		cout << "+-------------------------"<<endl;
		for (int i = 0; i < this->VERTEX.size(); i++) {
			cout<<"|   " << VERTEX[i]->getIndex() << "\t| ";
			auto it = GetEdgeIterator(i);
			int count = it.count();
			while (count > 0) {
				cout << (*it)->V2()->getIndex() << "("<< (*it)->getW()<<")\t ";
				--count;
				++it;
			}
			cout << "\n";
		}
		system("pause");
	}


	EdgeIterator GetEdgeIterator(){
		return EdgeIterator(this);
	}
	EdgeIterator GetEdgeIterator(Tvertex* v) {
		return EdgeIterator(this, findVertexPosition(0, this->VERTEX.size(), v->getIndex()));
	}
	EdgeIterator GetEdgeIterator(int v) {
		return EdgeIterator(this, v);
	}
	VertexIterator GetVertexIterator() {
		return VertexIterator(this);
	}
	
	
	class EdgeIterator {
		friend class Graph;
		char F;
		typename list<Tedge*>::iterator lIt;
		vector<list<Tedge*>*>* LIST;
		int v1 = -1; int v2;
		vector<vector<Tedge*>>* MATRIX;
	public:
		EdgeIterator(Graph* G, int v = -1) {
			this->F = G->Dense();
			if (this->F == 'L') {
				LIST = G->body->getList();
				if (v < 0) {//Взять самое первое ребро из коллекции
					for (int i = 0; i < LIST->size(); i++) {
						if ((*LIST)[i]->size() > 0) {
							this->lIt = (*LIST)[i]->begin();
							this->v1 = i;
							break;
						}
					}
				}
				else {
					this->lIt = (*LIST)[v]->begin();
					this->v1 = v;
				}

			}
			else {
				MATRIX = G->body->getMatrix();
				v2 = 0;
				if (v < 0) {
					v1 = 0;
					this->operator++();
				}
				else
					v1 = v;
			}
		}
		Tedge* operator*() {
			if (F == 'L')
				return *lIt;
			for (int i = v2; i < MATRIX->size(); i++) {
				if ((*MATRIX)[v1][i] != nullptr) {
					v2 = i;
					return (*MATRIX)[v1][v2];
				}
			}
		}
		bool operator++() {
			if (F == 'L') {
				if (lIt != --(*LIST)[v1]->end()) {
					lIt++;
					return true;
				}
				for (int i = v1 + 1; i < LIST->size(); i++) {
					if ((*LIST)[i]->size() > 0) {
						this->lIt = (*LIST)[i]->begin();
						this->v1 = i;
						return true;
					}
				}
				return false;
			}
			else {
				for (int i = v1; i < MATRIX->size(); i++) {
					for (int j = v2 + 1; j < MATRIX->size(); j++) {
						if ((*MATRIX)[i][j] != nullptr) {
							this->v1 = i;
							this->v2 = j;
							return true;
						}
					}
					this->v2 = -1;
				}
				return false;
			}
		}
		int count() {
			if (F == 'L') {
				if (v1 != -1)
					return (*LIST)[v1]->size();
				return 0;
			}
			int _c = 0;
			for (int i = 0; i < (*MATRIX).size(); i++) {
				if ((*MATRIX)[v1][i] != nullptr)
					_c++;
			}
			return _c;
		}

		//==========For std::set
		bool operator< (const EdgeIterator& it) const {//it -> Итератор находящийся в коллекции
			return this->v1 < it.v1;//Очередь сортируется по номеру вершины :(
		}
	};
	class VertexIterator {
		friend class Graph;
		vector<Tvertex*>* VERTEX;
		typename vector<Tvertex*>::iterator vIt;
		VertexIterator(Graph* G) {
			this->VERTEX = &G->VERTEX;
			vIt = (*this->VERTEX).begin();
		}
	public:
		Tvertex* operator*() {
			return *vIt;
		}
		bool operator++() {
			if (vIt != --(*VERTEX).end()) {
				vIt++;
				return true;
			}
			return false;
		}
	};
	class Task1 {
		Graph<Tvertex, Tedge>* G;
		string out;
	public:
		Task1(Graph<Tvertex, Tedge>* G) {
			this->G = G;
		}
		void restart() {
			set<EdgeIterator>Q;
			out.clear();
			for (int i = 0; i < G->V(); i++) {//Source = i
				G->VERTEX[i]->setTask1(i, 0, nullptr);//Настраиваем source вершину [кем установлено, вес, указатель на предыдущую]
				Q.insert(G->GetEdgeIterator(i));//Кладем в очередь source вершину
				while (!Q.empty()) {//Пока есть вершины для обхода
					EdgeIterator cur = *Q.begin();
					Q.erase(Q.begin());
					int EdgeInCurrentVertex = cur.count();
					while (EdgeInCurrentVertex > 0) {//Пока в текущей вершине есть ребра
						Tvertex* _v1 = (*cur)->V1();
						Tvertex* _v2 = (*cur)->V2();
						if (_v1->getS() == _v2->getS()) {//Если source вершины совпадают
							if (_v1->getW() + 1 < _v2->getW()) {
								_v2->setTask1(i, _v1->getW() + 1, _v1);//Если считать через веса _v1->getW() + (*cur)->getW()
							}
						}
						else {
							_v2->setTask1(i, _v1->getW() + 1, _v1);//Если считать через веса _v1->getW() + (*cur)->getW()
							Q.insert(G->GetEdgeIterator(_v2));//Добавляем вершину в очередь для обхода только если в ней еще не были
						}
						--EdgeInCurrentVertex;
						++cur;
					}
				}
				for (int j = 0; j < G->V(); j++) {
					out += "From: "; out += to_string(i);
					out += "\tTo: "; out += to_string(j);
					out += "\tWeight: ";
					if (G->VERTEX[j]->getS() == i) {
						Tvertex* temp = G->VERTEX[j];
						out += to_string(temp->getW());
						out += "\tWay: ";
						while (temp->getPrev() != nullptr) {
							out += to_string(temp->getIndex());
							out += " ";
							temp = temp->getPrev();
						}
						out += to_string(temp->getIndex());
						out += "\n";
					}
					else {
						out += "inf\n";
					}
				}
				out += "=============================================================\n";
			}
		}
		void Result() {
			cout << out;
		}
		void Set(Graph<Tvertex, Tedge>* G) {
			this->G = G;
			restart();
		}
		~Task1() {
			out.clear();
		}
	};
	class Task2 {
		Graph<Tvertex, Tedge>* G;
		bool isNegativeCycle;
		bool updated;
	public:
		Task2(Graph<Tvertex, Tedge>* G) {
			this->G = G;
			this->isNegativeCycle = true;
			this->updated = false;
		}
		void restart() {
			if (!updated) {
				this->isNegativeCycle = true;//Возможно есть отрицательный цикл
				for (int i = 0; i < G->V(); i++) {//+1, т.к представляем что добавили мнимую S вершину 
					if (isNegativeCycle)
						isNegativeCycle = false;
					else
						break;//Если после предыдущего прохода по всем ребрам не производилась релаксация - выходим из цикла
					auto it = G->GetEdgeIterator();
					int count = G->E();
					while (count != 0) {
						int temp = (*it)->getW() + (*it)->V1()->getH();
						if (temp < (*it)->V2()->getH()) {
							(*it)->V2()->setH(temp);
							isNegativeCycle = true;//Возможно есть отрицательный цикл
						}
						--count;
						++it;
					}
				}
			}
			else {
				cout << "Already updated" << endl;
				cout << "Undo ? (y/n) ";
				char ch;
				cin >> ch;
				if (ch == 'y')
					undo();
				cout << endl;
			}
		}
		void undo() {
			auto it = G->GetEdgeIterator();
			do {
				int hV1 = (*it)->V1()->getH();
				int hV2 = (*it)->V2()->getH();
				int edgeW = (*it)->getW();
				(*it)->setW(edgeW - hV1 + hV2);
			} while (++it);
			this->updated = false;
		}
		void print() {
			cout<< "Negative cycle: " << isNegativeCycle << endl;
			if (!isNegativeCycle) {
				cout << "Print H params ? (y/n) ";
				char s;
				cin >> s;
				if (s == 'y' && G->V() > 0) {
					auto it = G->GetVertexIterator();
					do {
						system("cls");
						(*it)->print();
						system("pause");
					} while (++it);
				}
				if (!updated) {
					cout << "Update edges ? (y/n) ";
					cin >> s;
					if (s == 'y' && G->E() > 0) {
						this->updated = true;
						auto it = G->GetEdgeIterator();
						do {
							int hV1 = (*it)->V1()->getH();
							int hV2 = (*it)->V2()->getH();
							int edgeW = (*it)->getW();
							(*it)->setW(edgeW + hV1 - hV2);
						} while (++it);
					}
				}
			}
		}
	};
};
