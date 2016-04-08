#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   // chnNumChar[10] = new QString[]{"零","一","二","三","四","五","六","七","八","九"};
   // chnUnitSection[4] = new QString[]{"","万","亿","万亿"};
    ui->setupUi(this);
    QRegExp regx("[1-9][0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit);
    ui->lineEdit->setValidator(validator);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(mysetText(QString)));
    connect(ui->lineEdit_2,SIGNAL(textChanged(QString)),this,SLOT(setmynum(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mysetText(QString str)
{
    int unitPos = 0;
    QString chnStr = "";
    bool needZero = false;
    unsigned int num = str.toUInt();
    while(num>0)
    {
        unsigned int sec = num % 10000;
        if(needZero)
            chnStr = chnNumChar[0] + chnStr;
        chnStr = (sec !=0 ) ? chnUnitSection[unitPos] + chnStr : chnUnitSection[0] + chnStr;
        chnStr = SectionToChinese(sec,chnStr);      
        needZero = (sec < 1000) && (sec > 0);
        num /= 10000;
        ++unitPos;
    }
    ui->lineEdit_2->setText(chnStr);
}

QString MainWindow::SectionToChinese(unsigned int sec, QString str)
{
    QString strIns;
    int unitPos = 0;
    bool zero = true;
    while(sec>0)
    {
        int v = sec % 10;
        if(v == 0)
        {
            if((sec == 0) || (!zero))
            {
                zero = true;
                str = chnNumChar[v] + str;
            }
        }
        else
        {
            zero = false;
            strIns = chnNumChar[v];
            strIns += chnUnitChar[unitPos];
            str = strIns + str;
        }
        ++unitPos;
        sec /= 10;
    }
    return str;
}

int MainWindow::ChineseToValue(QString str)
{
    for(int val = 0; val < 10; ++val)
    {
        if(str.compare(chnNumChar[val]) == 0)
            return val;
    }
    return -1;
}

int MainWindow::ChineseToUnit(QString str, bool &flag)
{
    for(int unit = 0; unit < 5; ++unit)
    {
        if(str.compare(chnValuePair[unit].name) == 0)
        {
            flag = chnValuePair[unit].secUnit;
            return chnValuePair[unit].value;
        }
    }
    return 1;
}

void MainWindow::setmynum(QString str)
{
    unsigned int rtn = 0;
    unsigned int section = 0;
    int number = 0;
    bool secUnit = false;
    int pos = 0;

    while(pos<str.length())
    {
        int num = ChineseToValue(str.mid(pos, 1));
        if(num >= 0)
        {
            number = num;
            ++pos;
            if(pos >= str.length())
            {
                section += number;
                rtn += section;
                break;
            }
        }
        else
        {
            int unit = ChineseToUnit(str.mid(pos,1),secUnit);
            if(secUnit)
            {
                section = (section + number) * unit;
                rtn += section;
                section = 0;
            }
            else
            {
                section  += (number * unit);
            }
            number = 0;
            ++pos;
            if(pos >= str.length())
            {
                rtn += section;
                break;
            }
        }
    }
    QString s = QString::number(rtn);
    ui->lineEdit_3->setText(s);
}
