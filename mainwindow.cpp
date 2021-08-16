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

    ui->toolBar->addWidget(slider);
    ui->toolBar->setMovable(false);
    ShowActionsPlayPause(false);

    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
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

    //slider->setTickPosition(QSlider::TicksLeft);
}


