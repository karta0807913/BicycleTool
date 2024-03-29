#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#define DONT_SCALE_IMAGE

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QString>
#include <QPoint>
#include <opencv2/opencv.hpp>
#include <QGraphicsSceneMouseEvent>
#include "socketgraphicsitem.h"
#include <QWidget>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QAction>
#include <map>
#include <QColor>
#include <QObject>

#include "MouseRectEvent.h"
#include "DataType.pb.h"

template<typename W, typename H>
struct Size
{
    W height;
    H width;
};

class GraphicScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicScene(QWidget *parent = nullptr, MouseRectEvent<GraphicScene> *functor = nullptr);
    void setImage(QString path, int height, int width);
    void setImage(cv::Mat &img, int height, int width);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void setSelectable(bool state);
    void deleteAllItems();
    void keyPressEvent(QKeyEvent *event);
    void setSelectMode(MouseRectEvent<GraphicScene> *functor);
    Size<float, float> getScalingRate();
    void setRectInfo(QColor color, QList<QString> &classList);
    void setDeleteHotKey(Qt::Key key);
    cv::Mat &getOriginImage();
    void addItem(QGraphicsItem *item);
	void addItem(SocketGraphicsItem<DataType::RectData> *item);
    bool deleteItem(QGraphicsItem *item);
    QList<QString> getPlotClassesList();
    int getGraphicItemsNum();
	QColor getDrawColor();
    ~GraphicScene();

private:
    Qt::Key deleteHotKey;
    QGraphicsPixmapItem pixmapItem;
    QGraphicsLineItem auxiliiaryLine_X;
    QGraphicsLineItem auxiliiaryLine_Y;
    cv::Mat originImg;
    QPixmap displayImg;
    MouseRectEvent<GraphicScene> *mouseEvent;
    Size<float, float> scalingRate;
    QList<QString> rectClassList;
    QColor rectColor;
    int graphicItemNum;

    int itemCounter = 0;

    QColor MultiClassColor;
};

#endif // GRAPHICSCENE_H
