#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QRect>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include "socketgraphicsitem.h"
#include <QTextStream>
#include <QColor>
#include <QGraphicsItem>

#include "graphicscene.h"

#include "MouseRectEvent.h"
#include "DataType.pb.h"

namespace Ui {
class GraphicWidget;
}

class GraphicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicWidget(QWidget *parent = 0);
    void setGeometry(const QRect &rect);
    void setImage(QString path);
    void setImage(cv::Mat img);
    void addItem(SocketGraphicsItem<DataType::RectData> *item);
    void addRectItem(float x1, float y1, float x2, float y2, QColor color, QList<QString> &classList);
    void setSelectMode(MouseRectEvent<GraphicScene> *functor);
    void setSelectable(bool state);
    void deleteAllItems();
    void update();
    void setRectInfo(QColor color, QList<QString> &classList);
    void setDeleteHotKey(Qt::Key key);
    void setMultiClassesList(QList<QString> classesList);
    QList<QGraphicsItem *> items();
    QList<QGraphicsItem *> selectItems();
    QList<QString> getMultiClassesList();
    GraphicScene *getMainScene();
    cv::Mat &getOriginImage();

    void changeRectItemColor(SocketGraphicsItem<DataType::RectData> *rectItem, QColor color);
    void mouseReleaseEvent(QMouseEvent *event);

    ~GraphicWidget();
signals:
    void itemNumberChanged(int);
private:
    Ui::GraphicWidget *ui;
    MouseRectEvent<GraphicScene> *empty;
    GraphicScene *scene;
    QWidget *parent;
    int imgWidth;
    int imgHeight;
};

#endif // GRAPHICWIDGET_H
