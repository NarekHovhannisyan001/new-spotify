#include "mediaplayer.h"

MediaPlayer::MediaPlayer(QWidget* parent)
    : QLabel(parent),
    label(new QLabel("select music", this)),
    play_pause(new QPushButton("►", this)),
    stop(new QPushButton("🔄", this)),
    upload(new QPushButton("💻",this)),
    flag(false),
    audio(new QAudioOutput(this)),
    player(new QMediaPlayer(this)),
    filePath("/Users/narek/Desktop/MyMusic/music.mp3"),
    pausedPosition(-1)
{
    label->setGeometry(5, 5, 95, 40);

    play_pause->setGeometry(110, 5, 40, 40);
    connect(play_pause, &QPushButton::clicked, this, &MediaPlayer::handle_play_pause); // <-- Add this line

    stop->setGeometry(160, 5, 40, 40);
    connect(stop, &QPushButton::clicked, this, &MediaPlayer::handle_stop);

    upload->setGeometry(210,5,40,40);
    connect(upload,&QPushButton::clicked,this,&MediaPlayer::handle_upload);

    audio->setVolume(0.5);

    player->setAudioOutput(audio);

    clearFileContents();
}


void MediaPlayer::handle_play_pause() {
    if (!flag) {
        if (pausedPosition != -1) {
            // If the media was paused, resume from the paused position
            player->setPosition(pausedPosition);
            player->play();
        } else {
            // Set the source of QMediaPlayer to the copied music file
            player->setSource(QUrl::fromLocalFile(filePath));
            // Play the media
            player->play();
        }
        play_pause->setText("⏸");
    } else {
        // Pause the media
        player->pause();
        // Store the position where playback was paused
        pausedPosition = player->position();
        play_pause->setText("►");
    }
    flag = !flag;
}





void MediaPlayer::handle_upload() {
    // std::cout << "12334";
    path = QFileDialog::getOpenFileName(nullptr, "Select file to upload", QDir::homePath());
    clearFileContents();
    readToFile();
    player->stop();
    flag = false;
    play_pause->setText("►");
    label->setText(QFileInfo(path).fileName());
    player->setSource(QUrl::fromLocalFile("/Users/narek/Documents/Qt/two_spotify/music.mp3"));
}


MediaPlayer::~MediaPlayer()
{
    delete label;
    delete play_pause;
    delete stop;
    delete audio;
    delete player;
}

void MediaPlayer::handle_stop() {
    player->stop();
    player->setSource(QUrl::fromLocalFile(filePath));
    flag = false;
    play_pause->setText("►");
}

void MediaPlayer::readToFile() {
    QFile inputFile(path);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open input file:" << path;
        return;
    }

    // Specify your desired directory path
    QString outputPath = filePath; // Replace "/your/desired/path/" with your desired directory path

    QFile outputFile(outputPath);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open output file";
        inputFile.close();
        return;
    }

    // Write the contents of the input file to the output file
    QByteArray data = inputFile.readAll();
    outputFile.write(data);

    qDebug() << "File copied successfully. New file name:" << outputPath;

    inputFile.close();
    outputFile.close();
}


// void MediaPlayer::clearFileContents() {
//     // Open the file in WriteOnly mode, clearing its contents
//     QFile file(filePath);
//     if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
//         // File opened successfully, clear its contents
//         file.close();
//         qDebug() << "File cleared successfully:" << filePath;
//     } else {
//         // Failed to open the file
//         qDebug() << "Failed to clear file:" << filePath;
//     }
// }
void MediaPlayer::clearFileContents() {
    std::ofstream file(filePath.toStdString(), std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        std::cout << "File cleared successfully." << std::endl;
        file.close();
    } else {
        std::cerr << "Failed to clear file." << std::endl;
    }
}
