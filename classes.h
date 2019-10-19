#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

class laboratorios{
public:
	int membros = 400;
	int getlocais();
	void conta_membros();
	void setlocais(int o);
private:
	int locais = 6;
};

int laboratorios::getlocais(){
	return locais;	
}

void laboratorios::setlocais(int o){
	locais = o;
}

void laboratorios::conta_membros(){
	this->membros = 10;
}

class LAB:public laboratorios{
public:
	LAB(int k);
};

LAB::LAB(int k){
	membros = k;
	setlocais(1);
}

#endif
