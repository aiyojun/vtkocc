#ifndef VTKOCC_QMODELREADER_H
#define VTKOCC_QMODELREADER_H


#include <TopoDS_Shape.hxx>
#include <utility>
#include "imp.h"

class QModelReader : public QThread {
    Q_OBJECT
public:
    QModelReader(QString filepath, std::vector<TopoDS_Shape>& shapes, QObject *parent = nullptr)
        : QThread(parent), filepath(std::move(filepath)), g_shapes(shapes) {}
    std::vector<TopoDS_Shape>& getShapes() { return g_shapes; }
Q_SIGNALS:
    void complete();
protected:
    void run() override;
private:
    std::vector<TopoDS_Shape>& g_shapes;
    QString filepath;
};


#endif //VTKOCC_QMODELREADER_H
