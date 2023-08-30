#ifndef VTKOCC_PERFORMANCEIMPORTER_H
#define VTKOCC_PERFORMANCEIMPORTER_H

#include "imp.h"
#include <Standard_Handle.hxx>
#include <Standard_CString.hxx>
#include <TopoDS_Shape.hxx>
#include <TDocStd_Document.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>

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
    enum ReadTask { BUILD_SHAPE, BUILD_DOC, AUTO_BUILD };

    explicit PerformanceImporter(QObject* parent = nullptr): QThread(parent), _taskType(BUILD_DOC) {}
    ~PerformanceImporter() override = default;

    void SetTask(QString filename, PerformanceImporter::ReadTask task = ReadTask::AUTO_BUILD);
    const Handle(TDocStd_Document)& GetDocument() const { return _document; }
    const TopoDS_Shape& GetShape() const { return _shape; }
    void ValidateTask();
    QString GetDocumentInformation();
    const Handle(AIS_Shape)& GetAShape() const { return _aShape; }

    void Render(const Handle(AIS_InteractiveContext)& ctx);

    void ReadSync();
    void ReadAsync();

    static TopoDS_Shape ReadShapeSTEP(Standard_CString filename);
    static TopoDS_Shape ReadShapeSTL (Standard_CString filename);
    static TopoDS_Shape ReadShapeIGES(Standard_CString filename);
    static TopoDS_Shape ReadShapeBRep(Standard_CString filename);
    static Handle(TDocStd_Document) BuildXCAFDocumentSTEP(Standard_CString filename);

protected:
    void run() override;

private:
    bool IsStepFile(const std::string& filename) { return std::regex_match(filename, std::regex("(.)+\\.(step|stp|STEP|STP)$")); }

Q_SIGNALS:
    void finished();

private:
    ReadTask _taskType;
    std::string _filename;
    Handle(TDocStd_Document) _document;
    TopoDS_Shape _shape;
    Handle(AIS_Shape) _aShape;
};

#endif //VTKOCC_PERFORMANCEIMPORTER_H
