#include "modelserverselector.h"
#include "ui_modelserverselector.h"

#include <QAbstractButton>
#include <QSettings>
#include <QMetaType>
#include <QTimer>


ModelServerSelector::ModelServerSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelServerSelector)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signal_update_current_row(int, int)), this, SLOT(slot_update_current_row(int, int)));

    // style set
    setStyleSheet("QLineEdit{border-radius:5px 5px; color:blue} "
                  "QLabel{color:blue} "
                  "QPushButton{border-radius:5px 5px; color:blue}");
    ui->buttonBox->buttons().at(0)->setText(tr("确定"));
    ui->buttonBox->buttons().at(0)->setStyleSheet("color: green; border:none");

    ui->buttonBox->buttons().at(1)->setText(tr("取消"));
    ui->buttonBox->buttons().at(1)->setStyleSheet("color: red; border:none");

    ui->Tips->setStyleSheet("color:red");

    // meta registry
    qRegisterMetaType<OcrDefine::ModelProto>("OcrDefine::ModelProto");
    qRegisterMetaType<OcrDefine::OcrEngine>("OcrDefine::OcrEngine");

    // disable sort to keep it as insert order
    ui->ProtoView0->setSortingEnabled(false);
    ui->ProtoView1->setSortingEnabled(false);
    ui->SvView0->setSortingEnabled(false);
    ui->SvView1->setSortingEnabled(false);
    // red-black tree, so the order will keep the same, accord the key operator <
    pro_mp["TcpProto"] = OcrDefine::TcpProto;
    pro_mp["DirectProto"] = OcrDefine::DirectProto;

    ocr_mp["OcrInnerTesseract"]= OcrDefine::OcrInnerTesseract;
    ocr_mp["OcrInnerEb"] = OcrDefine::OcrInnerEb;
    ocr_mp["OcrUserDefine"] = OcrDefine::OcrUserDefine;

    for(auto ite=pro_mp.constBegin(); ite != pro_mp.constEnd(); ite++){
        ui->ProtoView0->addItem(ite.key());
        ui->ProtoView1->addItem(ite.key());
    }

    for(auto ite=ocr_mp.constBegin(); ite != ocr_mp.constEnd(); ite++){
        ui->SvView0->addItem(ite.key());
        ui->SvView1->addItem(ite.key());
    }
    // setdefault
    to_default();

    // add host, port validater
    // ignore
}

ModelServerSelector::~ModelServerSelector()
{
    delete ui;
}

void ModelServerSelector::LoadSetting(int type, OcrDefine::ModelProto &proto , OcrDefine::OcrEngine &engine, QString& host, int &port)
{
    if(type==0){
        proto = pro_mp.value(ui->ProtoView0->currentItem()->text());
        engine = ocr_mp.value(ui->SvView0->currentItem()->text());
        host = ui->Host0->text();
        port = ui->Port0->text().toInt();
    }else{
        proto = pro_mp.value(ui->ProtoView1->currentItem()->text());
        engine = ocr_mp.value(ui->SvView1->currentItem()->text());
        host = ui->Host1->text();
        port = ui->Port1->text().toInt();
    }
}

void ModelServerSelector::to_default()
{
    ui->SvView0->setCurrentRow(1);
    ui->SvView1->setCurrentRow(0);
    ui->ProtoView0->setCurrentRow(0);
    ui->ProtoView1->setCurrentRow(0);
    ui->Host0->setVisible(false);
    ui->Port0->setVisible(false);
    ui->Host1->setVisible(false);
    ui->Port1->setVisible(false);
}

void ModelServerSelector::slot_update_current_row(int type, int row){
    QTimer t;
    t.singleShot(500, this,[=]{
        if(type==0){
            ui->ProtoView0->setCurrentRow(row);
        }else{
            ui->ProtoView1->setCurrentRow(row);
        }
    });
}

void ModelServerSelector::on_buttonBox_accepted()
{
    auto proto = pro_mp.value(ui->ProtoView0->currentItem()->text());
    auto engine = ocr_mp.value(ui->SvView0->currentItem()->text());
    auto host = ui->Host0->text();
    auto port = ui->Port0->text().toInt();
    emit reset(0, proto, engine, host, port);
    proto = pro_mp.value(ui->ProtoView1->currentItem()->text());
    engine = ocr_mp.value(ui->SvView1->currentItem()->text());
    host = ui->Host1->text();
    port = ui->Port1->text().toInt();
    emit reset(1, proto, engine, host, port);
}

void ModelServerSelector::on_pushButton_clicked()
{
    to_default();
}

void ModelServerSelector::on_ProtoView0_currentRowChanged(int currentRow)
{
    if(currentRow == 1){
        if(ui->SvView0->currentItem()->text().startsWith("OcrInner")){
            emit signal_update_current_row(0, 0);
            ui->Tips->setText("OcrInner not Support other proto");
            return;
        }else{
            ui->Host0->setVisible(true);
            ui->Port0->setVisible(true);
        }

    }else{
        ui->Host0->setVisible(false);
        ui->Port0->setVisible(false);
    }
    ui->Tips->setText("");
}

void ModelServerSelector::on_ProtoView1_currentRowChanged(int currentRow)
{
    if(currentRow == 1){
        if(ui->SvView1->currentItem()->text().startsWith("OcrInner")){
            emit signal_update_current_row(1, 0);
            ui->Tips->setText("OcrInner not Support other proto");
            return;
        }else{
            ui->Host1->setVisible(true);
            ui->Port1->setVisible(true);
        }
    }else{
        ui->Host1->setVisible(false);
        ui->Port1->setVisible(false);
    }
    ui->Tips->setText("");
}

void ModelServerSelector::on_SvView0_currentRowChanged(int currentRow)
{
    Q_UNUSED(currentRow);
    ui->ProtoView0->setCurrentRow(0);
}

void ModelServerSelector::on_SvView1_currentRowChanged(int currentRow)
{
    Q_UNUSED(currentRow);
    ui->ProtoView0->setCurrentRow(0);
}
