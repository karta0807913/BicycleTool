#include "socketgraphicsitem.h"
#include "GraphicsData.h"

template<typename DataType>
SocketGraphicsItem<DataType>::SocketGraphicsItem() :
   QGraphicsRectItem(nullptr), data()
{
    textItem.setParentItem(this);
}

template<typename DataType>
void SocketGraphicsItem<DataType>::setList(QList<QString> &classList)
{
    if(classList.count() == 1)
        textItem.setPlainText(classList[0]);
    else
        textItem.setPlainText("");
    this->classList = classList;
}

template<typename DataType>
const DataType & SocketGraphicsItem<DataType>::getDetail()
{
	return data;
}

template<typename DataType>
void SocketGraphicsItem<DataType>::setRect(const QRectF &rect)
{
    textItem.setPos(rect.x(), rect.y());
    QGraphicsRectItem::setRect(rect);
}

template<typename DataType>
void SocketGraphicsItem<DataType>::setRect(qreal x, qreal y, qreal w, qreal h)
{
    textItem.setPos(x, y);
    QGraphicsRectItem::setRect(x, y, w, h);
}

template<typename DataType>
SocketGraphicsItem<DataType>::~SocketGraphicsItem()
{
}

//void SocketGraphicsItem::setPos(const QPointF &pos)
//{
//    textItem.setPos(pos.x(), pos.y());
//    QGraphicsRectItem::setPos(pos);
//}

//void SocketGraphicsItem::setPos(qreal x, qreal y)
//{
//    textItem.setPos(x, y);
//    QGraphicsRectItem::setPos(x, y);
//}

template class SocketGraphicsItem<GraphicsData>;