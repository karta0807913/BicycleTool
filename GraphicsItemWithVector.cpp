#include "GraphicsItemWithVector.h"

GraphicsItemWithVector::GraphicsItemWithVector()
{
	vector.setParentItem(this);
}


GraphicsItemWithVector::~GraphicsItemWithVector()
{
}

GraphicsItemWithVector::CreateItemEvent::CreateItemEvent(GraphicScene * scene) : MouseRectEvent<GraphicScene>(scene)
{
	this->step = NotInit;
	this->item = nullptr;
}

void GraphicsItemWithVector::CreateItemEvent::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	switch (this->step) {
	case NotInit:
		this->item = new GraphicsItemWithVector();
		this->scene->addItem(this->item);
		color = this->scene->getDrawColor();
		color.setAlpha(25);
		this->item->setBrush(color);
		color.setAlpha(255);
		this->item->setPen(QPen(color, 1));
		
		startX = event->scenePos().x();
		startY = event->scenePos().y();
		
		this->item->setRect(event->scenePos().x(), event->scenePos().y(), 0, 0);
		this->step = CreateRect;
		return;
	case CreateVector:
		this->item->vector.setLine(startX, startY, event->scenePos().x(), event->scenePos().y());
		this->item = nullptr;
		this->step = NotInit;
		return;
	}
}

void GraphicsItemWithVector::CreateItemEvent::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	if (this->item == nullptr)
		return;
	switch (this->step) {
	case CreateRect:
		
		int x, y, w, h;
		
		x = (event->scenePos().x() > startX) ? startX : event->scenePos().x();
		y = (event->scenePos().y() > startY) ? startY : event->scenePos().y();
		
		w = ((int)event->scenePos().x() ^ startX ^ x) - x;
		h = ((int)event->scenePos().y() ^ startY ^ y) - y;
		
		this->item->setRect(x, y, w, h);
		return;
	case CreateVector:
		this->item->vector.setLine(startX, startY, event->scenePos().x(), event->scenePos().y());
		return;
	}
}

void GraphicsItemWithVector::CreateItemEvent::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	if (this->item == nullptr)
		return;
	switch (this->step) {
	case CreateRect:
		if (this->item->rect().width() < 10 && this->item->rect().height() < 10) {
			this->scene->deleteItem(this->item);
			this->step = NotInit;
			this->item = nullptr;
			return;
		}
		this->step = CreateVector;
		color.setAlpha(255);
		this->item->vector.setPen(color);
		startX = this->item->rect().x() + this->item->rect().width() / 2;
		startY = this->item->rect().y() + this->item->rect().height() / 2;
		return;
	case CreateVector:
		return;
	}
}

void GraphicsItemWithVector::CreateItemEvent::stop()
{
	if (this->item != nullptr) {
		this->scene->deleteItem(this->item);
	}
}
