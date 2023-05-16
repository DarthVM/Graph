#ifndef GRAPH_MYWIDGET_H
#define GRAPH_MYWIDGET_H

#include "Graph.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPen>





class MyWidget : public QWidget  {
public:
    MyWidget(Graph*, int, int, QWidget *parent = nullptr);
protected:
    int width;
    int height;
    Graph *G;
    void paintEvent(QPaintEvent *);
    void drawLines(QPainter*);
};


#endif //GRAPH_MYWIDGET_H
