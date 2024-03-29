#include "ctunnes.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <stdlib.h>
#include <genero.h>
#include <QDate>
#include <QDebug>
#include <sstream>

using namespace std;

struct song{
    int code;
    QString nombre;
    QString cantante;
    QString genero;
    QString duracion;
    double precio;
    int estrellas,reviews;
};

struct download
{
    int codedown;
    QString fecha;
    QString cancion;
    int codesong;
    QString cliente;
    double precio;
};

QFile codigoarchivo("codigo.itn");
QFile downloadarchivo("download.itn");
QFile songsarchivo("song.itn");

QDataStream readC(&codigoarchivo);
QDataStream writeC(&codigoarchivo);
QDataStream writeS(&songsarchivo);
QDataStream writeD(&downloadarchivo);

ctunes::ctunes() {
    codigoarchivo.open(QIODevice::ReadWrite);
    downloadarchivo.open(QIODevice::ReadWrite);
    songsarchivo.open(QIODevice::ReadWrite);

    qint64 size = codigoarchivo.size();
    if(size == 0) {
        int codecancion = 1;
        int codedownload = 1;
        QDataStream readC(&codigoarchivo);
        readC << codecancion << codedownload;
    }
}

int ctunes::getCode(long offset) {
    codigoarchivo.seek(offset);
    int codigosong;
    QDataStream writeC(&codigoarchivo);
    writeC >> codigosong;

    codigoarchivo.seek(offset);
    int nextcode = codigosong + 1;

    QDataStream readC(&codigoarchivo);
    readC << nextcode;

    return codigosong;
}

void ctunes::addSong(string nombre, string cantante, Genero::Generos generoCantante, double precio,string duracion){
    string genero;
    if (generoCantante == Genero::POP) {
        genero = "Pop";
    } else if (generoCantante == Genero::ROCK) {
        genero = "Rock";
    } else if (generoCantante == Genero::RAP) {
        genero = "Rap";
    } else if (generoCantante == Genero::DANCE) {
        genero = "Dance";
    } else if (generoCantante == Genero::REGGAE) {
        genero = "Raggae";
    } else if (generoCantante == Genero::ELECTRONICA) {
        genero = "Electronica";
    } else if (generoCantante == Genero::RANCHERA) {
        genero = "Ranchera";
    }

    song songs;
    songsarchivo.seek(songsarchivo.size());
    songs.code = getCode(0);
    songs.nombre = QString::fromStdString(nombre);
    songs.cantante = QString::fromStdString(cantante);
    songs.genero = QString::fromStdString(genero);
    songs.precio = precio;
    songs.reviews = 0;
    songs.estrellas = 0;
    songs.duracion = QString::fromStdString(duracion) ;
    writeS << songs.code << songs.nombre << songs.cantante << songs.genero << songs.precio << songs.reviews << songs.estrellas << songs.duracion;
    codigoarchivo.flush();
}



string ctunes::infoSong(int codeSong) {
    songsarchivo.seek(0);
    string textoconcatenado;
    int numerodescargas=0;
    bool cancionEncontrada = false;
    while (!songsarchivo.atEnd()) {
        song songs;
        writeS >> songs.code >> songs.nombre >> songs.cantante >> songs.genero >> songs.precio >> songs.reviews >> songs.estrellas >> songs.duracion;

        if (songs.code == codeSong) {
            cancionEncontrada = true;
            textoconcatenado = "Codigo: " + QString::number(songs.code).toStdString() + "\nCancion: " + songs.nombre.toStdString() + "\nCantante: " + songs.cantante.toStdString() + "\nGenero: " + songs.genero.toStdString() + "\nPrecio: " + QString::number(songs.precio).toStdString() + "\nReviews: " + QString::number(songs.reviews).toStdString() + "\nEstrellas: " + QString::number(songs.estrellas).toStdString() + "\nDuracion: " + songs.duracion.toStdString();

            downloadarchivo.seek(0); // Mover el puntero de archivo aquí para volver al principio del archivo de descargas

            while (!downloadarchivo.atEnd()) {

                download descarga;
                writeD >> descarga.codedown >> descarga.fecha >> descarga.codesong >> descarga.cliente >> descarga.precio;
                numerodescargas++;
                if (codeSong == descarga.codesong) {
                    textoconcatenado = "\n--------------------------------\nCodigo de descarga: " + QString::number(descarga.codedown).toStdString() + "\nfecha de descarga: " + descarga.fecha.toStdString() + "\nCodigo de la cancion: " + QString::number(descarga.codesong).toStdString() + "\nNombre Cliente: " + descarga.cliente.toStdString() + "\nPrecio de compra: " + QString::number(descarga.precio).toStdString()+"\nNumero de descargas: " +QString::number(numerodescargas).toStdString();
                }
            }

        }
    }

    if (!cancionEncontrada) {
        return "No se encontró la canción";
    }

    return textoconcatenado;
}

