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
window.setWindowTitle("3D Viewer")
window.setWindowIcon(":/icons/3d.svg")
window.loadFont(":/titillium-web-font/TitilliumWeb-1eq2.ttf")
window.loadStylesheet(":/themes/basic.qss")
window.setDefaultFont("Titillium Web")
resize(window, 900, 600)


var label = window.qColorLabel("label0")
setGeometry(label, 0, 0, 200, 32)
label.text = "Hello"
label.alignment = 0x84
console.info(label.alignment)

var button = window.qPushButton("btn0")
setGeometry(button, 0, 36, 200, 32)
button.text = "Hello World"
button["clicked()"].connect(function() {
    console.info("click Hello World")
})

// var occ = window.qOccViewer("occViewer")
//
// setGeometry(occ, 0, 0, 900, 600)
//
//
// console.info(Object.keys(occ.qRenderThread()));
//
// setTimeout(function () {
//     qApplicationWindow.updateOcc(occ)
//
//     setTimeout(function () {
//
//
//
//         occ.qRenderThread().switchLeftView()
//
//     }, 2000)
//
// }, 1000);
//





