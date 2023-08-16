//
// Created by jun.dai on 2023/8/16.
//

#ifndef VTKOCC_QOCCTOOLS_H
#define VTKOCC_QOCCTOOLS_H


#include <QtCore/QPoint>
#include <Graphic3d_Vec2.hxx>
#include <Aspect_VKeyFlags.hxx>
#include <V3d_View.hxx>

class QOccTools {
public:
    static Graphic3d_Vec2i QPoint2Graphic3d_Vec2i(const QPoint& p);
    static Aspect_VKeyMouse QtMouseButton2Aspect_VKeyMouse(const Qt::MouseButton& button);
    static void useRayTracing(Handle(V3d_View) view);
//    static Aspect_VKeyFlags buildAspect_VKeyFlags(bool ctrlkey, bool altkey, bool shiftkey);
};


#endif //VTKOCC_QOCCTOOLS_H
