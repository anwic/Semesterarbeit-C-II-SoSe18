#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>

class zeichenFeld : public QWidget{
    Q_OBJECT
public:
    zeichenFeld(QWidget *parent = 0);
    void links();
    void rechts();
    void start();
    void pause();
    QString serialize(); //speichert in String
    void deserialize(QString dateiInhalt);


private:
    int punkte = 0;
    QRect avatar;
    std::vector<QRect> objekte;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;

protected:
    void paintEvent(QPaintEvent *event); //Visualisierung auf Spielfeld


private slots:
    void mehrPunkte();
    void abwaerts();
    void neuesObjekt();
};

