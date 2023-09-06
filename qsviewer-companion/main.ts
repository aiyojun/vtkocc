// QScript ui generator framework.
// First of all, make an alias for qApplicationWindow.
const app = qApplicationWindow;
// Prepare necessary functions for context. More concise api.
function layout(widget: QWidget, x: number, y: number, width: number, height: number)
{ app.setWidgetGeometry(widget, typecast("QRect", new QRect(x, y, width, height))); }
function resize(widget: QWidget, width: number, height: number)
{ app.setSize(widget, typecast("QSize", new QSize(width, height))); }
function locate(widget: QWidget, x: number, y: number)
{ app.place(widget, typecast("QPoint", new QPoint(x, y))); }
function $click(widget: QWidget, callback: () => void)
{ widget["clicked()"].connect(callback); }
String.prototype.replaceAll = function (regex: RegExp | string, str: string)
{ return this.toString().split(regex).join(str); }
function exists(o: any, k: any) {
    if (k === undefined)
        return o !== undefined && o !== null
    return typeof o === 'object' && o !== null
        && !(o instanceof Array) && o.hasOwnProperty(k)
        && o[k] !== undefined && o[k] !== null
}
// ui utils:
function compute(length: number, calc: string) {
    calc = calc.trim();
    if (/^[0-9]+$/.test(calc)) return parseInt(calc);
    if (/^[0-9]+px$/.test(calc)) return parseInt(calc.substring(0, calc.length - 2));
    if (/^[0-9]+%$/.test(calc)) return parseInt(calc.substring(0, calc.length - 1)) * .01 * length;
    calc = calc.replaceAll(" ", "");
    if (/^calc\(([+-]?([0-9]+%|[0-9]+px))+\)$/.test(calc)) {
        calc = calc.substring(5, calc.length - 1);
        let arr = []
        let i = 0
        while (i < calc.length) {
            let _arr = calc.substring(i).match(/^[+-]?[0-9]+%/);
            if (_arr !== null && _arr.length > 0) {
                arr.push(parseInt(calc.substring(i, i + _arr[0].length - 1)) * .01 * length);
                i = i + _arr[0].length;
                continue;
            }
            _arr = calc.substring(i).match(/^[+-]?[0-9]+px/);
            if (_arr !== null && _arr.length > 0) {
                arr.push(parseInt(calc.substring(i, i + _arr[0].length - 2)));
                i = i + _arr[0].length;
            }
            break;
        }
        let r = 0;
        for (i = 0; i < arr.length; i++) r += arr[i];
        return r;
    }
    return 0;
}

let manager: Record<string, any> = {
    counter: 0,
    widgets: {},
    supplyWidgetName: function(_ui: Record<string, any>) {
        if (!exists(_ui, "name"))
            _ui["name"] = "widget-" + (this.counter++);
        return _ui["name"];
    },
    widgetOf: function (name: string) {
        return this.widgets[name];
    },
    QBasicButton: function (_ui: Record<string, any>) {
        let name = _ui["name"];
        let w = app.qPushButton(name);
        w.text = _ui["text"] || "";
        this.widgets[name] = w;
        return w;
    },
    QLabel: function (_ui: Record<string, any>) {
        let name = _ui["name"];
        let w = app.qLabel(name);
        w.text = _ui["text"] || "";
        if (name !== "") this.widgets[name] = w;
        return w;
    },
    QColorLabel: function (_ui: Record<string, any>) {
        let name = _ui["name"];
        let w = app.qColorLabel(name);
        w.text = _ui["text"] || "";
        if (name !== "") this.widgets[name] = w;
        return w;
    },
    QLineEdit: function (_ui: Record<string, any>) {
        let name = _ui["name"];
        let w = app.qLineEdit(name);
        w.text = _ui["text"] || "";
        w.placeHolderText = _ui["placeholder"] || "";
        if (name !== "") this.widgets[name] = w;
        return w;
    },
    QOccViewer: function (_ui: Record<string, any>) {
        let name = _ui["name"];
        let w = app.qOccViewer(name);
        if (name !== "") this.widgets[name] = w;
        return w;
    },
    QNavigator: function (_ui: Record<string, any>) {
        let name = _ui["name"];
        let w = app.qNavigator(name);
        if (name !== "") this.widgets[name] = w;
        return w;
    },
    QLinearSpinner: function (_ui: Record<string, any>) {
        let name = _ui["name"];
        let w = app.qLinearSpinner(name);
        if (name !== "") this.widgets[name] = w;
        return w;
    },
}

