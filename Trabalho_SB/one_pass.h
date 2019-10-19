#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <ctype.h>

using namespace std;

map <string, int> section{
	{"DATA", -1},
	{"TEXT", -1}
};
map <string, int>:: iterator sec;
map <string, int>:: iterator sec1;

map <string, map<string, int>> instruction{
{"ADD", {{"1", 2}}},
{"SUB", {{"2", 2}}},
{"MULT",{{"3", 2}}},
{"DIV", {{"4", 2}}},
{"JMP", {{"5", 2}}},
{"JMPN",{{"6", 2}}},
{"JMPP",{{"7", 2}}},
{"JMPZ",{{"8", 2}}},
{"COPY",{{"9", 3}}},
{"LOAD",{{"10", 2}}},
{"STORE",{{"11", 2}}},
{"INPUT",{{"12", 2}}},
{"OUTPUT",{{"13", 2}}},
{"STOP", {{"14", 1}}}
};

map <string, string> table_symbol;

map <string, map<string, int>>:: iterator it;
map <string, string>:: iterator it1;


void check_line(ofstream &out_obj, vector<string> s, int n_linha, int* end){
	it = instruction.find(s[0]);
	int i, j;
	string aux;

	if(it != instruction.end()){
		out_obj << (it->second.begin())->first << " ";

		for (i = 1; i < s.size(); i++){
			for (j = 0; j < s[i].size(); j++){
				if(ispunct(s[i][j]) && s[i][j] != '_' && s[i][j] != '+'){
						erro(n_linha, "léxico");
						break;
					}
			}
			if (i!= 0) out_obj << s[i] << " ";
		}

		*end += it->second.begin()->second;
		if(s.size() != it->second.begin()->second) erro(n_linha, "sintático");

	}else if(s[0] == "SECTION"){

		if(s[1] != "DATA" && s[1] != "TEXT"){
			erro(n_linha, "sintático");

		}

		if(s[1] == "DATA"){
			sec = section.find(s[1]);

			if(sec != section.end()){
				sec->second = n_linha;
			}
		}else if(s[1] == "TEXT"){
			sec = section.find(s[1]);

			if(sec != section.end()){
				sec->second = n_linha;
			}
		}

	}else if(s[0].find(':') && s[0] != "SECTION"){
		for(i = 0; i < s[0].size()-1; i++) aux += s[0][i];
		it1 = table_symbol.find(aux);

		if(it1 != table_symbol.end()){
			erro(n_linha, "semântico");
			it1->second = to_string(*end);
		}

		if(s[1] == "CONST"){
			out_obj << s[2] << " ";
			table_symbol.insert({aux, to_string(*end)});
			*end += 1;
		
		}else if(s[1] == "SPACE"){
			if(s.size() == 2){
				out_obj << "00" << " ";
				table_symbol.insert({aux, to_string(*end)});
				*end += 1;
			
			}else{
				out_obj << "00" << " ";
				table_symbol.insert({aux, to_string(*end)});
				*end += 1;
				for(i = 1; i < stoi(s[2]); i++){
					out_obj << "00" << " ";
					table_symbol.insert({aux + '+' + to_string(i), to_string(*end)});
					*end += 1;
				}
			}
		
		}else{
			table_symbol.insert({aux, to_string(*end)});
			if(s.size() != 1){
				s.erase(s.begin());
				n_linha += 1;
				check_line(out_obj, s, n_linha, end);
			}
		}
	}
}

void obj(vector <string> s, string name_obj, int n_linha, int* end){
	ofstream out_obj;

    if(file_aux == 0){
        out_obj.open(name_obj);
        out_obj << "";
        file_aux++;
    }else{
        out_obj.open(name_obj, ios::app);
    }

    check_line(out_obj, s, n_linha, end);

    out_obj.close();
}

void generate_obj(ifstream &file, string name_obj, int* end, int n_linha){
	string linha, word;
    vector <string> s;

    while(getline(file, linha)){
        s.clear();

        if (!linha.empty()){
            for (int i = 0; i <= linha.size(); i++) {
                if (linha[i] == ' ' || linha[i] == ',' || linha[i] == '\t' || i == linha.size()){
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

        obj(s, name_obj, n_linha, end);
        n_linha++;
	}
}

void replace_rotules(string src, int n_linha){
	string obj_code, linha, word;
	vector <string> s;

	fstream file;
	file.open(src, ios::in);

	if(file.is_open()){
		getline(file, linha);
		file.close();

		if (!linha.empty()){
            for (int i = 0; i <= linha.size(); i++) {
                if (linha[i] == ' ' || i == linha.size()){
                    if(!word.empty()) s.push_back(word);
                    word = "";
                }else{
                	word += linha[i];
                }
            }
		}
	}

	file.open(src, ios::out);

	for(int i = 0; i < s.size(); i++){
		it1 = table_symbol.find(s[i]);
		if(it1 != table_symbol.end()){
			s[i] = it1->second;
		}

		if (i < s.size() -1){
			it1 = table_symbol.find(s[i+1]);

			if(s[i] == "4" && it1 != table_symbol.end() && it1->second == "0"){
				erro(n_linha, "semântico");
			
			}else if((s[i] == "5" || s[i] == "6" || s[i] == "7" || s[i] == "8") && it1 == table_symbol.end()){
				erro(n_linha, "semântico");

			}else if((s[i] == "5" || s[i] == "6" || s[i] == "7" || s[i] == "8") && it1 != table_symbol.end()){
				sec1 = sec++;
				if(sec->second > sec1->second){
					if(n_linha < sec->second){
						erro(sec->second, "semântico");
					}
				}else if(sec->second < sec1->second){
					if(n_linha > sec1->second+1){
						erro(sec->second, "semântico");
					}
				}
			}
		}
		
		file << s[i] << " ";
	}
}

void one_pass(string src){
	string name_pre = "", name_obj = "";
    int i = 0, end = 0, n_linha = 0;
    
    while(src[i] != '.'){
        name_obj = name_obj + src[i];
        i++;
    }

    name_pre = name_obj + ".pre";
    name_obj = name_obj + ".obj";

    ifstream file;
    file.open (name_pre);

    if (file.is_open()){
        generate_obj(file, name_obj, &end, n_linha);
        file.close();

    } else {
        cout << "Não foi possível abrir o arquivo \".pre\"." << endl;
    }

    replace_rotules(name_obj, n_linha);

 	  for(sec = section.begin(); sec != section.end(); sec++){
    	if(sec->second == -1){
    		erro(sec->second, "semântico");
    	}
    }
}

