#ifndef SOCKETGRAPHICSITEM_H
#define SOCKETGRAPHICSITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QString>
#include <QList>
#include <QObject>

#include "GraphicsData.h"

template <typename DataType>
class SocketGraphicsItem : public QGraphicsRectItem
{
public:

    enum {
            Type=UserType+1
    };
    explicit SocketGraphicsItem();
    void setList(QList<QString> &classList);
	const DataType& getDetail();
    void setRect(const QRectF &rect);
    void setRect(qreal x, qreal y, qreal w, qreal h);
    int type() const override {
            return Type;
    }
//    void setPos(qreal x, qreal y);
//    void setPos(const QPointF &pos);
     ~SocketGraphicsItem() override;

private:
    QList<QString> classList;
    QGraphicsTextItem textItem;
	DataType data;
};

#endif // SOCKETGRAPHICSITEM_H
