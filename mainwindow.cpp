#include "mainwindow.h"
#include "loglist.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>
#include <QFileInfo>
#include <QFile>
#include <QStringRef>
#include <QRegExp>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    counter{0},
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //remove unused tab
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

    //start game
    newChessWindow();

    //add menu bar - new | load | save | delete
    QAction *newChessAction = ui->menuBar->addAction("New");
    connect(newChessAction, SIGNAL(triggered()), this, SLOT(newChessWindow()));

    QAction *loadChessAction = ui->menuBar->addAction("Load");
    connect(loadChessAction, SIGNAL(triggered()), this, SLOT(loadChessWindow()));

    QAction *saveChessAction = ui->menuBar->addAction("Save");
    connect(saveChessAction, SIGNAL(triggered()), this, SLOT(saveChessWindow()));

    QAction *deleteChessAction = ui->menuBar->addAction("Delete");
    connect(deleteChessAction, SIGNAL(triggered()), this, SLOT(deleteChessWindow()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newChessWindow()
{
    counter++;

    QWidget *chessWindowDialog = new ChessWindow(this);
    chessWindowDialog->show();

    ui->tabWidget->addTab(chessWindowDialog, "chess " + QString::number(counter));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::deleteChessWindow()
{
    delete ui->tabWidget->widget(ui->tabWidget->currentIndex());
}


void MainWindow::loadChessWindow()
{
    bool ok;
    QString file = QInputDialog::getText(this, tr("Load"), tr("Enter name of file:"),
                                            QLineEdit::Normal, QString(), &ok);

    QFileInfo check_file(file);
    check_file = check_file.absoluteFilePath();
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile())
    {
        QFile fp(check_file.filePath());
        if (!fp.open(QIODevice::ReadOnly | QIODevice::Text))
                qDebug() << "ERROR: open file";

        // read file
        while (!fp.atEnd())
         {
            QString line = fp.readLine();
            line = line.simplified();  //remove ending white character
            QStringList words = line.split(' ');

            if (words.length() != 3)
            {
                qDebug() << "ERROR: wrong format (missing 3 words in line)";
                continue; // TODO
            }

            QRegExp expr("[1-9][0-9]*.");
            if (!expr.exactMatch(words[0]))
            {
                    qDebug() << "ERROR: first word" << words[0] << "does not match '[1-9][0-9]*.'";
            }


            bool isPawn = true;
            QRegExp expr_pawn("([a-h][1-8]x?[a-h][1-8][K|D|V|S|J]?[#|+]?)");
            QRegExp expr_others("[K|D|V|S|J][a-h][1-8]x?[a-h][1-8][#|+]?)");
            if (!expr_pawn.exactMatch(words[1]))
            {
                    if (!expr_others.exactMatch(words[1]))
                        qDebug() << "ERROR: nd word" << words[1] << "does not match";
                    else
                        isPawn = false;
            }

            if (!isPawn)
            {
                QChar c = words[1][0];
                if (c == 'K')
                    ;
                else if (c == 'D')
                    ;
                else if (c == 'V')
                    ;
                else if (c == 'S')
                    ;
                else if (c == 'J')
                    ;
            }

            if (!expr_pawn.exactMatch(words[2]))
            {
                    qDebug() << "ERROR: rd word" << words[2] << "does not match";
            }

            std::vector<LogList> log;




            //insert --- TODO
            for (auto i = words.begin(); i != words.end(); i++)
            {
                //qDebug() << *i;
                ;
            }
        }
    }
    else
    {
        qDebug() << file << " --- file does not exist!";
    }
}

void MainWindow::saveChessWindow()
{

}
