#ifndef SOCKETGRAPHICSITEM_H
#define SOCKETGRAPHICSITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QString>
#include <QList>
#include <QObject>

template <typename DataType>
class SocketGraphicsItem : public QGraphicsRectItem
{
public:

    enum {
            Type=UserType+1
    };
    explicit SocketGraphicsItem();
    void setList(QList<QString> &classList);
	virtual const DataType& getDetail();
    virtual void setDetail(const DataType& data);
    void setRect(const QRectF &rect);
    void setRect(qreal x, qreal y, qreal w, qreal h);
    int type() const override {
            return Type;
    }
//    void setPos(qreal x, qreal y);
//    void setPos(const QPointF &pos);
     virtual ~SocketGraphicsItem() override;

protected:
	DataType data;
    QGraphicsTextItem textItem;
private:
    QList<QString> classList;
};

#endif // SOCKETGRAPHICSITEM_H
