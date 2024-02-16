#ifndef CTUNES_H
#define CTUNES_H
#include <fstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <Genero.h>
#include <qfile.h>

using namespace std;

class ctunes
{
public:
    ctunes();
    int getCode(long);
    void addSong(string, string, Genero::Generos,double,string);
    void reviewSong(int, int);
    string downloadSong(int , string );
    QString songs(string);
    string infoSong(int);
    bool verificar_codigo(int);
private:
    int codecancion = 1;
    int codedownload = 1;
};


#endif // CTUNES_H
