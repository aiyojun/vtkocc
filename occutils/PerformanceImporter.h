#ifndef VTKOCC_PERFORMANCEIMPORTER_H
#define VTKOCC_PERFORMANCEIMPORTER_H

#include <QtCore/QThread>
#include <Standard_Handle.hxx>
#include <Standard_CString.hxx>
#include <TopoDS_Shape.hxx>
#include <TDocStd_Document.hxx>

class ModelReadException : public std::exception {
public:
    explicit ModelReadException(const char *s): std::exception(), _message(s) {}
    const char* what() const noexcept override { return _message; }
private:
    const char* _message;
};

class PerformanceImporter : public QThread {
    Q_OBJECT

public:
    enum ReadTask { BUILD_SHAPE, BUILD_DOC };

    PerformanceImporter(QObject* parent = nullptr): QThread(parent), _taskType(BUILD_DOC) {}
    ~PerformanceImporter() override = default;

    void SetTask(QString filename, PerformanceImporter::ReadTask task)
    { _taskType = task; _filename = filename.toStdString(); }
    const Handle(TDocStd_Document)& GetDocument() const { return _document; }
    const TopoDS_Shape& GetShape() const { return _shape; }
    void ValidateTask();

    void ReadSync();
    void ReadAsync();

    static TopoDS_Shape ReadShapeSTEP(Standard_CString filename);
    static TopoDS_Shape ReadShapeSTL (Standard_CString filename);
    static TopoDS_Shape ReadShapeIGES(Standard_CString filename);
    static TopoDS_Shape ReadShapeBRep(Standard_CString filename);
    static Handle(TDocStd_Document) BuildXCAFDocumentSTEP(Standard_CString filename);

protected:
    void run() override;

Q_SIGNALS:
    void finished();

private:
    ReadTask _taskType;
    std::string _filename;
    Handle(TDocStd_Document) _document;
    TopoDS_Shape _shape;
};

#endif //VTKOCC_PERFORMANCEIMPORTER_H
