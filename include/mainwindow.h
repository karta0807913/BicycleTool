#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphicscene.h"
#include "GraphicsItemWithVector.h"
#include "DataType.pb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

	CreateSocketGraphicsItem<GraphicScene, DataType::RectData> * create;
	ResizeGraphicsItem<GraphicScene, DataType::RectData> *resize;
	MouseRectEvent<GraphicScene> *move;
	GraphicsItemWithVector::CreateItemEvent *createGV;

public slots:
	void createMode();
	void moveMode();
	void changeImage();
    void saveSetting();
    void loadSetting();
    void clear();
};

#endif // MAINWINDOW_H
