#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QMouseEvent>
class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mypushbutton(QWidget *parent = nullptr);
    mypushbutton(QString normalimgpath,QString pressimgpath=" ");//按下前 按下后

    //跳跃
    void zoom1();
    void zoom2();
    QString Normalimgpath;
    QString Pressimgpath;
    // void mousePressEvent(QMouseEvent *e);
    // void mouseReleaseEvent(QMouseEvent *e);

private:


signals:
};

#endif // MYPUSHBUTTON_H
