#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QObject>
#include <QGraphicsRectItem>

class FieldView : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    FieldView();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalFieldPressed(int x, int y);

};

#endif // FIELDVIEW_H
