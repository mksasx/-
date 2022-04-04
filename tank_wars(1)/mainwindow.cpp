#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QInputDialog>
#include <QProcess>
#include <QDebug>
#include <iostream>
#include <string>
#include <windows.h>
#include <QThread>

int totalspeed = 5;

class GameThread : public QThread
{
public:
    GameThread(){
    }
    void run(){
        std::string cmd = "Tank-War.exe" + QString::number(totalspeed, 10).toStdString();
        system(cmd.c_str());
    }

};

QMediaPlayer* player = new QMediaPlayer;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMediaPlaylist *playList = new QMediaPlaylist(this);
    playList->addMedia(QUrl("qrc:/BGM.mp3"));
    player->setPlaylist(playList);
    player->setVolume(100);
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    GameThread *game = new GameThread();
    game->start();
}

void MainWindow::on_pushButton_4_clicked()
{
    player->stop();
    ui->pushButton_4->setText(QString("已静音"));
    ui->pushButton_4->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    bool isOK;
    QString text = QInputDialog::getText(NULL, "调节速度", "请输入速度(范围1~10):", QLineEdit::Normal,"5", &isOK);
    if(isOK && !text.isEmpty()) {
          totalspeed = text.toInt();
    }
    else
        totalspeed = 5;
}

void MainWindow::on_pushButton_2_clicked()
{

}

