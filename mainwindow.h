#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphicscene.h"
#include "GraphicsData.h"
#include "GraphicsItemWithVector.h"

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

	CreateSocketGraphicsItem<GraphicScene, GraphicsData> * create;
	ResizeGraphicsItem<GraphicScene, GraphicsData> *resize;
	MouseRectEvent<GraphicScene> *move;
	GraphicsItemWithVector::CreateItemEvent *createGV;

public slots:
	void createMode();
	void moveMode();
	void changeImage();
};

#endif // MAINWINDOW_H
