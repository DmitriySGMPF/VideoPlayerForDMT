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


    //QWidget *container = new QWidget;

    slider = new QSlider(this);

    //h_layout = new QHBoxLayout(container);

    //h_layout->addWidget(slider);
    slider->setOrientation(Qt::Horizontal);

    //ui->statusbar->setLayout(h_layout);
    ui->toolBar->addWidget(slider);
    ui->toolBar->setMovable(false);

    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    //connect(player, &QMediaPlayer::durationChanged, bar, &QProgressBar::setMaximum);
    //connect(player, &QMediaPlayer::positionChanged, bar, &QProgressBar::setValue);
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

void MainWindow::on_actionPlay_triggered()
{
    player->play();
    //ui->toolBar->addAction()
    //ui->statusbar->showMessage("PLAYlsdfnkudsjislajdnfku,ijskdlafvdnsdadvfdas");
}


void MainWindow::on_actionPause_triggered()
{
    player->pause();
    //ui->statusbar->showMessage("PAUSE");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    //ui->statusbar->showMessage("STOP");
}


