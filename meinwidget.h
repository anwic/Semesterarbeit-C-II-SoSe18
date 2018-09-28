#include "zeichenfeld.h"
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QtWidgets>

class meinWidget : public QWidget{
    Q_OBJECT
public:
    meinWidget(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *);

private:
    zeichenFeld *meinZeichenFeld;
    bool gesperrt = true;

private slots:
    void pause();
    void start();
    void speichern();
    void laden();
};
