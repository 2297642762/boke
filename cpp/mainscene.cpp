#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPixmap>
#include<QPushButton>
#include<QAction>
#include<QPainter>
#include "mypushbutton.h"
#include<QTimer>
#include<QMouseEvent>
#include<QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("薯条带你爆金币");
    QSoundEffect * startsound = new QSoundEffect(this);
    startsound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    //音乐


    //退出
    connect(ui->quite,&QAction::triggered,[=](){this->close();});

    mypushbutton * starbuttom =new mypushbutton(":/res/MenuSceneStartButton.png");
    starbuttom->setParent(this);
    starbuttom->move(this->width()*0.5-starbuttom->width()*0.5,this->height()*0.7);
    connect(starbuttom,&QPushButton::clicked,[=](){

        //加入音乐
        startsound->play();




        qDebug()<<"点击开始爆金币了！！！";
        starbuttom->zoom1();
        starbuttom->zoom2();

        //延时0.5秒后 进入选择场景
        QTimer::singleShot(500, this,[=](){
            this->hide();
            choosescene->show();

            connect(choosescene,&chooselevelscene::chooseSceneBack,[=](){
            this->show();
            });

        });
    });//跳



}
void MainScene::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);




}

MainScene::~MainScene()
{
    delete ui;
}
