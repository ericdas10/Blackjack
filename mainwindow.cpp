#include "mainwindow.h"
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , currentScore(0)
        , currentCardIndex(0)
{
    // Initialize UI components
    cardTableWidget = new QTableWidget(this);
    cardTableWidget->setColumnCount(1);
    cardTableWidget->setHorizontalHeaderLabels({"Cards"});
    cardTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    cardSlider = new QSlider(Qt::Horizontal, this);
    generateButton = new QPushButton("Generate Cards", this);
    revealButton = new QPushButton("Reveal Card", this);

    cardSlider->setRange(1, 13);
    cardSlider->setTickInterval(1);
    cardSlider->setTickPosition(QSlider::TicksBelow);

    // Set up the layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(cardSlider);
    //sliderLayout->addWidget(new QLabel("Number of cards"));

    mainLayout->addLayout(sliderLayout);
    mainLayout->addWidget(generateButton);
    mainLayout->addWidget(revealButton);
    mainLayout->addWidget(cardTableWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(generateButton, &QPushButton::clicked, this, &MainWindow::onCardGenerate);
    connect(revealButton, &QPushButton::clicked, this, &MainWindow::onRevealCard);

    initializeGame();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeGame()
{
    cardValues = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    drawnCardValues.clear();
    currentScore = 0;
    currentCardIndex = 0;
    cardTableWidget->setRowCount(0);
}

void MainWindow::onCardGenerate()
{
    int numCards = cardSlider->value();
    for (int i = 0; i < numCards; ++i) {
        generateCard();
    }
}

void MainWindow::onRevealCard()
{
    if (currentCardIndex < drawnCardValues.size()) {
        revealCard(currentCardIndex);
        currentCardIndex++;
        checkGameStatus();
    }
}

void MainWindow::generateCard()
{
    int cardIndex = rand() % 13;
    int cardValue = cardValues[cardIndex];
    drawnCardValues.append(cardValue);

    int row = cardTableWidget->rowCount();
    cardTableWidget->insertRow(row);
    cardTableWidget->setItem(row, 0, new QTableWidgetItem("X"));
}

void MainWindow::revealCard(int index)
{
    if (index < drawnCardValues.size()) {
        int cardValue = drawnCardValues[index];
        currentScore += cardValue;

        QString cardText;
        if (cardValue == 10 && (index == 9 || index == 10 || index == 11)) {
            if (index == 9) cardText = "J";
            else if (index == 10) cardText = "Q";
            else if (index == 11) cardText = "K";
        } else if (cardValue == 11) {
            cardText = "A";
        } else {
            cardText = QString::number(cardValue);
        }

        cardTableWidget->setItem(index, 0, new QTableWidgetItem(cardText));
    }
}

void MainWindow::checkGameStatus()
{
    if (currentScore == 21) {
        QMessageBox::information(this, "Game Status", "You're on fire!");
        initializeGame();
    } else if (currentScore > 21) {
        QMessageBox::information(this, "Game Status", "You busted...");
        initializeGame();
    }
}
