///////////////////////////////////////////////////////
// Runtime instances
///////////////////////////////////////////////////////
const ui_declare = {
    type: "QVBoxLayout", width: "1280px", height: "960px", children: [
        { type: "QHBoxLayout", width: "100%", height: "36px", children: [
                {type: "QLabel", name: "logo", text: "VTK OCC", width: "100px", height: "100%"},
                {type: "QHBoxLayout", reverse: true, width: "calc(100% - 200px)", height: "100%", children: [
                        {type: "QPushButton", name: "darkModeButton", text: "Dark", size: 20, icon: ":/icons/laptop.svg", width: "100px", height: "100%"},
                        {type: "QPushButton", text: "View", size: 20, icon: ":/icons/box-axonometric.svg", width: "100px", height: "100%"},
                        {type: "QPushButton", name: "openLocalFilesystem", text: "Open", size: 20, icon: ":/icons/open-folder.svg", width: "100px", height: "100%"},
                    ]},
            ] },
        { type: "QHBoxLayout", width: "100%", height: "calc(100% - 36px - 24px)", children: [
                { type: "QVBoxLayout", width: "240px", height: "100%", children: [
                        { type: "QVBoxLayout", width: "240px", height: "50%", children: [
                                { type: "QLabel", name: "label_3d_views", width: "100%", height: "32px", text: "View" },
                                { type: "QHBoxLayout", width: "100%", height: "80px", children: [
                                    { type: "QToolButton", name: "viewMain", width: "80px", height: "80px", text: "Front", size: 20, icon: ":/icons/box-front.svg", toolButtonStyle: "ToolButtonTextUnderIcon" },
                                    { type: "QToolButton", name: "viewLeft", width: "80px", height: "80px", text: "Left" , size: 20, icon: ":/icons/box-left.svg" , toolButtonStyle: "ToolButtonTextUnderIcon" },
                                    { type: "QToolButton", name: "viewTop" , width: "80px", height: "80px", text: "Top"  , size: 20, icon: ":/icons/box-top.svg"  , toolButtonStyle: "ToolButtonTextUnderIcon" },
                                ] },
                                { type: "QLabel", name: "label_3d_infos", width: "100%", height: "32px", text: "Statistics" },
                                { type: "QVBoxLayout", width: "100%", height: "80px", children: [
                                        { type: "QColorLabel", name: "qclAssembly", padding: "20px", width: "auto", height: "32px", text: "Assembly: yes" },
                                        { type: "QFrame", width: "0", height: "5px" },
                                        { type: "QColorLabel", name: "qclFormat"  , padding: "20px", width: "auto", height: "32px", text: "Format: none" },
                                        { type: "QFrame", width: "0", height: "5px" },
                                        { type: "QColorLabel", name: "qclParts"   , padding: "20px", width: "auto", height: "32px", text: "Parts: 0" },
                                        { type: "QFrame", width: "0", height: "5px" },
                                        { type: "QColorLabel", name: "qclName", padding: "20px", width: "auto", height: "32px", text: "Name: none" },
                                        { type: "QFrame", width: "0", height: "5px" },
                                        { type: "QColorLabel", name: "qclDepth", padding: "20px", width: "auto", height: "32px", text: "Depth: 0" },
                                        { type: "QFrame", width: "0", height: "5px" },
                                    ] },
                            ] },
                        { type: "QVBoxLayout", width: "240px", height: "50%", children: [
                                { type: "QNavigator", name: "navigator", width: "100%", height: "100%" },
                                { type: "QScrollArea", name: "navigatorScroll", position: "absolute", x: "0", y: "0", width: "100%", height: "100%" }
                            ] }
                    ] },
                { type: "QOccViewer", name: "occViewer", width: "calc(100% - 240px)", height: "100%" },
            ] },
        { type: "QHBoxLayout", width: "100%", height: "24px", children: [
                {type: "QFrame", position: "absolute", x: "0", y: "0", width: "100px", height: "100%"},
                { type: "QLabel", name: "statusBar", width: "100%", height: "100%", text: "- Prepared VTK OCC ..." },
                { type: "QPushButton", name: "support", position: "absolute", x: "calc(100% - 100px)", y: "0", width: "100px", height: "100%", text: "Support", source: "https://" }
            ] }
    ]
}
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
                continue;
            }
            break;
        }
        let r = 0;
        for (i = 0; i < arr.length; i++) r += arr[i];
        return r;
    }
    return 0;
}
///////////////////////////////////////////////////////
// Runtime instances
///////////////////////////////////////////////////////
class Manager {
    _counter: number = 0;
    _widgets: Record<string, QWidget> = {};

