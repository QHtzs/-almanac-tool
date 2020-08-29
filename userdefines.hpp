#ifndef USERDEFINES_H
#define USERDEFINES_H

#include<QList>



struct OcrDefine{
    enum ModelProto{
        TcpProto,    //tcp
        DirectProto  // no any
    };

    //
    enum OcrEngine{
        OcrInnerTesseract,   //built-in tesseract-ocr
        OcrInnerEb,   // built-in an Ann model, digit recon
        OcrUserDefine  // use Add
    };
};

struct ResultModel
{
    int row;
    int col;
    QString value;
    ResultModel(int _row, int _col,QString _value) {
        row = _row;
        col = _col;
        value = _value;
    }
};

typedef QList<ResultModel> ResultType;

#endif // USERDEFINES_H
