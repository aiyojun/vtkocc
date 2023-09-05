/**
 * Qt script ui management framework.
 */
var window = qApplicationWindow
function setGeometry(widget, x, y, width, height) {
    window.setWidgetGeometry(widget, typecast("QRect", new QRect(x, y, width, height)));
}
function move(widget, x, y) {
    window.place(widget, typecast("QPoint", new QPoint(x, y)))
}
function resize(widget, width, height) {
    window.setSize(widget, typecast("QSize", new QSize(width, height)))
}
window.loadFont(":/titillium-web-font/TitilliumWeb-1eq2.ttf")
window.loadStylesheet(":/themes/basic.qss")
window.setDefaultFont("Titillium Web")
resize(window, 900, 600)

var occ = window.qOccViewer("occViewer")

setGeometry(occ, 0, 0, 900, 600)


console.info(Object.keys(occ.qRenderThread()));

setTimeout(function () {
    qApplicationWindow.updateOcc(occ)

    setTimeout(function () {



        occ.qRenderThread().switchLeftView()

    }, 2000)

}, 1000);



