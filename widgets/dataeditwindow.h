#ifndef DATAEDITWINDOW_H
#define DATAEDITWINDOW_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QClipboard>
#include <QFileDialog>
#include <QFile>
#include <QRegExp>
#include <QTextStream>
#include <QMetaType>
#include <QDialog>
#include <QMouseEvent>

#include "userdefines.hpp"


namespace Ui {
class DataEditWindow;
}

class DataEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataEditWindow(QWidget *parent = nullptr);
    ~DataEditWindow();

public slots:
    void RecieveResultData(ResultType resultData); //ocr
    void RecieveTessResult(QString tessStr);  //ocr
    void fix_form_size();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseRelaseEvevt(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

private:
    void _init_grid();
    QMenu *_right_click_menu;
    QPoint _right_click_point;
    QAction* _add_head_row;
    QAction* _add_head_col;
    QAction* _add_col;
    QAction* _add_row;
    QAction* _del_col;
    QAction* _del_row;
    QAction* _copy_data;
    QAction* _paste_data;
    QAction* _copy_from_tesseract;
    void _init_table_widget_actions();

private slots:
    void re_grid_widget();

    void _add_tablewidget_col();
    void _add_tablewidget_row();
    void _del_tablewidget_col();
    void _del_tablewidget_row();
    void _add_tablewidget_headcol();
    void _add_tablewidget_headrow();
    void _copy_tablewidget_data();
    void _paste_tablewidget_data();
    void _copy_tess_to_tablewidget();
    void show_tablewidget_menu(QPoint point);

    void on_Btn_CopyTessResult_clicked();

    void on_Btn_SaveResult_clicked();

    void on_Edt_DefaultFileName_selectionChanged();

    void on_BtnDuck_clicked();

    void on_BtnMax_clicked();

signals:
    void dock_to();


private:
    Ui::DataEditWindow *ui;
    QPoint m_last_pos;
    bool m_perm;
    bool m_is_max;
};

#endif // DATAEDITWINDOW_H
