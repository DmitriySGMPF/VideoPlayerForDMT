#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>

#include <QToolBar>
#include <QAction>
#include <QList>

#include <QTime>
#include <QLabel>

#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_actionOpen_triggered();

    void SetSliderTimePosition(qint64 position);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *vw;
    QProgressBar *bar;
    QSlider *slider;
    QLabel *status_video_time;

    // Functions

    void ShowActionsPlayPause(bool flag);

    void SetStatusVideoTime();

};
#endif // MAINWINDOW_H
