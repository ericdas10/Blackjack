#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTableWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCardGenerate();
    void onRevealCard();

private:
    QTableWidget *cardTableWidget;
    QSlider *cardSlider;
    QPushButton *generateButton;
    QPushButton *revealButton;
    QVector<int> cardValues;
    QVector<int> drawnCardValues;
    int currentScore;
    int currentCardIndex;

    void initializeGame();
    void checkGameStatus();
    void generateCard();
    void revealCard(int index);
};

#endif // MAINWINDOW_H
