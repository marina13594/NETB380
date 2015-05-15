#include "secdialog.h"
#include "ui_secdialog.h"
#include <QDebug>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);

    QString sPath = "C:/";

    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(dirmodel);

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::Files);
    filemodel->setRootPath(sPath);
    ui->listView->setModel(filemodel);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_treeView_clicked(const QModelIndex &index)
{
    sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
}

void SecDialog::on_listView_clicked(const QModelIndex &index)
{
    qDebug() << index.data(Qt::DisplayRole ).toString();
    sPath=sPath+"/"+(index.data(Qt::DisplayRole ).toString());
}

void SecDialog::on_ok_button_clicked()
{
    char tag[4]; //the 3 character (byte) portion of the mp3 file
    char songTitle[31]; //30 characters (bytes)
    char artist[31]; //30 characters (bytes)
    char album[31]; //30 characters (bytes)
    char year[5]; //4 characters (bytes)
    char comment[29]; //28 characters (bytes)

    //variable declaration (binary portion of file)
    char zero; //this is always 0
    char track; //track number for mp3 file
    char genre; //number telling which genre the song belongs to

    //variable declaration (string)
    string mp3Name = sPath.toLocal8Bit().constData(); //name of mp3 file
    qDebug() << sPath << endl;
    //variable declaration (read input from a file)
    ifstream mp3In; //read information from mp3 file

    //Open the file, converting the mp3 file name to a c string
    mp3In.open(mp3Name.c_str(), ios::binary);

    //Check to make sure that the file can be opened
    //If not, display an ERROR message and end the program
    if (!mp3In.is_open())
    {
        qDebug() << "ERROR! Couldn't open mp3 file. Ending program" << endl;
    }
    else
    {
        //set ifstream pointer to the beginning of the last 128 bytes in the file
        mp3In.seekg(-128, ios::end);

        //read in the bytes and store them in appropriate variables
        //At the end of each unformatted variable (or variable without a \0), add a terminating character to parse the
        //byte sequence
        mp3In.read(tag, 3);
        tag[3] = '\0';
        mp3In.read(songTitle, 30);
        songTitle[30] = '\0';
        mp3In.read(artist, 30);
        artist[30] = '\0';
        mp3In.read(album, 30);
        album[30] = '\0';
        mp3In.read(year, 4);
        year[4] = '\0';
        mp3In.read(comment, 28);
        comment[28] = '\0';
        mp3In >> zero;
        mp3In >> track;
        mp3In >> genre;

        //display current ID3v1.1 information to the user
        qDebug() << "Tag: " << tag << endl
        << "Song Title: " << songTitle << endl
        << "Artist: " << artist << endl
        << "Album: " << album << endl
        << "Year: " << year << endl
        << "Comment: " << comment << endl
        << "Zero byte: " << (int)zero << endl
        << "Track byte: " << (int)track << endl
        << "Genre byte: " << (int)genre << endl;
    }
    mp3In.close();
}
