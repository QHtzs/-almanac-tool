#include "hookedimagesave.h"
#include "ui_hookedimagesave.h"

#include <QAbstractButton>
#include <QFileDialog>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QRegExp>

HookedImageSave::HookedImageSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HookedImageSave)
{
    ui->setupUi(this);
    _im_index = 0;
    _remain = 0;
    _path = "";
    QIntValidator *v = new QIntValidator(this);
    ui->NumberEdit->setValidator(v);
#ifdef WIN32
    QRegExpValidator *v1 = new QRegExpValidator(QRegExp("[A-Za-z]:[/\\\\].*"), this);
#else
    QRegExpValidator *v1 = new QRegExpValidator(QRegExp("/.+"), this);
#endif
    ui->PathEdit->setValidator(v1);

    setStyleSheet("QLineEdit{border-radius:5px 5px; color:blue} "
                  "QLabel{color:blue}");
    ui->buttonBox->buttons().at(0)->setText(tr("确定"));
    ui->buttonBox->buttons().at(0)->setStyleSheet("color: green; border:none");

    ui->buttonBox->buttons().at(1)->setText(tr("取消"));
    ui->buttonBox->buttons().at(1)->setStyleSheet("color: red; border:none");
}

HookedImageSave::~HookedImageSave()
{
    delete ui;
}

void HookedImageSave::save_image(const QImage& im){
    if(_remain > 0){
        QString File = QString("%1/%2.png").arg(_path).arg(_im_index++);
        im.save(File);
        _remain--;
    }
}

void HookedImageSave::on_PathEdit_selectionChanged()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->PathEdit->setText(dir);
}

void HookedImageSave::on_buttonBox_accepted()
{
    QString s = ui->NumberEdit->text();
    if(!s.isEmpty()) _remain = s.toInt();
    _path = ui->PathEdit->text();
}
