#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSignalsSlots();
    ui->textBrowser->append("Please enter a credit card value\n");
    readBankFile(visa,"/Users/blank/Documents/CS3A/build-creditCard-Desktop_Qt_5_11_0_clang_64bit-Debug/VisaNeo.txt");
    readBankFile(mc,"/Users/blank/Documents/CS3A/build-creditCard-Desktop_Qt_5_11_0_clang_64bit-Debug/mcNeo.txt");
    readBankFile(amex,"/Users/blank/Documents/CS3A/build-creditCard-Desktop_Qt_5_11_0_clang_64bit-Debug/AmexNeo");
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSignalsSlots()
{
    connect(ui->enterButton,SIGNAL(pressed()),this,SLOT(pressedEnter()));
    connect(ui->exitButton,SIGNAL(pressed()),this,SLOT(close()));
}
QString MainWindow::toQString(std::string data)
{
    QString temp = QString::fromStdString(data);
    return temp;
}

void MainWindow::details(std::string &data, std::string cardType)
{
    std::string results[3];
    results[0] = "TYPE: " + cardType ;
    results[1] = "LEVEL: ";
    results[2] = "BANK: ";
    int index = 1;
    for(size_t i = 0; i < data.size(); ++i)
    {
        if(data[i] == '~')
        {
            results[index]+=data.substr(0,i);
            data.erase(0,i+1);
            ++index;
        }
        if(data.find('~') > data.size())
        {
            results[index] += data;
            break;
        }
    }
    for(size_t i = 0; i < 3; ++i)
        ui->textBrowser->append(toQString(results[i]));
}

void MainWindow::pressedEnter()
{
    bool work;
    int bin = 0;
    QString userData = ui->textEdit->toPlainText();
    std::string cardInfo, cardType;
    ui->textBrowser->clear();
    for(int i = 0; i < userData.size();++i)
    {
        int ascii = userData[i].toLatin1();
        if( ascii < 48  || ascii > 57)
        {
            ui->textEdit->clear();
            ui->textBrowser->clear();
            ui->textBrowser->append("Error invalid input! Please try again!\n");
            ui->textEdit->clear();
        }
        else
        {
            ui->textBrowser->clear();       
            if(luhn(userData.toStdString()))
            {
                bin = userData.left(6).toInt();
                ui->textBrowser->append("Valid Card, obtaining infortmation...\n");
                char switchero = userData[0].toLatin1();
                switch(switchero)
                {
                    case '5':
                        cardType = "Mastercard";
                        parse(bin,cardInfo,mc,work);
                        break;
                    case '3':
                        cardType = "American Express";
                        parse(bin,cardInfo,amex,work);
                        break;
                    case '4':
                        cardType = "Visa";
                        parse(bin,cardInfo,visa,work);
                        break;
                    default:
                        ui->textBrowser->append("No info on card! ");
                }
                if(work)
                    details(cardInfo,cardType);
                else
                    ui->textBrowser->append("Card is Valid, but database has no infortmation on card!\n");
            }
            else
                ui->textBrowser->append("invalid Card! Card does not exist!\n");
        }
    }
    ui->textBrowser->append("\nPlease Input New Data\n");
}

void MainWindow::readBankFile(std::map<int, std::string> &bank, std::string fileName)
{
    std::string data, bin;
    std::ifstream file(fileName.c_str());
    while(std::getline(file,data))
    {
        int index;
        bin = data.substr(0,6);
        index = std::stoi(bin);
        bank[index] = data.substr(7);
    }

}

void MainWindow::parse(int bin, std::string &holdData, std::map<int,std::string>bank, bool &works)
{
   if(bank.find(bin) == bank.end())
       works = false;
   else
   {
       holdData = bank[bin];
       works = true;
   }
}
bool MainWindow::luhn(std::string number)
{
    int index = number.length() - 1;
    int pos = 1;
    int checkSum = 0;
    while(index >= 0)
    {
        int temp;
        pos % 2 == 0 ? temp = 2 * (int)(number[index] - '0') : temp = (int)(number[index] - '0');
        if(temp >= 10)
        {
            checkSum += temp % 10;
            checkSum += temp / 10;
        }
        else
        checkSum += temp;
        ++pos;
        --index;
    }
    return (checkSum % 10 == 0);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
