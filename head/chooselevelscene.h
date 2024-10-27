#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include "playscene.h"
#include <QMainWindow>

class chooselevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevelscene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    playscene * pscene = NULL;
signals:
    void  chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
