/**
 * Qt script ui management framework.
 * console {
 *     log
 *     error
 *     warn
 *     info
 *     debug
 * }
 * document {
 *     createElement
 *     getElementById
 * }
 */
var xlabel = qApplicationWindow.createWidget("QLabel", "xlabel")
xlabel.setText("Hello World")
qApplicationWindow.setGeometry({x: 0, y: 0, width: 900, height: 600})
qApplicationWindow.show();
// println(document.getElementsByName())
// document.createElement()

// println("-- execute main.js")
// println("-- win : ", win);
// println(win)
// // var xlabel =
// var xlabel = win.build("QLabel", "xlabel") //win.findChild("xlabel")
// println("-- build : ", xlabel)
// print(xlabel)
// print(xlabel.objectName)
// xlabel.setText("Hello World")
// // xlabel.setGeometry(0, 0, 100, 32);
// win.setGeo(0, 0, 900, 600);
// win.show()
