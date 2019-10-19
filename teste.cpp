#include <iostream>
#include <string>
#include <algorithm>
#include "classes.h"

using namespace std;

struct papel
{
	int papelaria = 10;
	int* papelaria1 = &papelaria;
};

inline int vezes10(int vezes){
	return vezes*10;
}

void mostra(string a){
	cout << a << "\n";
	a.replace(0, 8, "teste aaaaaaa");
	cout << a << "\n";
	string p = a.substr(0, 8);
	cout << p << "\n";

}

int main(){

	char c;
	LAB *v1 = new LAB(10);
	laboratorios *v2 = new laboratorios();

	struct papel papelada;
	papelada.papelaria = 1;
	cout << papelada.papelaria << "\n";
	*papelada.papelaria1 = 2;
	cout << *papelada.papelaria1 << "\n";

	struct papel* papelada1;
	papelada1->papelaria = 3;
	cout << papelada1->papelaria << "\n";
	//*papelada1->papelaria1 = 4;
	//cout << *papelada1->papelaria1 << "\n"; //Não deu certo, tentar arrumar depois.

	enum{
		a1, b1, c1 = 100, d1
	};

	int x;
	int* p = &x;

	string a = "testando está função";
	char txt[] = "alo";

	cout << txt[1] << "\n";
	
	mostra (a);
	cout << a1 << "\t" << b1 << "\t" << c1 << "\t" << d1 << "\n";
	cin >> x;
	cout << "x = "  << x << "\n";

	cout << vezes10(x) << "\n";

	*p = 10;

	cout << *p << "\n";

	cout << "O LAB possui " << v1->membros << " membros, sendo que possui " << v1->getlocais() << " local (s)" << endl;
	cout << "O BRASIL possui " << v2->membros << " membros, sendo que possui " << v2->getlocais() << " local (s)" << endl;

	v2->membros = 1000;
	v2->setlocais(9);

	cout << "O EUA possui " << v2->membros << " membros, sendo que possui " << v2->getlocais() << " local (s)" << endl;

std::string data = "This is a sample string.";
 
// convert string to upper case
std::for_each(data.begin(), data.end(), [](char & c){
	c = ::toupper(c);
});

	cout << data << endl;
	
	return 0;
}