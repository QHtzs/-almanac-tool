#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

#include "widgets/hookedimagesave.h"
#include "widgets/modelserverselector.h"
#include "widgets/dataeditwindow.h"
#include "widgets/cavas.h"

#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void edit_lay_change();

private slots:

signals:
    void fix_ret_form_size();

protected:
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    HookedImageSave *m_w_hook;
    ModelServerSelector* m_w_select;
    DataEditWindow* m_w_dedit;
    Cavas *m_w_canvas;
};
#endif // MAINWINDOW_H
