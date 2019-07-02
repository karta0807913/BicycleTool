#include <fstream>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseRectEvent.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	create = new CreateSocketGraphicsItem<GraphicScene, DataType::RectData>(ui->widget->getMainScene());
	resize = new ResizeGraphicsItem<GraphicScene, DataType::RectData>(ui->widget->getMainScene());
	move = new MouseRectEvent<GraphicScene>(ui->widget->getMainScene());
	createGV = new GraphicsItemWithVector::CreateItemEvent(ui->widget->getMainScene());
	//connect(ui->actionArror, SIGNAL(triggered()), this, SLOT(setSelectMode()));
	//connect(ui->actionScaling, SIGNAL(triggered()), this, SLOT(setResizeMode()));

	connect(ui->drawButton, SIGNAL(clicked()), this, SLOT(createMode()));
	connect(ui->moveButton, SIGNAL(clicked()), this, SLOT(moveMode()));
	connect(ui->changeImage, SIGNAL(clicked()), this, SLOT(changeImage()));
	connect(ui->saveSetting, SIGNAL(clicked()), this, SLOT(saveSetting()));
	connect(ui->loadSetting, SIGNAL(clicked()), this, SLOT(loadSetting()));
	connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear()));
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

void MainWindow::saveSetting() {
    std::fstream fs ("./setting.proto", std::fstream::out);
    if(fs.is_open()) {
        DataType::GlobalData screen;
        QRectF screen_rect = ui->widget->rect();
        screen.set_screen_w(screen_rect.width());
        screen.set_screen_h(screen_rect.height());
        foreach(QGraphicsItem *item, ui->widget->items()) {
            if (SocketGraphicsItem<DataType::RectData>::Type == item->type()) {
                SocketGraphicsItem<DataType::RectData> *sitem = (SocketGraphicsItem<DataType::RectData>*)item;
                auto rect = screen.add_rect();
                auto data = sitem->getDetail();
                rect->CopyFrom(data);
                cout << rect->x() << " ";
                cout << rect->y() << " ";
                cout << rect->w() << " ";
                cout << rect->h() << " ";
                cout << rect->dx() << " ";
                cout << rect->dy() << endl;
            }
        }
        screen.SerializeToOstream(&fs);
    }
}

void MainWindow::loadSetting() {
    std::fstream fs ("./setting.proto", std::fstream::in);
    if(fs.is_open()) {
        DataType::GlobalData screen;
        screen.ParseFromIstream(&fs);
        auto rect = screen.rect();
        for(auto iter = rect.begin(); iter != rect.end(); ++iter) {
            createGV->createItemFromRectData(*iter);
            cout << iter->x() << " ";
            cout << iter->y() << " ";
            cout << iter->w() << " ";
            cout << iter->h() << " ";
            cout << iter->dx() << " ";
            cout << iter->dy() << endl;
        }
    }
}

void MainWindow::clear() {
    ui->widget->deleteAllItems();
}
