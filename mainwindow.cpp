#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_w_hook = new HookedImageSave();
    m_w_select = new ModelServerSelector();

    m_w_dedit = new DataEditWindow(nullptr);
    m_w_canvas = new Cavas();

    ui->horizontalLayout->addWidget(m_w_canvas, 2);
    ui->horizontalLayout->addWidget(m_w_dedit, 1);

    connect(ui->actionhook, &QAction::triggered, this, [=](){m_w_hook->show();});
    connect(ui->actionselect, &QAction::triggered,this, [=](){m_w_select->show();});
    connect(m_w_dedit, SIGNAL(dock_to()), this, SLOT(edit_lay_change()));
    connect(this, SIGNAL(fix_ret_form_size()), m_w_dedit, SLOT(fix_form_size()), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_w_hook)  m_w_hook->deleteLater();
    if(m_w_select) m_w_select->deleteLater();
    if(m_w_dedit) m_w_dedit->deleteLater();
}

void MainWindow::edit_lay_change()
{
    if(m_w_dedit->parent() == nullptr){
        ui->horizontalLayout->addWidget(m_w_dedit, 1);
    }else{
        ui->horizontalLayout->removeWidget(m_w_dedit);
        m_w_dedit->setParent(nullptr);
        m_w_dedit->show();
        emit fix_ret_form_size();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_w_dedit){
        delete m_w_dedit;
        m_w_dedit = nullptr;
    }
    event->accept();
}
