template <typename T, T NADA = 0>
class Stack {
private:
    struct Nodo{
        T elem;
        Nodo *ant;
 
        Nodo(T elem = NADA, Nodo* ant = nullptr) : elem(elem), ant(ant) {}
    };
    short size;
    Nodo * lastIn;
 
public:
    Stack() : lastIn(nullptr), size(0) {}
 
    void push(T elem) {
        Nodo *nuevo =  new Nodo(elem, lastIn);
        if (lastIn != nullptr) {
            nuevo->ant = lastIn;
        }
        lastIn = nuevo;
        size++;
    };
    void pop() {
        if (lastIn != nullptr) {
            Nodo *aux = lastIn;
            lastIn = lastIn->ant;
            size--;
            delete aux;
        };
        if (size==0)
            lastIn = nullptr;
    };
    T top() {
        if (lastIn != nullptr)
            return lastIn->elem;
        return NADA;
    };
    bool empty() {
        return size == 0;
    };
 
};
 
 
 
source---
#include <iostream>
#include "Header.h"
 
using namespace std;
 
void main() {
    Stack <short> pila;
    for (short i = 0; i < 20; i++)
        pila.push(i);
    for (short i = 0; i < 20; i++){
        cout << pila.top()<<endl;
        pila.pop();
    }
    getchar();
    return;
}
