#include "cavas.h"
#include "ui_cavas.h"

Cavas::Cavas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cavas)
{
    ui->setupUi(this);
}

Cavas::~Cavas()
{
    delete ui;
}

void Cavas::resizeEvent(QResizeEvent *event){
    event->accept();
}