void ctunes::reviewSong(int code, int stars) {
    songsarchivo.seek(0);
    while (!songsarchivo.atEnd()) {
        qint64 pos = songsarchivo.pos();
        song songs;
        writeS >> songs.code >> songs.nombre >> songs.cantante >> songs.genero >> songs.precio >> songs.reviews >> songs.estrellas >> songs.duracion;
        if (songs.code == code) {
            if (stars >= 0 && stars <= 5) {
                int reviewCont = songs.reviews + 1;
                int newStars = songs.estrellas + stars;
                //double rating = (double)newStars / reviewCont;
                songsarchivo.seek(pos);
                writeS << songs.code << songs.nombre << songs.cantante << songs.genero << songs.precio << reviewCont << newStars << songs.duracion;
                songsarchivo.flush();
                break;
            }
        }
    }
}


bool ctunes::verificar_codigo(int codes) {
    songsarchivo.seek(0);
    while (!songsarchivo.atEnd()) {
        song songs;
        writeS >> songs.code >> songs.nombre >> songs.cantante >> songs.genero >> songs.precio >> songs.reviews >> songs.estrellas >> songs.duracion;
        if (songs.code == codes) {
            return true;
        }
    }
    return false;
}
/*QString ctunes::songs(string txtFile){
    QString path = QString::fromStdString(txtFile+".txt");
    QFile file(path);
    QTextStream out(&file);

    file.open(QIODevice::ReadWrite);
    file.resize(0);

    songsarchivo.seek(0);
    while (!songsarchivo.atEnd()) {
        song songs;
        writeS >> songs.code >> songs.nombre >> songs.cantante >> songs.genero >> songs.precio >> songs.reviews >> songs.estrellas >> songs.duracion;
        file.seek(file.size());
        if(songs.reviews!=0){
            out << "-CODIGO: " << songs.code << "-TITULO: " << songs.nombre << "-CANTANTE: "<< songs.cantante << "-GENERO: "<< songs.genero << "-PRECIO:" << songs.precio;
        }else{
            out << "-CODIGO:  " << songs.code << "-TITULO: " << songs.nombre << " -CANTANTE: "<< songs.cantante << "-GENERO: "<< songs.genero << "-PRECIO:" << songs.precio;
        }
    }
    file.close();
    file.open(QIODevice::ReadOnly);
    file.seek(0);
    QString text = out.readAll();
    qDebug() << text;
    return text;
}
*/
string ctunes::downloadSong(int code,string cliente){
    songsarchivo.seek(0);
    while (!songsarchivo.atEnd()) {
        song songs;
        writeS >> songs.code >> songs.nombre >> songs.cantante >> songs.genero >> songs.precio >> songs.reviews >> songs.estrellas >>songs.duracion;
        if (songs.code == code) {

            QDate currentDate = QDate::currentDate();
            QString stringDate = currentDate.toString("dd-MM-yyyy");

            download descarga;
            downloadarchivo.seek(downloadarchivo.size());
            descarga.codedown = getCode(4);
            descarga.fecha = stringDate;
            descarga.codesong=songs.code;
            descarga.cliente = QString::fromStdString(cliente);
            descarga.precio=songs.precio;
            descarga.cancion=songs.nombre;
            writeD << descarga.codedown << QString::fromStdString(descarga.fecha.toStdString())<< descarga.codesong << descarga.cliente << descarga.precio;
            return "Gracias " + descarga.cliente.toStdString()+ " por bajar " + descarga.cancion.toStdString() +" a un costo de Lps. " + QString::number(descarga.precio).toStdString();

        }

    }
    return "no se encontro la cancion";
}
