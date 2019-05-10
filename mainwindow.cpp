#include "mainwindow.h"

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

    ChessWindow *chessWindowDialog = new ChessWindow(this);
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
    ChessWindow *currentChess = static_cast<ChessWindow *>(ui->tabWidget->currentWidget());

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
        {
                qDebug() << "ERROR: open file";
                return ;
        }

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

            QRegExp expr_pawn("([a-h][1-8]x?[a-h][1-8][K|D|V|S|J]?[#|+]?)");
            QRegExp expr_others("[K|D|V|S|J][a-h][1-8]x?[a-h][1-8][#|+]?)");

            //move of white player
            bool isPawn = true;
            if (!expr_pawn.exactMatch(words[1]))
            {
                    if (!expr_others.exactMatch(words[1]))
                        qDebug() << "ERROR: nd word" << words[1] << "does not match";
                    else
                        isPawn = false;
            }
            insertToLog(currentChess, words[1], isPawn, true);

            //move of black player
            isPawn = true;
            if (!expr_pawn.exactMatch(words[2]))
            {
                if (!expr_others.exactMatch(words[2]))
                    qDebug() << "ERROR: rd word" << words[2] << "does not match";
                else
                    isPawn = false;
            }
                insertToLog(currentChess, words[2], isPawn, true);
        }
    }
    else
    {
        qDebug() << file << " --- file does not exist!";
    }
}

void MainWindow::insertToLog(ChessWindow *chess, QString str, bool isPawn, bool isWhite)
{
    int x_start;
    int y_start;
    int x_end;
    int y_end;

    State figure = isWhite ? wPawn : bPawn;
    if (!isPawn)
    {
        QChar c = str[0];
        if (c == 'K')
            figure = isWhite ? wKing : bKing;
        else if (c == 'D')
            figure = isWhite ? wQueen : bQueen;
        else if (c == 'V')
            figure = isWhite ? wRook : bRook;
        else if (c == 'S')
            figure = isWhite ? wBishop : bBishop;
        else if (c == 'J')
            figure = isWhite ? wKnight : bKnight;

        str.remove(0, 1);
    }

    //get starting coordinates
    x_start = str[1].toLatin1() - int('a') + 1;
    y_start = str[2].digitValue();

    //check if 'x' is string
    State kick = empty;
    if (str.contains('x'))
    {
        str.remove(3, 1);
        kick = wPawn; //temporary value
    }

    //get end coordinates
    x_end = str[3].toLatin1() - int('a') + 1;
    y_end = str[4].digitValue();

    if (kick != empty)
    {
       ; //TODO
    }

    State swap = empty;
    if (isPawn)
    {
        if (str.length() == 5)
        {
            QChar c = str[5];
            if (c == 'K')
                figure = isWhite ? wKing : bKing;
            else if (c == 'D')
                figure = isWhite ? wQueen : bQueen;
            else if (c == 'V')
                figure = isWhite ? wRook : bRook;
            else if (c == 'S')
                figure = isWhite ? wBishop : bBishop;
            else if (c == 'J')
                figure = isWhite ? wKnight : bKnight;
        }
    }

    chess->log.push_back(new LogList(figure, x_start, y_start, x_end, y_end, kick, swap));
}

void MainWindow::saveChessWindow()
{
    qDebug() << "save()";

    bool ok;
    QString file = QInputDialog::getText(this, tr("Save"), tr("Enter name of file:"),
                                            QLineEdit::Normal, QString(), &ok);

    QFileInfo check_file(file);
    check_file = check_file.absoluteFilePath();

    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile())
    {
        QFile fp(check_file.filePath());
        if (!fp.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug() << "ERROR: open file";  //TODO
            return ;
        }

        QWidget *current = ui->tabWidget->currentWidget();
        QTextEdit *line = current->findChild<QTextEdit *> ("log");

        if (line != nullptr)
        {
            QTextStream stream(&fp);
            stream << line->toPlainText();
            fp.flush();
            fp.close();
        }
        else
            qDebug() << "Internal Error!"; //TODO
    }
    else
    {
        qDebug() << file << " --- file does not exist!"; //TODO
    }
}