    supplyWidgetName(_ui: Record<string, any>) {
        if (!exists(_ui, "name"))
            _ui["name"] = _ui["type"] + "_" + (this._counter++);
        return _ui["name"];
    }

    widgetOf(name: string): QWidget {
        console.info("-- widgetOf : ", name, " ", typeof this._widgets[name]);
        return this._widgets[name];
    }

    create(type: string, _ui: Record<string, any>): QWidget {
        console.info("-- create widget : ", type);
        const handles = [
            {
                name: "QFrame", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qFrame(name);
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QLabel", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qLabel(name);
                    w.text = _ui["text"] || "";
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QColorLabel", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qColorLabel(name);
                    w.text = _ui["text"] || "";
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QLineEdit", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qLineEdit(name);
                    w.text = _ui["text"] || "";
                    w.placeHolderText = _ui["placeholder"] || "";
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QPushButton", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qPushButton(name);
                    if (exists(_ui, "icon"))
                        app.setButtonIcon(w, _ui["icon"]);
                    if (exists(_ui, "size"))
                        app.setButtonIconSize(w, typecast("QSize", new QSize(_ui["size"], _ui["size"])));
                    w.text = _ui["text"] || "";
                    this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QToolButton", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qToolButton(name);
                    if (exists(_ui, "icon"))
                        app.setButtonIcon(w, _ui["icon"]);
                    if (exists(_ui, "size"))
                        app.setButtonIconSize(w, typecast("QSize", new QSize(_ui["size"], _ui["size"])));
                    app.setToolButtonStyle(w, (exists(_ui, "toolButtonStyle") && _ui["toolButtonStyle"] === "ToolButtonTextUnderIcon") ? 3 : 2)
                    app.setButtonText(w, _ui["text"]);
                    this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QTextBrowser", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qTextBrowser(name);
                    app.setTextBrowserSource(w, _ui["source"] || "https://")
                    w.text = _ui["text"] || "";
                    w.placeHolderText = _ui["placeholder"] || "";
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QOccViewer", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qOccViewer(name);
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QNavigator", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qNavigator(name);
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QScrollArea", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qScrollArea(name);
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
            {
                name: "QLinearSpinner", builder: (_ui: Record<string, any>) => {
                    let name = _ui["name"];
                    let w = app.qLinearSpinner(name);
                    if (name !== "") this._widgets[name] = w;
                    return w;
                }
            },
        ];
        for (let i = 0; i < handles.length; i++) {
            const handle = handles[i];
            if (handle.name === type)
                return handle.builder(_ui);
        }
        throw new Error("unknown plugin : " + type);
    }
}
const manager: Manager = new Manager();
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
    manager.supplyWidgetName(_ui);
    manager.create(type, _ui);
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

