#pragma once
#include "socketgraphicsitem.h"
#include "graphicscene.h"
#include "DataType.pb.h"

class GraphicsItemWithVector :
	public SocketGraphicsItem<DataType::RectData>
{
protected:
	GraphicsItemWithVector();
public:
	~GraphicsItemWithVector();
    const DataType::RectData& getDetail() override;
    void setDetail(const DataType::RectData& data) override;
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
    void createItemFromRectData(const DataType::RectData& data);
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
