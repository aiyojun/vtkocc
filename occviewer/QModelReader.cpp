#include "QModelReader.h"
#include "QOccTools.h"
#include <STEPControl_Reader.hxx>

void QModelReader::run() {
    LOG("QModelReader::run");
    g_shapes = std::move(QOccTools::ReadModelFile(filepath.toStdString()));
    LOG("QModelReader::run complete");
    emit complete();
}
