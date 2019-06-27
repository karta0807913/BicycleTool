#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseRectEvent.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	create = new CreateSocketGraphicsItem<GraphicScene, GraphicsData>(ui->widget->getMainScene());
	resize = new ResizeGraphicsItem<GraphicScene, GraphicsData>(ui->widget->getMainScene());
	move = new MouseRectEvent<GraphicScene>(ui->widget->getMainScene());
	createGV = new GraphicsItemWithVector::CreateItemEvent(ui->widget->getMainScene());
	//connect(ui->actionArror, SIGNAL(triggered()), this, SLOT(setSelectMode()));
	//connect(ui->actionScaling, SIGNAL(triggered()), this, SLOT(setResizeMode()));

	connect(ui->drawButton, SIGNAL(clicked()), this, SLOT(createMode()));
	connect(ui->moveButton, SIGNAL(clicked()), this, SLOT(moveMode()));
	connect(ui->changeImage, SIGNAL(clicked()), this, SLOT(changeImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeImage()
{
    this->ui->widget->setImage("D:\\pic\\5fd2b030gw1fbo5iczkm7j21hc0u0qg6.jpg");
}

void MainWindow::createMode() {
	ui->widget->setSelectable(false);
	ui->widget->setSelectMode(createGV);
}

void MainWindow::moveMode() {
	ui->widget->setSelectable(true);
	ui->widget->setSelectMode(move);
}