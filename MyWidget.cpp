#include "MyWidget.h"


#define vert(class_object) class_object->Get_V()
#define edge(class_object) class_object->Get_E()


#define POINT_IN(num, x1, y1) coord[num][0]=x1; coord[num][1]=y1;
#define POINT(num) coord[num][0], coord[num][1]

#define X(num) coord[num][0]
#define Y(num) coord[num][1]


int Is_Full(const int coord[][2], int s, int mode) { // Checking if the all veretxes have coordinates; Mode 1 - for number, Mode 2 - for vertex
    int k=0;
    switch (mode) {
        case 1: {
            for(int i=0; i<s; i++)
                for(int j=0; j<2; j++)
                    if(coord[i][j]==0)
                        k++;

            return k;
        }

        case 2: {
            for (int i = 0; i < s; i++)
                for (int j = 0; j < 2; j++)
                    if (coord[i][j] == 0)
                        return i;
        }
        default:
            return -1;

    }

}




MyWidget::MyWidget(Graph *G2, int a, int b, QWidget *parent) : G(G2), width(a), height(b), QWidget(parent) {}




void MyWidget::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event)

    QPainter qp(this);
    drawLines(&qp);
}

void MyWidget::drawLines(QPainter *qp) {


    int size=(int)vert(G).size();
    list<Edge> &p=edge(G);
    int coord[size][2];

    for (int i = 0; i <= size; i++)
        for (int j = 0; j <= size; j++)
            coord[i][j] = 0;


    QPen pen(Qt::black, 5, Qt::SolidLine);
    QPen pen2(Qt::red, 20, Qt::SolidLine);
    QPen pen3(Qt::blue, 5, Qt::SolidLine);


    int loc = 0, space = 50, len=125;

    int n = G->Vert_Degree(1);

    POINT_IN(0, width / 2, space)

    for (int i = 1; i < n; i++) {
        loc = loc + width / n;
        qp->setPen(pen);
        qp->drawLine(width / 2, space, loc, len);
        POINT_IN(i, loc, len)
    }

    qp->setPen(pen);
    qp->drawLine(width / 2, space, loc, space);
    POINT_IN(n, loc, space)

    len = len*2;
    int t=Is_Full(coord, size, 1);
    loc=width/t;
    for (int i=n+1; i<size; i++) {
        POINT_IN(Is_Full(coord,size, 2), loc, len)
        loc = loc + width/t;
    }

    qp->setPen(pen);
    for (auto it : p) {
        if ( (V1 != 1 || V2 != 1) || (V1 != n || V2 != n)  )  {
            qp->drawLine(POINT(V1-1), POINT(V2-1));
        }
    }


    QString str;
    qp->setPen(pen2);


    QFont font("Calibre",  15,QFont::Bold,  false);
    qp->setFont(font);



    for (int i = 0; i < size; i++) {
        qp->setPen(pen2);
        qp->drawPoint(POINT(i));

        str = QString::fromStdString(to_string(i+1));
        qp->setPen(pen3);
        qp->drawText(X(i)+15,Y(i)+35, str);

    }

}