#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

map <string, int> table_symbol;
map <string, int>::iterator it1;
map <string, int>::iterator it2;

void find_data(vector <string> s){
	int i = 0;

	while(i < s.size()){
    	if (s[i] == "1" || s[i] == "2" || s[i] == "3" || s[i] == "4"
    		|| s[i] == "10" || s[i] == "11" || s[i] == "12" || s[i] == "13"){

    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 == table_symbol.end()){
    			table_symbol.insert({s[i], 0});
    		}

    		i++;

    	}else if (s[i] == "9"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 == table_symbol.end()){
    			table_symbol.insert({s[i], 0});
    		}

    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 == table_symbol.end()){
    			table_symbol.insert({s[i], 0});
    		}

    		i++;

    	}else if (s[i] == "14"){
    		i++;
    		break;

    	}else{
    		i = i+2;
    	}
    }

    while(i < s.size()){
    	if(s[i] != "00"){
    		it1 = table_symbol.find(to_string(i));

    		if(it1 == table_symbol.end()){
    			table_symbol.insert({to_string(i), stoi(s[i])});
    		}else{
    			it1->second = stoi(s[i]);
    		}
    	}
    	i++;
    }
}

void execution(vector <string> s){
	int i = 0, acc = 0, x;

	while(i < s.size()){
    	if(s[i] == "1"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 != table_symbol.end()){
    			acc += it1->second;
    		}
    		i++;
            cout << "ACC = " << acc << endl;

    	}else if(s[i] == "2"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 != table_symbol.end()){
    			acc -= it1->second;
    		}
    		i++;
            cout << "ACC = " << acc << endl;

    	}else if(s[i] == "3"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 != table_symbol.end()){
    			acc *= it1->second;
    		}
    		i++;
            cout << "ACC = " << acc << endl;

    	}else if(s[i] == "4"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 != table_symbol.end()){
    			acc /= it1->second;
    		}
    		i++;
            cout << "ACC = " << acc << endl;

    	}else if(s[i] == "5"){
    		i = stoi(s[i+1]);
    		i = i+2;

    	}else if(s[i] == "6"){
    		if(acc < 0){
    			i = stoi(s[i+1]);
    		}else{
    			i = i + 2;
    		}

    	}else if(s[i] == "7"){
    		if(acc > 0){
    			i = stoi(s[i+1]);
    		}else{
    			i = i + 2;
    		}

    	}else if(s[i] == "8"){
    		if(acc == 0){
    			i = stoi(s[i+1]);
    		}else{
    			i = i + 2;
    		}

    	}else if(s[i] == "9"){
    		i++;
    		it1 = table_symbol.find(s[i]);
    		it2 = table_symbol.find(s[i+1]);

    		if(it1 != table_symbol.end() && it2 != table_symbol.end()){
    			it2->second = it1->second;
    		}
    		i = i + 2;
            cout << "End = " << it2->first << "\t" << "Valor = " << it2->second << endl;

    	}else if(s[i] == "10"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 != table_symbol.end()){
    			acc = it1->second;
    		}
    		i++;
            cout << "ACC = " << acc << endl;

    	}else if(s[i] == "11"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 != table_symbol.end()){
    			it1->second = acc;
    		}
    		i++;
            cout << "End = " << it1->first << "\t" << "Valor = " << it1->second << endl;

    	}else if(s[i] == "12"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		cout << "Favor, inserir um valor numérico: ";
    		if(it1 != table_symbol.end()){
    			cin >> it1->second;
    		}else{
    			cin >> x;
    			table_symbol.insert({s[i], x});
    		}
            it1 = table_symbol.find(s[i]);
    		i++;
            cout << "End = " << it1->first << "\t" << "Valor = " << it1->second << endl;

    	}else if(s[i] == "13"){
    		i++;
    		it1 = table_symbol.find(s[i]);

    		if(it1 != table_symbol.end()){
    			cout  << "O valor de saı́da é:" << it1->second << endl;;
    		}
    		i++;

    	}else if (s[i] == "14"){
    		break;
    	}
    }
}

void code_execution(ifstream &file){
	string linha, word;
	vector <string> s;
    int i;

	getline(file, linha);

    if (!linha.empty()){
        for (i = 0; i <= linha.size(); i++) {
            if (linha[i] == ' ' || i == linha.size()){
                    if(!word.empty()) s.push_back(word);
                    word = "";

            }else{
                if(linha[i] != ' ') word = word + linha[i];
            }
        }
    }else{
    	cout << "O arquivo está vazio!" << endl;
    }

    find_data(s);
    execution(s);
}