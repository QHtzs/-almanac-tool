#ifndef HOOKEDIMAGESAVE_H
#define HOOKEDIMAGESAVE_H

#include <QDialog>


namespace Ui {
class HookedImageSave;
}

class HookedImageSave : public QDialog
{
    Q_OBJECT

public:
    explicit HookedImageSave(QWidget *parent = nullptr);
    ~HookedImageSave();


public slots:
    void save_image(const QImage& im);

private slots:
    void on_PathEdit_selectionChanged();

    void on_buttonBox_accepted();

private:
    Ui::HookedImageSave *ui;

    uint64_t _im_index;
    QString _path;
    int _remain;
};

#endif // HOOKEDIMAGESAVE_H
