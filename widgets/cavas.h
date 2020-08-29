#ifndef CAVAS_H
#define CAVAS_H

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class Cavas;
}

class Cavas : public QWidget
{
    Q_OBJECT

public:
    explicit Cavas(QWidget *parent = nullptr);
    ~Cavas();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::Cavas *ui;
};

#endif // CAVAS_H
