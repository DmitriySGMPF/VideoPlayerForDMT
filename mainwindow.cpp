#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    this->setCentralWidget(vw);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);

    status_video_time = new QLabel;
    status_video_time->setText("00:00");

    ui->toolBar->addWidget(slider);
    ui->toolBar->addWidget(status_video_time);
    ui->toolBar->setMovable(false);
    ShowActionsPlayPause(false);

    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::SetSliderTimePosition);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Открыть файл", "", "");
    on_actionStop_triggered();

    player->setMedia(QUrl::fromLocalFile(filename));

    on_actionPlay_triggered();
}

void MainWindow::SetSliderTimePosition(qint64 position)
{
    slider->setValue(position);
    SetStatusVideoTime();
}

void MainWindow::ShowActionsPlayPause(bool flag)
{
    QList<QAction*>  list_actions;
    list_actions = ui->toolBar->actions();
    if(flag)
    {
        list_actions[0]->setVisible(false);
        list_actions[1]->setVisible(true);
    }
    else
    {
        list_actions[0]->setVisible(true);
        list_actions[1]->setVisible(false);
    }
}

void MainWindow::SetStatusVideoTime()
{
    const qint64 currentInfo = player->position() / 1000;
    const qint64 duration = player->duration() / 1000;
    QString tStr;

    if (currentInfo)
    {
        QTime currentTime((currentInfo / 3600) %60,
                          (currentInfo / 60) % 60,
                          (currentInfo % 60),
                          (currentInfo * 1000) % 1000);
        QTime totalTime((duration / 3600) % 60,
                        (duration / 60) % 60,
                        (duration % 60),
                        (duration * 1000) % 1000);
        QString format = "mm:ss";

        if (duration > 3600)
            format = "hh:mm:ss";

        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }

    status_video_time->setText(tStr);

}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
    ShowActionsPlayPause(true);
}


void MainWindow::on_actionPause_triggered()
{
    player->pause();
    ShowActionsPlayPause(false);
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ShowActionsPlayPause(false);
}


