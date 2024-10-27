#include "chooselevelscene.h"
#include<QMenuBar>
#include<QDebug>
#include<QPainter>
#include<mypushbutton.h>
#include<QMouseEvent>
#include<QTimer>
#include<QLabel>
#include<QSoundEffect>
chooselevelscene::chooselevelscene(QWidget *parent)
    : QMainWindow{parent}
{

    this->setFixedSize(320,588);

    //this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    QPixmap icon(":/res/Coin0001.png");

    if (icon.isNull()) {
        qDebug() << "Icon loading failed!";
    } else {
        this->setWindowIcon(icon);
    }
    this->setWindowTitle("薯条选择关卡");

    QMenuBar * bar=this->menuBar();
    this->setMenuBar(bar);
    QMenu * starmenu = bar->addMenu("开始");
    QAction * quiteaction = starmenu->addAction("退出");
    connect(quiteaction,&QAction::triggered,[=](){
        this->close();
    });


    //选择关卡音效
    QSoundEffect * choosesound = new QSoundEffect(this);
    choosesound ->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    //返回音效
    QSoundEffect * backsound = new QSoundEffect(this);
    backsound ->setSource(QUrl::fromLocalFile(":/res/:/res/BackButtonSound.wav"));
    //返回按钮
    mypushbutton * closebtn= new mypushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closebtn->setParent(this);
    closebtn->move(this->width()-closebtn->width(),this->height()-closebtn->height());

    connect(closebtn,&QPushButton::clicked,[=](){
        backsound->play();
        if(closebtn->Pressimgpath!= "") //选中路径不为空，显示选中图片
            {
                QPixmap pixmap;
                bool ret = pixmap.load(closebtn->Pressimgpath);
                if(!ret)
                {
                    qDebug() << closebtn->Pressimgpath << "加载图片失败2!";
                }

                closebtn->setFixedSize( pixmap.width(), pixmap.height() );
                closebtn->setStyleSheet("QPushButton{border:0px;}");
                closebtn->setIcon(pixmap);
                closebtn->setIconSize(QSize(pixmap.width(),pixmap.height()));

            };
        QTimer::singleShot(300, this,[=](){
                QPixmap pixmap;
                bool ret = pixmap.load(closebtn->Normalimgpath);
                if(!ret)
                {
                    qDebug() << closebtn->Normalimgpath << "加载图片失败2!";
                }

                closebtn->setFixedSize( pixmap.width(), pixmap.height() );
                closebtn->setStyleSheet("QPushButton{border:0px;}");
                closebtn->setIcon(pixmap);
                closebtn->setIconSize(QSize(pixmap.width(),pixmap.height()));
        });

            QTimer::singleShot(500, this,[=](){
                this->hide();
                //触发自定义信号，关闭自身
                emit this->chooseSceneBack();
            });

    });

    for(int i =0 ;i<20;i++)
    {
        mypushbutton *menubtn = new mypushbutton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(40 + (i%4)*70 , 135+ (i/4)*70);

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString("第%1关").arg(QString::number(i+1)));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
        label->move(40 + (i%4)*70 , 135+ (i/4)*70);//让数字在按钮上显示
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);  //鼠标事件穿透

        connect(menubtn,&QPushButton::clicked,[=](){
            choosesound->play();
        if(pscene == NULL)
            {
            this->hide();
            pscene = new playscene(i+1);
            pscene->show();
                connect(pscene,&playscene::playSceneBack,[=](){
                this->setGeometry(pscene->geometry());
                this->show();
                delete pscene;
                pscene = NULL;
            });
        }

        });
    }



}
void chooselevelscene::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);






}
