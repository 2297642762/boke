#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    void paintEvent(QPaintEvent *e);


private:
    Ui::MainScene *ui;
    chooselevelscene *choosescene = new chooselevelscene;
};
#endif // MAINSCENE_H
