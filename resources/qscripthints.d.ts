interface QObject {
    readonly objectName: string;
}

interface QPoint {
    x: number;
    y: number;
}

interface QPointConstructor {
    readonly prototype: QPoint;

    new(): QPoint;

    new(x: number, y: number): QPoint;
}

declare var QPoint: QSizeConstructor;

interface QSize {
    width: number;
    height: number;
}

interface QSizeConstructor {
    readonly prototype: QSize;

    new(): QSize;

    new(width: number, height: number): QSize;
}

declare var QSize: QSizeConstructor;

interface QRect {
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

type QBasicObject = QPoint | QSize | QRect;

type QVariant = null;

type QWidgets = QWidget | QLabel;

interface QWidget extends QObject {
    readonly modal: boolean;
    readonly windowModality: number;
    readonly enabled: boolean;
    readonly geometry: QVariant;
    readonly frameGeometry: QVariant;
    readonly normalGeometry: QVariant;
    readonly x: number;
    readonly y: number;
    readonly pos: QVariant;
    readonly frameSize: QVariant;
    readonly size: QVariant;
    readonly width: number;
    readonly height: number;
    readonly rect: QVariant;
    readonly childrenRect: QVariant;
    readonly childrenRegion: QVariant;
    readonly sizePolicy: QVariant;
    readonly minimumSize: QVariant;
    readonly maximumSize: QVariant;
    readonly minimumWidth: number;
    readonly minimumHeight: number;
    readonly maximumWidth: number;
    readonly maximumHeight: number;
    readonly sizeIncrement: QVariant;
    readonly baseSize: QVariant;
    readonly palette: QVariant;
    readonly font: QVariant;
    readonly cursor: QVariant;
    readonly mouseTracking: boolean;
    readonly tabletTracking: boolean;
    readonly isActiveWindow: boolean;
    readonly focusPolicy: number;
    readonly focus: boolean;
    readonly contextMenuPolicy: number;
    readonly updatesEnabled: boolean;
    readonly visible: boolean;
    readonly minimized: boolean;
    readonly maximized: boolean;
    readonly fullScreen: boolean;
    readonly sizeHint: QVariant;
    readonly minimumSizeHint: QVariant;
    readonly acceptDrops: boolean;
    readonly windowTitle: string;
    readonly windowIcon: QVariant;
    readonly windowIconText: string;
    readonly windowOpacity: number;
    readonly windowModified: boolean;
    readonly toolTip: string;
    readonly toolTipDuration: number;
    readonly statusTip: string;
    readonly whatsThis: string;
    readonly accessibleName: string;
    readonly accessibleDescription: string;
    readonly layoutDirection: string;
    readonly autoFillBackground: boolean;
    readonly styleSheet: string;
    readonly locale: QVariant;
    readonly windowFilePath: string;
    readonly inputMethodHints: number;

    destroyed(o: QObject): void;

    destroyed(): boolean;

    objectNameChanged(s: string): void;

    deleteLater(): void;

    windowTitleChanged(s: string): void;

    windowIconChanged(icon: QVariant): void;

    windowIconTextChanged(s: string): void;

    customContextMenuRequested(p: QVariant): void;

    setEnabled(b: boolean): void;

    setDisabled(b: boolean): void;

    setWindowModified(b: boolean): void;

    setWindowTitle(s: string): void;

    setStyleSheet(s: string): void;

    setFocus(): void;

    update(): void;

    repaint(): void;

    setVisible(b: boolean): void;

    setHidden(b: boolean): void;

    show(): void;

    hide(): void;

    showMinimized(): void;

    showMaximized(): void;

    showFullScreen(): void;

    showNormal(): void;

    close(): void;

    raise(): void;

    lower(): void;

    updateMicroFocus(): void;

    grab(r: QVariant): void;

    grab(): void;
}

interface QMainWindow extends QWidget {
    readonly iconSize: QVariant;
    readonly toolButtonStyle: number;
    readonly animated: boolean;
    readonly documentMode: boolean;
    readonly tabShape: number;
    readonly dockNestingEnabled: boolean;
    readonly dockOptions: number;
    readonly unifiedTitleAndToolBarOnMac: boolean;

    iconSizeChanged(s: QVariant): void;

    toolButtonStyleChanged(n: number): void;

    tabifiedDockWidgetActivated(w: QWidget): void;

    setAnimated(b: boolean): void;

    setDockNestingEnabled(b: boolean): void;

    setUnifiedTitleAndToolBarOnMac(b: boolean): void;
}

interface QLabel extends QWidget {
    readonly text: string;
    textFormat: number;
    pixmap: QVariant;
    scaledContents: boolean;
    alignment: number;
    wordWrap: boolean;
    margin: number;
    indent: number;
    openExternalLinks: boolean;
    textInteractionFlags: number;
    hasSelectedText: boolean;
    selectedText: string;

    setText(text: string): void;

    setTextFormat(n: number): void;

    setPixmap(p: QVariant): void;

    setScaledContents(b: boolean): void;

    setAlignment(n: number): void;

    setWordWrap(b: boolean): void;

    setMargin(m: number): void;

    setIndent(i: number): void;

    setOpenExternalLinks(b: boolean): void;

    setTextInteractionFlags(n: number): void;
}

interface QApplicationWindow extends QWidget {
    createWidget(type: string): QWidgets;

    createWidget(type: string, id: string): QWidgets;

    place(w: QWidgets, x: QBasicObject): void;

    findChild(s: string): QWidgets;
}

declare var qApplicationWindow: QApplicationWindow;

declare function typecast(obj: QVariant): QSize | QRect;

declare function typecast(type: string, obj: QBasicObject): QVariant;