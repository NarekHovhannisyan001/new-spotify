#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H


#include <QWidget>
#include <QLabel>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QAudioOutput>
#include <QFile>
#include <QTcpSocket>
#include <QUrl>
#include <QFileDialog>

#include <fstream>
#include <iostream>



class MediaPlayer : public QLabel
{
public:
    MediaPlayer(QWidget* parent);
    ~MediaPlayer();

private slots:
    void handle_play_pause();
    void handle_stop();
    void handle_upload();


private:
    void readToFile();
    void clearFileContents();

private:
    QLabel* label;
    QPushButton* play_pause;
    QPushButton* stop;
    QPushButton* upload;
    bool flag;

    QAudioOutput* audio;
    QMediaPlayer* player;


    QString path;
    QString filePath;

    qint64 pausedPosition;

};

#endif // MEDIAPLAYER_H
