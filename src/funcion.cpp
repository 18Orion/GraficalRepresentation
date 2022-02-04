#include "funcion.hpp"

funcion::funcion(){}

funcion::~funcion(){}

void funcion::prepare(string funcion){
    string cache;
    vector<string> vectorCache;
    /*Separa la funcion en un vector para su uso más facil*/
    for (int i = 0; i <= funcion.length(); i++) {
        if(isdigit(funcion[i])||funcion[i]=='.'||funcion[i]=='x'){
            if(funcion[i]=='x'){
                if(isdigit(funcion[i-1])){
                    vectorCache.push_back(cache);
                    cache="";
                    vectorCache.push_back("*");
                    hasMult=true;
                }
                vectorCache.push_back("x");
            }else{
                cache+=funcion[i];
            }
        }else if(funcion[i]=='('){             //Ejecuta la función solve para añadir un vector que contenga el paréntesis
            if(isdigit(funcion[i-1])){
                vectorCache.push_back(cache);
                cache="";
                vectorCache.push_back("*");
                hasMult=true;
            }
            i++;
            cache="";
            while(funcion[i]!=')'){
                cache+=funcion[i];
                i++;
            }
            prepare(cache);
            cache="";
            vectorCache.push_back("()");        //Añade un placeholder para que al resolverla nos podamos referir al vector en cuestión
        }else{
            if(cache!="") vectorCache.push_back(cache);
            cache="";
            vectorCache.push_back({funcion[i]});
            if(isMult({funcion[i]})) hasMult=true;
            if(funcion[i]=='^') hasPower=true;

        }
    }
    fnVector.insert(fnVector.begin(), vectorCache);
}

string funcion::returnFunction(){
    string function;
    for (int i = 0, a=1; i < fnVector[0].size(); i++){
        if(fnVector[0][i]=="()"){
            function+="(";
            for (int b = 0; b < fnVector[a].size(); b++) function+=fnVector[a][b];
            function+=")";
            a++;
        }else function+=fnVector[0][i];
    }
    return function;
}

double funcion::solve(double x){
    /*Substituye las variables de la ecuación copiandolas a un nuevo vector que va a
    ser modificado según se va resolviendo la función                               */
    double result=0;
    vector<string> fn;
    for (int i=0 ,a = 1; i < fnVector[0].size(); i++) {
        if(fnVector[0][i]=="x"){
            fn.push_back(to_string(x));
        }else if(fnVector[0][i]=="()"){
            fn.push_back(to_string(solve(x, fnVector[a])));
            a++;
        }else{
            fn.push_back(fnVector[0][i]);
        }
    }
    if(hasPower){
        for (int i = 0; i < fn.size(); i++) {           //Hace las potencias
            if(fn[i]=="^"){
                fn[i-1]=to_string(pow(stod(fn[i-1]), stod(fn[i+1])));
                fn.erase(fn.begin()+i+1);
                fn.erase(fn.begin()+i);
                i--;
            }
        }
    }
    if(hasMult){
        for (int i = 1; i < fn.size(); i++) {           //Hace las multiplicaciones y divisiones
            if(fn[i]=="*"){
                fn[i-1]=to_string(stod(fn[i-1])*stod(fn[i+1]));
                fn.erase(fn.begin()+i+1);
                fn.erase(fn.begin()+i);
                i--;
            }
            if(fn[i]=="/"){
                fn[i-1]=to_string(stod(fn[i-1])/stod(fn[i+1]));
                fn.erase(fn.begin()+i+1);
                fn.erase(fn.begin()+i);
                i--;
            }
        }
    }
    for (int i = 0; i < fn.size(); i++) {           //Hace las sumas y restas
        if(i==0&&!isSum(fn[0])){
            result+=stod(fn[0]);
        }
        if(fn[i]=="+"&&fn[i][0]!='-'){
            result+=stod(fn[i+1]);
        }else if(fn[i]=="-"){
            result-=stod(fn[i+1]);
        }
    }
    return result;
}

double funcion::solve(double x, vector<string> inV){
    double result=0;
    vector<string> fn;
    /*Substituye las variables de la ecuación copiandolas a un nuevo vector que va a
    ser modificado según se va resolviendo la función                               */
    for (int i = 0; i < inV.size(); i++) {
        if(inV[i]=="x"){
            fn.push_back(to_string(x));
        }else{
            fn.push_back(inV[i]);
        }
    }
    if(hasPower){
        for (int i = 0; i < fn.size(); i++) {           //Hace las potencias
            if(fn[i]=="^"){
                fn[i-1]=to_string(pow(stod(fn[i-1]), stod(fn[i+1])));
                fn.erase(fn.begin()+i+1);
                fn.erase(fn.begin()+i);
            }
        }
    }
    if(hasMult){
        for (int i = 1; i < fn.size(); i++) {           //Hace las multiplicaciones y divisiones
            if(fn[i]=="*"){
                fn[i-1]=to_string(stod(fn[i-1])*stod(fn[i+1]));
                fn.erase(fn.begin()+i+1);
                fn.erase(fn.begin()+i);
            }
            if(fn[i]=="/"){
                fn[i-1]=to_string(stod(fn[i-1])/stod(fn[i+1]));
                fn.erase(fn.begin()+i+1);
                fn.erase(fn.begin()+i);
            }
        }
    }
    for (int i = 0; i < fn.size(); i++) {           //Hace las sumas y restas
        if(i==0&&!isSum(fn[0])){
            result+=stod(fn[0]);
        }
        if(fn[i]=="+"){
            result+=stod(fn[i+1]);
        }
        if(fn[i]=="-"){
            result=result-stod(fn[i+1]);
        }
    }
    return result;
}

bool funcion::isSum(string symbol){
    //Comprueba si un símbolo es una suma o resta
    bool is=false;
    if(symbol=="+"||symbol=="-"){
        is=true;
    }
    return is;
}

bool funcion::isMult(string symbol){
    //Comprueba si un símbolo es una multiplicación o división o derivados
    bool is=false;
    if(symbol=="*"||symbol=="/"){
        is=true;
    }
    return is;
}