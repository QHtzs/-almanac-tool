#ifndef MODELSERVERSELECTOR_H
#define MODELSERVERSELECTOR_H

#include <QDialog>
#include <QMap>
#include "userdefines.hpp"

namespace Ui {
class ModelServerSelector;
}

class ModelServerSelector : public QDialog
{
    Q_OBJECT

public:
    explicit ModelServerSelector(QWidget *parent = nullptr);
    ~ModelServerSelector();

    void LoaderExistsOcr(QString setting="setting.ini");

    void LoadSetting(int type, OcrDefine::ModelProto &proto , OcrDefine::OcrEngine &engine, QString& host, int &port);

private slots:
    void slot_update_current_row(int type, int row);

    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_ProtoView0_currentRowChanged(int currentRow);

    void on_ProtoView1_currentRowChanged(int currentRow);

    void on_SvView0_currentRowChanged(int currentRow);

    void on_SvView1_currentRowChanged(int currentRow);

signals:
    void reset(int type, OcrDefine::ModelProto proto , OcrDefine::OcrEngine engine, const QString& host, int port);

    void signal_update_current_row(int type, int row);

private:
    void to_default();

    Ui::ModelServerSelector *ui;

    QMap<QString, OcrDefine::ModelProto> pro_mp;
    QMap<QString, OcrDefine::OcrEngine> ocr_mp;

};

#endif // MODELSERVERSELECTOR_H
