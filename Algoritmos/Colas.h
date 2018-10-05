template <typename T, T NADA = 0>
class Queue {
private:
	struct Nodo{
		T elem;
		Nodo *next;

		Nodo(T elem = NADA, Nodo* next = nullptr) : elem(elem), next(next) {}
	};
	short size;
	Nodo * first;
	Nodo * last;

public:
	Queue() : first(nullptr), last(nullptr),size(0) {}

	void push(T elem) {
		Nodo *nuevo =  new Nodo(elem, nullptr);
		if (last != nullptr) 
			last->next = nuevo;
		last = nuevo;
		if (first == nullptr) {
			first = last;
		}
		size++;
	};
	void pop() {
		if (first != nullptr) {
			Nodo *aux = first;
			first = first->next;
			size--;
			delete aux;
		};
		if (size==0)
			first = last = nullptr;
	};
	T front() {
		if (first != nullptr)
			return first->elem;
		return NADA;
	};

	T back(){
		if (last != nullptr)
			return last->elem;
		return NADA;
	};

	bool empty() {
		return size == 0;
	};
};
