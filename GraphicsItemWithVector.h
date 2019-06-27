#pragma once
#include "socketgraphicsitem.h"
#include "graphicscene.h"
#include "GraphicsData.h"

class GraphicsItemWithVector :
	public SocketGraphicsItem<GraphicsData>
{
protected:
	GraphicsItemWithVector();
public:
	~GraphicsItemWithVector();
	class CreateItemEvent;
private:
	QGraphicsLineItem vector;
};

class GraphicsItemWithVector::CreateItemEvent : public MouseRectEvent<GraphicScene> {
public:
	enum Step {
		NotInit,
		CreateRect,
		CreateVector
	};
	CreateItemEvent(GraphicScene *scene);
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void stop() override;
private:
	Step step;
	GraphicsItemWithVector *item;
	int startX;
	int startY;
	QColor color;
};