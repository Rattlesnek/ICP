/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

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

    /*QAction *saveChessAction = ui->menuBar->addAction("Save");
    connect(saveChessAction, SIGNAL(triggered()), this, SLOT(saveChessWindow()));
*/
    QAction *deleteChessAction = ui->menuBar->addAction("Delete");
    connect(deleteChessAction, SIGNAL(triggered()), this, SLOT(deleteChessWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorMessage(QString error)
{
    QMessageBox messageBox;
    messageBox.critical(nullptr, "Error massage", error);
    messageBox.setFixedSize(500,200);
}

void MainWindow::newChessWindow()
{
    counter++; //increase total number of chess window

    std::vector<LogList> log;
    ChessWindow *chessWindowDialog = new ChessWindow(log, this);
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
    counter++; //increase total number of chess window

    std::vector<LogList> log;
    bool ok;
    QString file = QInputDialog::getText(this, tr("Load"), tr("Enter name of file:"),
                                            QLineEdit::Normal, QString(), &ok);
\
    if (file == "") return ;

    QFileInfo check_file(file);
    check_file = check_file.absoluteFilePath();
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile())
    {
        QFile fp(check_file.filePath());
        if (!fp.open(QIODevice::ReadOnly | QIODevice::Text))
        {
                errorMessage("open file: " + check_file.filePath());
                return ;
        }

        int line_counter = 1;
        // read file
        while (!fp.atEnd())
        {
            QString line = fp.readLine();
            line = line.simplified();  //remove ending white character
            QStringList words = line.split(' ');

            if (words.length() != 3)
            {
                errorMessage("wrong format (except 3 words in every line), line: " + QString::number(line_counter));
                return ;
            }

            QRegExp expr("[1-9][0-9]*."); //TODO --- check if it increase and nothing missing
            if (!expr.exactMatch(words[0]))
            {
                errorMessage("first word does not match, line: " + QString::number(line_counter));
                return ;
            }

            //move of white player
            switch (stringVersion(words[1]))
            {
            case 0:
                insertLongToLog(log, words[1], true, true);
                break;
            case 1:
                insertLongToLog(log, words[1], false, true);
                break;
            case 2:
                insertShortToLog(log, words[1], true, true);
                break;
            case 3:
                insertShortToLog(log, words[1], false, true);
                break;
            default:
                errorMessage("second word does not match, line: " + QString::number(line_counter));
                return ;
            }

            //move of black player
            switch (stringVersion(words[2]))
            {
            case 0:
                insertLongToLog(log, words[2], true, false);
                break;
            case 1:
                insertLongToLog(log, words[2], false, false);
                break;
            case 2:
                insertShortToLog(log, words[2], true, false);
                break;
            case 3:
                insertShortToLog(log, words[2], false, false);
                break;
            default:
                errorMessage("third word does not match, line: " + QString::number(line_counter));
                return ;
            }
            line_counter++;
        }
        fp.close();
    }
    else
    {
        errorMessage("file: " + check_file.filePath() + " does not exist");
        return ;
    }

    ChessWindow *chessWindowDialog = new ChessWindow(log, this);
    chessWindowDialog->show();

    ui->tabWidget->addTab(chessWindowDialog, "chess " + QString::number(counter));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

int MainWindow::stringVersion(QString s)
{
    QRegExp long_expr_pawn("([a-h][1-8]x?[a-h][1-8][K|D|V|S|J]?[#|+]?)");
    QRegExp long_expr_others("([K|D|V|S|J][a-h][1-8]x?[a-h][1-8][#|+]?)");

    if (long_expr_pawn.exactMatch(s))
        return 0;
    if (long_expr_others.exactMatch(s))
        return 1;

    QRegExp short_expr_pawn("([1-8]|[a-h])?x?[a-h][1-8][K|D|V|S|J]?[#|+]?");
    QRegExp short_expr_others("[K|D|V|S|J]([1-8]|[a-h])?x?[a-h][1-8][#|+]?");
    if (short_expr_pawn.exactMatch(s))
        return 2;
    if (short_expr_others.exactMatch(s))
        return 3;

    return FAIL;
}


void MainWindow::insertLongToLog(std::vector<LogList> &log, QString str, bool isPawn, bool isWhite)
{
    int x_start, y_start, x_end, y_end;

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
    x_start = str[0].toLatin1() - int('a') + 1;
    y_start = str[1].digitValue();

    //check if 'x' is string
    State kick = empty;
    if (str.contains('x'))
    {
        str.remove(2, 1);
        kick = wPawn; //temporary value
    }

    //get end coordinates
    x_end = str[2].toLatin1() - int('a') + 1;
    y_end = str[3].digitValue();

    State swap = empty;
    if (isPawn)
    {
        QRegExp swap_expr("[K|D|V|S|J][+|#]?");
        if (swap_expr.exactMatch(str.mid(4, str.length())))
        {
            QChar c = str[4];
            if (c == 'K')
                swap = isWhite ? wKing : bKing;
            else if (c == 'D')
                swap = isWhite ? wQueen : bQueen;
            else if (c == 'V')
                swap = isWhite ? wRook : bRook;
            else if (c == 'S')
                swap = isWhite ? wBishop : bBishop;
            else if (c == 'J')
                swap = isWhite ? wKnight : bKnight;
        }
    }

    log.push_back(LogList(figure, y_start, x_start, y_end, x_end, kick, swap));
}

void MainWindow::insertShortToLog(std::vector<LogList> &log, QString str, bool isPawn, bool isWhite)
{
    int x_start = 0, y_start = 0, x_end, y_end; //0 means uknown

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

    //check if the log string has hint
    QRegExp hint("([a-h]|[1-8])[a-h][1-8]");
    if (hint.exactMatch(str.mid(0,3)))
    {
        if (str[0].isDigit())
            y_start = str[0].digitValue();
        else
            x_start = str[0].toLatin1() - int('a') + 1;

        str.remove(0, 1);
    }

    //check if 'x' is string
    if (str.contains('x'))
        str.remove(0, 1);

    qDebug() << str;

    //get end coordinates
    x_end = str[0].toLatin1() - int('a') + 1;
    y_end = str[1].digitValue();

    qDebug() << y_end << x_end;

    State swap = empty;
    if (isPawn)
    {
        QRegExp swap_expr("[K|D|V|S|J][+|#]?");
        if (swap_expr.exactMatch(str.mid(3, str.length())))
        {
            QChar c = str[3];
            if (c == 'K')
                swap = isWhite ? wKing : bKing;
            else if (c == 'D')
                swap = isWhite ? wQueen : bQueen;
            else if (c == 'V')
                swap = isWhite ? wRook : bRook;
            else if (c == 'S')
                swap = isWhite ? wBishop : bBishop;
            else if (c == 'J')
                swap = isWhite ? wKnight : bKnight;
        }
    }

    log.push_back(LogList(figure, y_start, x_start, y_end, x_end, empty, swap));
}

/*void MainWindow::saveChessWindow()
{
    bool ok;
    QString file = QInputDialog::getText(this, tr("Save"), tr("Enter name of file:"),
                                            QLineEdit::Normal, QString(), &ok);
    if (file == "") return ;

    QFileInfo check_file(file);
    check_file = check_file.absoluteFilePath();

    if (check_file.exists())
    {
        if (!check_file.isFile())
        {
            errorMessage("excepted file, given directory");
            return ;
        }
    }

    QFile fp(check_file.filePath());
    if (!fp.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        errorMessage("cannot open file:" + check_file.filePath());
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
            qDebug() << "Internal Error!"; //probably never happaned
}
*/
