#include "meinwidget.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    meinWidget widget;
    widget.setGeometry(100,100,1100,400);
    widget.show();
    return a.exec();
}
