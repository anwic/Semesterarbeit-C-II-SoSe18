
#include "zeichenfeld.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent){
    QPalette palette;
    avatar.setRect(1 ,400 - 20 - 2, 25, 25); // Größe, Position
    palette.setColor(QPalette::Background, Qt::white); // Hintergrund
    setPalette(palette);
    setAutoFillBackground(true);



    timer1 = new QTimer();
    timer2 = new QTimer();
    timer3 = new QTimer();
    timer4 = new QTimer();
    connect(timer1, SIGNAL(timeout()),this, SLOT(update()));
    connect(timer2, SIGNAL(timeout()),this, SLOT(abwaerts()));
    connect(timer3, SIGNAL(timeout()),this, SLOT(neuesObjekt()));
    connect(timer4,SIGNAL(timeout()),this,SLOT(mehrPunkte()));
    srand(0); // zufaellige Zahlen
}




QString zeichenFeld::serialize(){
    QString inhalt = QString("p: ");
    inhalt = inhalt + QString::number(punkte); // Punkte in string speichern
    inhalt = inhalt + ";\n";

    inhalt = inhalt + QString("a: ");
    inhalt = inhalt + QString::number(avatar.left()); // Avatarposition speichern
    inhalt = inhalt + ";\n";

    for(int index = 0; index < objekte.size(); index = index + 1){ //Position der Objekte
        inhalt = inhalt + QString("h: ");
        inhalt = inhalt + (QString::number(objekte[index].x()));
        inhalt = inhalt + ";";
        inhalt = inhalt + (QString::number(objekte[index].y()));
        inhalt = inhalt + ";\n";
    }

    return inhalt;
}

void zeichenFeld::deserialize(QString dateiInhalt){ //Datei einlesen
    int index = 3; // p:_
    QString punkteStr ="";
    while(dateiInhalt[index] != ";" ){ // speicher Zahlen bis ; (Punkteanzahl)
        punkteStr += dateiInhalt[index];
        index = index + 1;
    }
    index += 4;
    punkte = punkteStr.toInt(); // Zahl speichern
    QString spielerStr =""; //Avatarposition aus string
    while(dateiInhalt[index] != ";" ){
        spielerStr += dateiInhalt[index];
        index = index + 1;
    }
    index += 4;
    avatar.moveLeft(spielerStr.toInt());
    objekte.clear(); //Objekte werden gelöscht
    while(index < dateiInhalt.length()){ // gespeicherte Objekte werden geladen
        QString xStr = "";
        while(dateiInhalt[index] != ";"){
            xStr += dateiInhalt[index];
            index = index + 1;
        }
        int x;
        x = xStr.toInt();
        index = index + 1;
        QString yStr = "";
        while(dateiInhalt[index] != ";"){
            yStr += dateiInhalt[index];
            index = index + 1;
        }
        int y;
        y = yStr.toInt();

        objekte.push_back(QRect(x,y,20,20)); //Objekt in die Objektliste gespeichert
        index += 4;
    }
    update(); //nachzeichnen
}

void zeichenFeld::rechts(){ // Bewegung des Avatars
    if(avatar.x() + 55 < 1000){
       avatar.moveLeft(avatar.x() + 30);
    }else {
        avatar.moveLeft(975);
    }
}

void zeichenFeld::links(){
    if(avatar.x() - 30 > 0){
        avatar.moveLeft(avatar.x() - 30);
    } else {
        avatar.moveLeft(0);
    }
}

void zeichenFeld::neuesObjekt(){ //neuen Objekte im Spielfeld
    int x = rand() % (980); // Zahlen von 0 - 980 (zufaellige zahl)
    QRect objekt;
    objekt.setHeight(20);
    objekt.setWidth(20);
    objekt.moveLeft(x);
    objekt.setY(1);
    objekte.push_back(objekt);
}

void zeichenFeld::abwaerts(){ //Geschwindigkeit der Objekte
    std::vector<QRect>::iterator o;

    for(o = objekte.begin(); o != objekte.end(); ++o){
        if(o->bottom() < 400){
            o->moveTop(o->top() + 2);
        } else {
            objekte.erase(o);
        }
    }
}

void zeichenFeld::mehrPunkte(){ // Punktestand erhört sich
   punkte = punkte + 5;
}

void::zeichenFeld::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    painter.drawText(0,22, QString::number(punkte)); //Punktanzeige
    painter.setBrush(Qt::Dense1Pattern); // Hindernisse


    for(int index = 0; index < objekte.size(); index++){
        painter.drawEllipse(objekte[index]); //runde Hindernisse
    }
    //leben
    painter.setPen(Qt::white);
    painter.setBrush(Qt::magenta);
    painter.drawEllipse(975,10,14,14);
    painter.drawEllipse(955,10,14,14);
    painter.drawEllipse(935,10,14,14);



    //avatar
    painter.setBrush(Qt::DiagCrossPattern);
    painter.drawRect(avatar);


    painter.end();
}


void zeichenFeld::start(){
  timer1->start(10);
  timer2->start(10);
  timer3->start(1000);
  timer4->start(2000);
}

void zeichenFeld::pause(){
  timer1->stop();
  timer2->stop();
  timer3->stop();
  timer4->stop();
}
