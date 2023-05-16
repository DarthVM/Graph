#include "Graph.h"
#include "MyWidget.h"





#define WIDTH 1024
#define HEIGHT 768

#define vert(class_object) class_object.Get_V()
#define edge(class_object) class_object.Get_E()

using namespace std;



 int main(int argc, char *argv[]) {
     Graph G;
     G.Keys();
     QApplication app(argc, argv);
     MyWidget window(&G, WIDTH, HEIGHT);
     window.resize(WIDTH, HEIGHT);
     window.setWindowTitle("Graph");
     window.show();
     return app.exec();



 }