        if (type === "QColorLabel") {
            app.setLabelAutoWidth(manager.widgetOf(_ui["name"]) as QLabel, compute(0, _ui["padding"] || "5px"));
        }

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

const cache = {
    importFilename: "",
}

function onCreate() {
    app.setWindowTitle("3D Viewer");
    app.setWindowIcon(":/icons/3d.svg");
    app.loadFont(":/titillium-web-font/TitilliumWeb-1eq2.ttf");
    app.setDefaultFont("Titillium Web");
    const width  = compute(0, ui_declare.width);
    const height = compute(0, ui_declare.height);
    resize(app, width, height);
    loopCreate(ui_declare);
    onUpdate(width, height);
    const occViewer = manager.widgetOf("occViewer") as QOccViewer;
    const occRender = occViewer.qRenderThread();
    const navigator = manager.widgetOf("navigator");
    const navScroll = manager.widgetOf("navigatorScroll") as QScrollArea;
    const darkModeButton = manager.widgetOf("darkModeButton");
    const statusBar = manager.widgetOf("statusBar");
    const emitStatus = (msg: string) => statusBar.text = "- " + msg;
    $click(darkModeButton, () => {
        if (darkModeButton.text === "Dark") {
            darkModeButton.text = "Light";
            app.loadStylesheet(":/themes/dark.qss");
        } else {
            darkModeButton.text = "Dark";
            app.loadStylesheet(":/themes/basic.qss");
        }
    });
    $click(manager.widgetOf("viewMain"), () => occRender.switchFrontView());
    $click(manager.widgetOf("viewLeft"), () => occRender.switchLeftView());
    $click(manager.widgetOf("viewTop" ), () => occRender.switchTopView());
    app.setScrollWidget(navScroll, navigator);
    console.info(Object.keys(manager.widgetOf("support")));
    const logo = manager.widgetOf("logo");
    logo.alignment = 0x81;
    $click(manager.widgetOf("openLocalFilesystem"), () => {
        cache.importFilename = app.openLocalFilesystem();
        emitStatus("loading " + cache.importFilename);
        occRender.importModelFile(cache.importFilename);
    });
    occRender["finishedReadModel"].connect(() => {
        emitStatus("Finished import " + cache.importFilename);
    });
    occRender["sendAssemblyTree"].connect((info: string) => navigator.parse(JSON.stringify(statistic(JSON.parse(info)))));
    app.loadStylesheet(":/themes/basic.qss");
}

function onUpdate(w: number, h: number) {
    loopLayout(ui_declare, 0, 0, w, h);
    let occViewer = manager.widgetOf("occViewer");
    let occRender = occViewer.qRenderThread();
    occRender.fresh();
}

function statistic(info: Record<string, any>) {
    const qcl0 = (manager.widgetOf("qclAssembly") as QLabel);
    const qcl1 = (manager.widgetOf("qclFormat")   as QLabel);
    const qcl2 = (manager.widgetOf("qclParts")    as QLabel);
    const qcl3 = (manager.widgetOf("qclDepth")    as QLabel);
    const qcl4 = (manager.widgetOf("qclName")     as QLabel);
    qcl0.text = "Assembly: no";
    qcl1.text = "Format: none";
    qcl2.text = "Parts: 0";
    qcl3.text = "Depth: 0";
    qcl4.text = "Name: none";
    if (info["text"] !== "---") return info;
    let _r = info;
    _r["text"] = "Model";
    let shapes: Record<string, any> | null = null;
    for (let i = 0; i < _r["children"].length; i++) {
        if (_r["children"][i]["text"] === "Shapes") {
            shapes = _r["children"][i];
            break;
        }
    }
    let maxDepth = 0
    let counter = 0;
    const loopAnalysis = (_j: Record<string, any>, _depth: number = 0) => {
        if (_depth > maxDepth) { maxDepth = _depth; }
        counter++;
        if (!exists(_j, "children")) return _j;
        const arr = [];
        for (let i = 0; i < _j["children"].length; i++) {
            const node = _j["children"][i];
            if (node["text"] === "???" || node["text"] === "---")
                continue;
            arr.push(loopAnalysis(node, _depth + 1));
        }
        _j["children"] = arr;
        return _j;
    }
    loopAnalysis(_r);
    if (shapes !== null) {
        const shapesChildren = shapes["children"];
        qcl0.text = "Assembly: " + (shapesChildren.length > 1 ? "yes" : "no");
        qcl1.text = "Format: " + cache.importFilename.substring(cache.importFilename.lastIndexOf(".") + 1).toLowerCase();
        qcl2.text = "Parts: " + shapesChildren.length;
        qcl3.text = "Depth: " + (maxDepth - 1);
        qcl4.text = "Name: " + cache.importFilename.substring(cache.importFilename.lastIndexOf("/") + 1, cache.importFilename.lastIndexOf(".")).toLowerCase();
        app.setLabelAutoWidth(qcl0, 20);
        app.setLabelAutoWidth(qcl1, 20);
        app.setLabelAutoWidth(qcl2, 20);
        app.setLabelAutoWidth(qcl3, 20);
        app.setLabelAutoWidth(qcl4, 20);
    }
    return _r;
}
///////////////////////////////////////////////////////
// Register life cycle functions.
///////////////////////////////////////////////////////
onCreate();
app["windowSizeChanged(int, int)"].connect(onUpdate);
