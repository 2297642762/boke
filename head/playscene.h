#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include<mycoin.h>
#include <QMainWindow>
#include<dataconfig.h>
class playscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit playscene(QWidget *parent = nullptr);
    playscene(int index);
    int levalindex;
    int gamearray[4][4];
    void paintEvent(QPaintEvent *e);
    bool iswin = false;
    mycoin * coinbtn[4][4];//金币
signals:
    void  playSceneBack();


};

#endif // PLAYSCENE_H
