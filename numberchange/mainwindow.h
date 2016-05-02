#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}

typedef struct
{
    QString name;
    int value;
    bool secUnit;
}chn_name_value;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    chn_name_value chnValuePair[5] = {
        {"十", 10, false},{"百", 100, false},{"千", 1000, false},{"万", 10000, true},{"亿", 100000000, true}
    };
    QString chnNumChar[10] = {"零","一","二","三","四","五","六","七","八","九"};
    QString chnUnitSection[4] = {"","万","亿","万亿"};
    QString chnUnitChar[4] = {"","十","百","千"};
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString SectionToChinese(unsigned int sec, QString str);
    int ChineseToValue(QString str);
    int ChineseToUnit(QString str, bool &flag);
public slots:
    void mysetText(QString str);
    void setmynum(QString str);
};

#endif // MAINWINDOW_H