// Register life cycle functions.
let ui_declare = {
    type: "QVBoxLayout", width: "1280px", height: "960px", children: [
        { type: "QHBoxLayout", width: "100%", height: "32px", children: [
                {type: "QLabel", name: "logo", text: "VTK OCC", width: "100px", height: "100%"},
                {type: "QHBoxLayout", reverse: true, width: "calc(100% - 200px)", height: "100%", children: [
                    {type: "QBasicButton", name: "openLocalFilesystem", text: "Open", width: "100px", height: "100%"},
                    {type: "QBasicButton", text: "View", width: "100px", height: "100%"},
                    ]},
            ] },
        { type: "QHBoxLayout", width: "100%", height: "calc(100% - 32px)", children: [
                { type: "QVBoxLayout", width: "240px", height: "100%", children: [
                        { type: "QNavigator", name: "navigator", width: "100%", height: "100%" }
                    ] },
                { type: "QOccViewer", name: "occViewer", width: "calc(100% - 240px)", height: "100%" },
            ] }
    ]
}

onCreate()
app["windowSizeChanged(int, int)"].connect(onUpdate)
///////////////////////////////////////////////////////
// Main function definitions:
///////////////////////////////////////////////////////
function loopCreate(_ui: Record<string, any>) {
    let type = _ui["type"];
    if (/^Q.*Layout$/.test(type)) {
        let children = _ui["children"];
        for (let i = 0; i < children.length; i++) {
            loopCreate(children[i]);
        }
        return;
    }
    if (/^Q.*/.test(type) && manager.hasOwnProperty(type))
        manager.supplyWidgetName(_ui);
        manager[type](_ui);
}

function layoutAbsolute(_ui: Record<string, any>, x: number, y: number, width: number, height: number) {
    if (exists(_ui, "position") && _ui["position"] === "absolute") {
        loopLayout(_ui,
            x + compute(width, _ui["x"]), y + compute(height, _ui["y"]),
            compute(width, _ui["width"]), compute(height, _ui["height"]));
        return true;
    }
    return false;
}

function loopLayout(_ui: Record<string, any>, x: number, y: number, width: number, height: number) {
    let type = _ui["type"];
    if (!/^Q.*Layout$/.test(type)) {
        layout(manager.widgetOf(_ui["name"]), x, y, width, height);
        return;
    }
    if (type === "QVBoxLayout") {
        let children = _ui["children"];
        let reverse = _ui["reverse"] || false;
        let dy = reverse ? (y + height) : y;
        for (let i = 0; i < children.length; i++) {
            if (layoutAbsolute(children[i], x, y, width, height)) continue;
            let _height = compute(height, children[i]["height"]);
            loopLayout(children[i], x, dy, compute(width, children[i]["width"]), _height);
            if ( reverse) dy -= _height;
            if (!reverse) dy += _height;
        }
        return;
    }
    if (type === "QHBoxLayout") {
        let children = _ui["children"];
        let reverse = _ui["reverse"] || false;
        let dx = reverse ? (x + width) : x;
        for (let i = 0; i < children.length; i++) {
            if (layoutAbsolute(children[i], x, y, width, height)) continue;
            let _width = compute(width, children[i]["width"]);
            loopLayout(children[i], dx, y, _width, compute(height, children[i]["height"]));
            if ( reverse) dx -= _width;
            if (!reverse) dx += _width;
        }
    }
}

function onCreate() {
    app.setWindowTitle("3D Viewer");
    app.setWindowIcon(":/icons/3d.svg");
    app.loadFont(":/titillium-web-font/TitilliumWeb-1eq2.ttf");
    app.setDefaultFont("Titillium Web");
    app.loadStylesheet(":/themes/basic.qss");
    let width  = compute(0, ui_declare.width);
    let height = compute(0, ui_declare.height);
    resize(app, width, height);
    loopCreate(ui_declare);
    onUpdate(width, height);
    let occViewer = manager.widgetOf("occViewer");
    let occRender = occViewer.qRenderThread();
    let navigator = manager.widgetOf("navigator");
    let logo = manager.widgetOf("logo");
    logo.alignment = 0x81;
    $click(manager.widgetOf("openLocalFilesystem"), function () {
        let filename = app.openLocalFilesystem();
        console.info("open local file : ", filename);
        occRender.importModelFile(filename);
    })
    // occRender["sendAssemblyTree(string)"];
    // $click(manager.widgetOf("occViewer", function () {
    //
    // });
}
function onUpdate(w: number, h: number) {
    loopLayout(ui_declare, 0, 0, w, h);
    let occViewer = manager.widgetOf("occViewer");
    let occRender = occViewer.qRenderThread();
    occRender.fresh();
}

for (let x in [1, 2, 3]) {
    console.info(x);
}





