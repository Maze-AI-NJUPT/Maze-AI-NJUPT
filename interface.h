#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QStyleFactory>
#include <QMessageBox>
#include <QApplication>
#include <QMediaPlayer>
class interface : public QWidget
{
    Q_OBJECT
public:
    explicit interface(QWidget *parent = 0);
public:
    QTimer* timer;
    bool isok;
    bool classicalisok;
    QMediaPlayer *BGM;
    QTimer *BGMTimer;
    void showMianMenu();
private:
    QLabel* msgLabel;
    QPushButton* button_classical;
    QPushButton *button_Quit;
    QPushButton *button_About;
    QProgressBar* probar;//进度条
    QPainter* painter;
private:
    void paintEvent(QPaintEvent*);
public slots:
    void classicalStart();
    void loading();
    void Quit();
    void CheckBGMstate();
    void AboutShow();
};

#endif // INTERFACE_H
