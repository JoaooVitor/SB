#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "error.h"

using namespace std;

namespace table{
    map<string, string> equal;
    map<string, string>::iterator itequal;
}

int file_aux = 0;

void output_pre(string token, string src, int aux){
    string name = "";
    int i = 0;
    
    while(src[i] != '.'){
        name = name + src[i];
        i++;
    }

    name = name + ".pre";

    ofstream out_pre;
    

    if(file_aux == 0){
        out_pre.open(name);
        out_pre << "";
        file_aux++;
    }else{
        out_pre.open(name, ios::app);
    }

    if(token == "/n"){
        out_pre << endl;
    }else if(aux == 0){
        out_pre << token << " ";
    }else{
        out_pre << token;
    }

    out_pre.close();
}

void line_pre_process(vector <string> token, string src, int n_linha, ifstream &file, string linha){
    int i, j, aux, space = 0;

    for(i = 0; i < token.size(); i++){
        if ((i != 0) && (token[i-1] != "IF")){
            table::itequal = table::equal.find(token[i] + ':');
            if(table::itequal != table::equal.end()){
                token[i] = table::itequal->second;
            }
        }

        if((token[i][0] == '0' && token[i][1] == 'X') || (token[i][1] == '0' && token[i][2] == 'X')){
            token[i] = to_string(stol (token[i],nullptr,16));
        }
    }

    if(token[0][token[0].size()-1] == ':'){
        if(token[1] != "EQU"){
            for(i = 0; i < token.size(); i++){
                if(token[i] == "+") space++;

                    output_pre(token[i], src, space);
            }
            output_pre("/n", src, 0);
        }else{
            table::equal.insert(pair<string, string>(token[0], token[2]));
        }
    }

    else if(token[0] == "IF"){
        table::itequal = table::equal.find(token[1]+":");
        if(table::itequal == table::equal.end()){
            erro(n_linha, "semântico");
        }else{
            if(stoi(table::itequal->second) != 1){
                getline(file, linha);
            }
        }
    }

    else{
        space = 0;
        for(i = 0; i < token.size()-1; i++){
            if(token[i+1] == "+") space++;
            output_pre(token[i], src, space);
        }
        output_pre(token[token.size()-1], src, space);
        output_pre("/n", src, 0);
    }
}

void read_file(ifstream &file, string src){
    string linha, word;
    int n_linha = 0;
    vector <string> s;

    while(getline(file >> ws, linha)){
        s.clear();

        if (!linha.empty()){
            for (int i = 0; i <= linha.size(); i++) {
                if ((linha[i] == ' ' && linha[i-1] != ',') || linha[i] == '\t' || i == linha.size()){
                    if(!word.empty()) s.push_back(word);
                    word = "";

                }else if(linha[i] == ';'){
                    break;

                }else{
                    if(linha[i] >= 'a' && linha[i] <= 'z') linha[i] = toupper(linha[i]);
                    if(linha[i] != ' ') word = word + linha[i];
                }
            }
        }


        if (!linha.empty()) line_pre_process(s, src, n_linha, file, linha);
        n_linha++;
    }
}