#include "mycoin.h"
#include<QDebug>
#include<QIcon>
#include<QTimer>
mycoin::mycoin(QWidget *parent)
    : QPushButton{parent}
{}
mycoin::mycoin(QString butpth)
{
    QPixmap pix ;
    bool ret = pix.load(butpth);
    if(!ret)
    {
        qDebug()<<butpth<<"图片读取失败金币";
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    time1=new QTimer(this);
    time2=new QTimer(this);


    connect(time1,&QTimer::timeout,[=](){
        QString str;
        str = QString(":/res/Coin000%1.png").arg(this->min++);
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min=1;
            this->isanimation=false;
            time1->stop();
        }

    });


    connect(time2,&QTimer::timeout,[=](){
        QString str;
        str = QString(":/res/Coin000%1.png").arg((this->max)--);
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min=8;
            this->isanimation=false;
            time2->stop();
        }

    });

}
void mycoin::changeflag()
{
    if(this->flag) //如果是正面，执行下列代码
    {
        time1->start(30);
        this->isanimation=true;
        this->flag = false;
    }
    else //反面执行下列代码
    {
        time2->start(30);
        this->isanimation=true;
        this->flag = true;
    }


}
void mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isanimation)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}
