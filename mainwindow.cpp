#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(400,180);
    this->setWindowTitle("Spotify");

    play = new MediaPlayer(this);
    play->setGeometry(5,5,390,60);
    play->setStyleSheet("background: green;");
    // play->show();

}



MainWindow::~MainWindow()
{
    delete ui;
}
