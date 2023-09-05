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

resize(window, 900, 600)

var occ = window.qOccViewer("occViewer")

setGeometry(occ, 0, 0, 900, 600)

setTimeout(function () {
    // qApplicationWindow.createOcc(occ)
    setTimeout(function () {
        qApplicationWindow.updateOcc(occ)
    }, 1000);
}, 1000);





// window.loadFont(":/titillium-web-font/TitilliumWeb-1eq2.ttf")
// window.loadStylesheet(":/themes/basic.qss")
// window.setDefaultFont("Titillium Web")
//
// var label0 = window.qLabel("label0")
// var input0 = window.qLineEdit("input0")
// var label1 = window.qLabel("label1")
// var input1 = window.qLineEdit("input1")
// var button0 = window.qPushButton("button0");
// var button1 = window.qPushButton("button1");
//
// var spinner = window.qLinearSpinner("spinner");
// setGeometry(spinner, 0, 100, 400, 200)
// // window.place(spinner, typecast("QPoint", new QPoint(0, 100)))
// label0.setText("Username")
// label1.setText("Password")
// window.place(label0, typecast("QPoint", new QPoint(0, 0)))
// window.place(input0, typecast("QPoint", new QPoint(150, 0)))
// window.place(label1, typecast("QPoint", new QPoint(0, 32)))
// window.place(input1, typecast("QPoint", new QPoint(150, 32)))
// window.place(button0, typecast("QPoint", new QPoint(0, 64)))
// window.place(button1, typecast("QPoint", new QPoint(150, 64)))
// window.setWidgetGeometry(input0, typecast("QRect", new QRect(150, 0, 200, 32)));
// window.setLineEditPlaceholder(input0, "Please input username")
// window.setLineEditPlaceholder(input1, "Please input password")
// window.setButtonText(button0, "OK")
// window.setButtonText(button1, "Cancel")
//
//
// console.info("button0 text :", button0.text)

