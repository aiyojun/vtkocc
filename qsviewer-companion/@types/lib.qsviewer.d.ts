interface String {
    replaceAll(regex: RegExp | string, str: string): string;
}

interface QObject extends Record<string, any> {
    readonly objectName: string;
}

interface QVariantObject {
}

interface QPoint extends QVariantObject {
    x: number;
    y: number;
}

interface QPointConstructor {
    readonly prototype: QPoint;

    new(): QPoint;

    new(x: number, y: number): QPoint;
}

declare var QPoint: QSizeConstructor;

interface QSize extends QVariantObject {
    width: number;
    height: number;
}

interface QSizeConstructor {
    readonly prototype: QSize;

    new(): QSize;

    new(width: number, height: number): QSize;
}

declare var QSize: QSizeConstructor;

interface QRect extends QVariantObject {
    x: number;
    y: number;
    width: number;
    height: number;
}

interface QRectConstructor {
    readonly prototype: QRect;

    new(): QRect;

    new(x: number, y: number, width: number, height: number): QRect;
}

declare var QRect: QRectConstructor;


interface QVariant<T extends QVariantObject> {
}

declare function typecast(obj: QVariant<QVariantObject>): QSize | QRect | QPoint;

declare function typecast(type: string, obj: QVariantObject): QVariant<QVariantObject>;

interface QWidget extends QObject {
    show(): void;

    hide(): void;

    setGeometry(rect: QRect): void;
}

interface QFrame extends QWidget {
}

interface QLabel extends QWidget {
    text: string;
    alignment: number;

    setText(text: string): void;

    setAlignment(align: number): void;
}

interface QColorLabel extends QLabel {
}

interface QAbstractButton extends QWidget {
    text: string;

    setText(text: string): void;
}

interface QPushButton extends QAbstractButton {
}

interface QToolButton extends QAbstractButton {
    toolButtonStyle: number;

    setToolButtonStyle(n: number): void;
}

interface QNavigator extends QWidget {
    parse(nav: string): void;
}

interface QScrollArea extends QWidget {
    alignment: number;

    setAlignment(alignment: number): void;
}

interface QLineEdit extends QWidget {
    text: string;
    placeholderText: string;

    setText(text: string): void;

    setPlaceholderText(text: string): void;
}

interface QTextBrowser extends QLineEdit {
}

interface QLinearSpinner extends QWidget {
}

interface QOccRender extends QObject {
    fresh(): void;

    importModelFile(filename: string): void;

    makeBevel(): void;

    makeCube(): void;

    switchFrontView(): void;

    switchTopView(): void;

    switchLeftView(): void;
}

interface QOccViewer extends QWidget {
    qRenderThread(): QOccRender;
}

interface QApplicationWindow extends QWidget {
    findChild(objectName: string): QWidget;

    setWindowTitle(title: string): void;

    setWindowIcon(filename: string): void;

    openLocalFilesystem(): string;

    place(w: QWidget, x: QVariant<QVariantObject>): void;

    setSize(w: QWidget, size: QVariant<QVariantObject>): void;

    loadStylesheet(filename: string): void;

    loadFont(filename: string): number;

    setDefaultFont(fontFamily: string): void;

    qFrame(id: string): QFrame;

    qLabel(id: string): QLabel;

    qColorLabel(id: string): QColorLabel;

    qPushButton(id: string): QPushButton;

    qToolButton(id: string): QToolButton;

    qNavigator(id: string): QNavigator;

    qScrollArea(id: string): QScrollArea;

    qLineEdit(id: string): QLineEdit;

    qTextBrowser(id: string): QTextBrowser;

    qLinearSpinner(id: string): QLinearSpinner;

    qOccViewer(id: string): QOccViewer;

    setLabelText(label: QLabel, text: string): void;

    setWidgetGeometry(widget: QWidget, geo: QVariant<QVariantObject>): void;

    setWidgetVisible(widget: QWidget, visible: boolean): void;

    setButtonText(button: QAbstractButton, text: string): void;

    setButtonIcon(button: QAbstractButton, icon: string): void;

    setButtonIconSize(button: QAbstractButton, size: QSize): void;

    setLineEditText(edit: QLineEdit, text: string): void;

    setLineEditPlaceholder(edit: QLineEdit, text: string): void;

    updateOcc(occ: QOccViewer): void;

    createOcc(occ: QOccViewer): void;

    setScrollWidget(scroll: QScrollArea, widget: QWidget): void;

    setTextBrowserSource(textBrowser: QTextBrowser, source: string): void;

}

declare var qApplicationWindow: QApplicationWindow;