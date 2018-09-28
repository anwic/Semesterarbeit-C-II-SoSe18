#include "meinwidget.h"

meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent) {

    QPalette palette;
    palette.setColor(QPalette::Background, Qt::white); // Hintergund
    meinZeichenFeld = new zeichenFeld();
    QPushButton *speichern = new QPushButton("Speichern");
    QPushButton *laden = new QPushButton("Laden");
    QPushButton *start = new QPushButton("Start");
    QPushButton *pause = new QPushButton("Pause");
    connect(laden, SIGNAL(clicked()), this, SLOT(laden()));
    connect(speichern, SIGNAL(clicked()), this, SLOT(speichern()));
    connect(start, SIGNAL(clicked()), this, SLOT(start()));
    connect(pause, SIGNAL(clicked()), this, SLOT(pause()));
    setPalette(palette);
    setAutoFillBackground(true);
    QGridLayout *gridLayout = new QGridLayout; //Positionen
    gridLayout->addWidget(start,0,1);
    gridLayout->setRowMinimumHeight(0,100);
    gridLayout->addWidget(pause,1,1);
    gridLayout->setRowMinimumHeight(1,100);
    gridLayout->addWidget(speichern,2,1);
    gridLayout->setRowMinimumHeight(2,100);
    gridLayout->addWidget(laden,3,1);
    gridLayout->setRowMinimumHeight(3,100);
    gridLayout->addWidget(meinZeichenFeld,0,0,4,1);
    gridLayout->setColumnMinimumWidth(0,1000);
    gridLayout->setColumnMinimumWidth(1,40);
    gridLayout->setColumnStretch(1,10);
    gridLayout->setRowStretch(4,10); // Wenn Fenster vergrößert wird, wird nicht das Spielfeld mit vergrößert
    setLayout(gridLayout);


}


void meinWidget::speichern(){
    QFile datei;
    pause();



    QFileDialog fenster(this);
    QString dateiName = fenster.getSaveFileName(this,tr("Speichern"), "", tr("Spielstand (*.xyz)"));
    datei.setFileName(dateiName);
    bool fehler =  datei.open(QIODevice::WriteOnly | QIODevice::Text); //abbruch bei Fehler
    if(fehler == false){
        return;
    }
    QTextStream textStream(&datei);
    textStream << meinZeichenFeld->serialize();
    datei.close();



}

void meinWidget::laden(){
    QFile datei;
    pause();



    //gespeicherte Datei wird geladen
    QFileDialog fenster(this);
    QString dateiName = fenster.getOpenFileName(this,tr("Laden"), "", tr("Spielstand (*.xyz)"));
    datei.setFileName(dateiName);

    bool fehler =  datei.open(QIODevice::ReadOnly | QIODevice::Text);
    if(fehler == false){
        return;
    }
    QString inhalt = datei.readAll(); // speichert Datei in string
    meinZeichenFeld->deserialize(inhalt);
    datei.close();
}

void meinWidget::keyPressEvent(QKeyEvent *event){ //Steuerung des Avatars
    if (event->key() == Qt::Key_Right) {
        if(!gesperrt){
            meinZeichenFeld->rechts();
        }
    }

    if(event->key() == Qt::Key_Left){
        if(!gesperrt){
            meinZeichenFeld->links();
        }
    }

}
void meinWidget::pause(){
    meinZeichenFeld->pause();
    gesperrt = true;
}


void meinWidget::start(){
    meinZeichenFeld->start();
    gesperrt = false;
}
