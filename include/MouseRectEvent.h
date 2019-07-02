#pragma once
#include "graphicscene.h"
#include "socketgraphicsitem.h"

template<typename Scene>
class MouseRectEvent {
public:
	MouseRectEvent(Scene *scene): scene(scene){
	}

	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) {
	}

	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	}

	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	}

	virtual void stop() {
	}

protected:
	Scene *scene;
};

template<typename Scene, typename DataType>
class CreateSocketGraphicsItem : public MouseRectEvent<Scene> {
public:
	CreateSocketGraphicsItem(Scene *scene) : MouseRectEvent<Scene>(scene) {
		obj = nullptr;
	}

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override  {
		obj = new SocketGraphicsItem<DataType>();
		QList<QString> classList = this->scene->getPlotClassesList();
		this->scene->addItem(obj);
		QColor color = this->scene->getDrawColor();
		color.setAlpha(25);
		obj->setBrush(color);
		color.setAlpha(255);
		obj->setPen(QPen(color, 1));

		startX = event->scenePos().x();
		startY = event->scenePos().y();

		obj->setRect(event->scenePos().x(), event->scenePos().y(), 0, 0);
	}

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
		if (obj == nullptr)
			return;

		int x, y, w, h;

		x = (event->scenePos().x() > startX) ? startX : event->scenePos().x();
		y = (event->scenePos().y() > startY) ? startY : event->scenePos().y();

		w = ((int)event->scenePos().x() ^ startX ^ x) - x;
		h = ((int)event->scenePos().y() ^ startY ^ y) - y;

		obj->setRect(x, y, w, h);
	}

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
		if (obj == nullptr)
			return;
		if (obj->rect().width() < 10 && obj->rect().height() < 10)
			this->scene->deleteItem(obj);
		obj = nullptr;
	}

	void stop() {
		if (obj != nullptr) {
			this->scene->deleteItem(obj);
		}
	}

protected:
	SocketGraphicsItem<DataType> *obj;
	int startX;
	int startY;
};

template<typename Scene, typename DataType>
class ResizeGraphicsItem : public MouseRectEvent<Scene> {
private:
	QGraphicsRectItem *controlItems[4] = { nullptr };
	int originPosX;
	int originPosY;
	int originRectHeight;
	int originRectWidth;

public:
	ResizeGraphicsItem(Scene *scene) : MouseRectEvent<Scene>(scene) {
	}

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
		QList<QGraphicsItem*> itemList = this->scene->selectedItems();
		int childWidth = 20;
		int childHeight = 20;
		if (itemList.count() == 0)
		{
			this->scene->setSelectable(true);
			if (controlItems[0] != nullptr)
				for (int index = 0; index < 4; ++index)
				{
					delete controlItems[index];
					controlItems[index] = nullptr;
				}
		}
		else
		{
			if (controlItems[0] == nullptr)
			{
				QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem *>(itemList[0]);
				QRectF parentRect = rectItem->rect();

				this->scene->setSelectable(false);

				for (int index = 0; index < 4; ++index)
				{
					controlItems[index] = new QGraphicsRectItem(rectItem);
					controlItems[index]->setBrush(Qt::black);
					controlItems[index]->setFlag(QGraphicsItem::ItemIsSelectable, true);
					controlItems[index]->setFlag(QGraphicsItem::ItemIsMovable, true);
				}

				controlItems[0]->setRect(parentRect.x() - childWidth / 2, parentRect.y() - childHeight / 2, childWidth, childHeight);
				controlItems[1]->setRect(parentRect.x() - childWidth / 2, parentRect.y() - childHeight / 2 + parentRect.height(), childWidth, childHeight);
				controlItems[2]->setRect(parentRect.x() - childWidth / 2 + parentRect.width(), parentRect.y() - childHeight / 2, childWidth, childHeight);
				controlItems[3]->setRect(parentRect.x() - childWidth / 2 + parentRect.width(), parentRect.y() - childHeight / 2 + parentRect.height(), childWidth, childHeight);

				originPosX = parentRect.x();
				originPosY = parentRect.y();
				originRectHeight = parentRect.height();
				originRectWidth = parentRect.width();
			}
		}
	}

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {

		if (controlItems[0] == nullptr)
			return;

		/*0**********2
		  *          *
		  *          *
		  *          *
		  *          *
		  *          *
		  *          *
		  1**********3*/

		if (controlItems[0]->isSelected())
		{
			controlItems[1]->setPos(controlItems[0]->pos().x(), controlItems[1]->pos().y());
			controlItems[2]->setPos(controlItems[2]->pos().x(), controlItems[0]->pos().y());
		}
		else if (controlItems[1]->isSelected())
		{
			controlItems[0]->setPos(controlItems[1]->pos().x(), controlItems[0]->pos().y());
			controlItems[3]->setPos(controlItems[3]->pos().x(), controlItems[1]->pos().y());
		}
		else if (controlItems[2]->isSelected())
		{
			controlItems[0]->setPos(controlItems[0]->pos().x(), controlItems[2]->pos().y());
			controlItems[3]->setPos(controlItems[2]->pos().x(), controlItems[3]->pos().y());
		}
		else if (controlItems[3]->isSelected())
		{
			controlItems[1]->setPos(controlItems[1]->pos().x(), controlItems[3]->pos().y());
			controlItems[2]->setPos(controlItems[3]->pos().x(), controlItems[2]->pos().y());
		}

		QGraphicsRectItem *parentItem = static_cast<QGraphicsRectItem*>(controlItems[0]->parentItem());
		parentItem->setRect(originPosX + controlItems[0]->pos().x(), originPosY + controlItems[0]->pos().y(),
			originRectWidth - controlItems[0]->pos().x() + controlItems[3]->pos().x(),
			originRectHeight - controlItems[0]->pos().y() + controlItems[3]->pos().y());
	}

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
	}

	void stop() {
		if (controlItems[0] != nullptr) {
			for (int index = 0; index < 4; ++index)
			{
				delete controlItems[index];
				controlItems[index] = nullptr;
			}
		}
	}
};

// template<typename Scene, typename DataType>
// class MoveGraphicsItem : public MouseRectEvent<Scene> {
// 	MoveGraphicsItem(Scene *scene) : MouseRectEvent(scene) {
// 	}
// 
// 	void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
// 	}
// 
// 	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
// 	}
// 
// 	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
// 	}
// 
// 	void stop() override {
// 	}
// };
