#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Game* game = new Game();
    connection = new Connection(game);
}

Widget::~Widget()
{
    delete ui;
}

