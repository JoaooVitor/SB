#include <iostream>
#include <fstream>
#include "code_analisys.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "É necessário especificar: <arquivo de entrada>" << endl;
        return EXIT_FAILURE;
	}

    string src(argv[1]);
    const int asmLen = 4;

    if (src.compare(src.length() - asmLen, asmLen, ".obj")) {
        cerr << "Arquivo de entrada inválido." << endl;
        exit(EXIT_FAILURE);
    }

    ifstream file;
    file.open (src);

    if (file.is_open()){
        code_execution(file);

    } else {
        cout << "Não foi possível abrir o arquivo \".obj\"." << endl;
    }

    return EXIT_SUCCESS;
}