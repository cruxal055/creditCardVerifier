#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <iostream>
#include <QTextStream>
#include <vector>
#include <fstream>
#include <qobject.h>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <qinputdialog.h>


typedef std::vector<std::map<std::string, std::string>> mapVector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void pressedEnter();


    protected:
        void changeEvent(QEvent *e);

    private:
        Ui::MainWindow *ui;     
        void setupSignalsSlots();
        QString toQString(std::string data);
        void details(std::string &data, std::string cardType);
        void readBankFile(std::map<int, std::string> &bank, std::string fileName);
        void displayMap(std::map<std::string, std::string> bank);
        QString readGeneralFile();
        void parse(int bin, std::string &holdData, std::map<int,std::string>bank, bool &works);
        bool luhn(std::string number);
        void readEmAll();
        void display( std::map<int,std::string>fuck);
        void loadArr(std::string arr[], std::string toReplace);

        std::string mcKey[4], visaKey[4],amexKey[4];
        std::map<int,std::string>visa, mc, amex;
        std::vector<mapVector>cardTypes;


    private slots:
       // void updateSelected(int index);
};

#endif // MAINWINDOW_H
