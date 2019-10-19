#include <iostream>
#include <fstream>
#include "processment.h"
#include "one_pass.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "É necessário especificar: <arquivo de entrada>" << endl;
        return EXIT_FAILURE;
	}

    string src(argv[1]);
    const int asmLen = 4;

    if (src.compare(src.length() - asmLen, asmLen, ".asm")) {
        cerr << "Arquivo de entrada inválido." << endl;
        exit(EXIT_FAILURE);
    }

    ifstream file;
    file.open (src);

    if (file.is_open()){
        read_file(file, src);
        file.close();
        file_aux = 0;
        one_pass(src);

    } else {
        cout << "Não foi possível abrir o arquivo \".asm\"." << endl;
    }

    return EXIT_SUCCESS;
}