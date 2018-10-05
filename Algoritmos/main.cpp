//Leer y escribir un archivo.

#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

int triangularIt(short n){
    int sum = 0;
    for (short i=1; i<n; i++){
        sum+=i;
        printf("%d ", sum);
    }
    cout <<endl;
    return 0;
}

int fibonnaciInt(short n){
    short n1=0, n2=1, n3 = 0;
    cout << n2 << " ";
    for(short i=1; i<n; i++){
        n3 = n1 + n2;
        n1 = n2;
        n2 = n3;
        cout << n3 << " ";
    }
    return 1;
}

void filaAterisco(short n){
    if(n == 0)
        return;
    cout << "*";
    return filaAterisco(n-1);
}

void trianguloInver(short n){
    if(n==0)
        return;
    filaAterisco(n);
    cout << endl;
    return trianguloInver(n-1);
}

void trianguloNormal(short n){
    if(n==0)
        return ;
    trianguloNormal(n-1);
    cout << endl;
    return filaAterisco(n);

}

//made by the teacher
void serie(int term, int n, int pos, int digit) {
    if (digit > 0) {
        serie(term, n, pos, digit - 1);
        term = term * 10 + digit;
        if (pos == 1) {
            cout << term << " ";
        } else {
            serie(term, n, pos - 1, n);
        }
    }
}

int factorial(short n){
    if (n==0)
        return 1;
    return n*factorial(n-1);
}

void generarPer(short n, short pn, short i, short pos){
    if(pn%n==0 ){
        return;
    };
    cout << n;
    generarPer(n, pn-1, n+1, pos);
    cout << endl;
    if (pn==0){
        return;
    }
    generarPer(n, pn-1, 1, pos-1);
}


void print(short a){
    cout << a;
}

function<int()> funcion(int& a) {
    auto f = [](int x) {
        for (int i = 2; i < sqrt(x)+1; i++) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    };
    return [&]() {
        for (;;) {
            if (f(++a)) {
                return a;
            }
        }
        return 0;
    };
}

int main() {
    int y = 1;
    auto f = funcion(y);
    for (int i = 0; i < 5; i++) {
        cout << f() << endl;
    }
    return 0;
}
