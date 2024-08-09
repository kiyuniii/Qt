#include "qteditor.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLabel>
#include <QStatusBar>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <QFontDialog>
#include <QPrinter>
#include <QPrintDialog>
//#include <QStyle>

QtEditor::QtEditor(QWidget *parent) : QMainWindow(parent) {
    textedit = new QTextEdit(this);                 //헤더에서 선언했으므로 .cpp에 QTextEdit *textedit = new QTextEdit(this)
    //setCentralWidget(textedit);//중앙 위젯으로 설정     처럼 다시 선언하면 안된다. 에러 발생함.

    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

/* 전처리기: "조건부 컴파일"
        - 거짓(0)이면 if내의 문장은 컴파일로 진행한다.
        - 진실(!0)이면
            if내의 문장은 무시하고
            else내의 문장 ~ endif까지 컴파일로 진행한다.*/
#if 0
    QTextEdit *textedit = new QTextEdit(this);  //원래 자동완성도 안됨
    mdiArea->addSubWindow(textedit);            //컴파일 과정에서 제외하기 때문
#else
    QTextEdit *textedit = newFile();

#endif

    /* ****************************************** [ QACTION ] *************************************** */
    QMenuBar *menubar = new QMenuBar(this);         //여기서 menubar는 카멜표기법을 사용하지 않는데, 이미 클래스에 property가 있기 때문
    setMenuBar(menubar);                            //QMenuBar *menubar = this->menuBar();

    /* File Menu */
    QAction *newAct = makeAction(":/images/new.png", tr("&New"), tr("Ctrl+N"), tr("New Window"), this, SLOT(newFile()));
    QAction *openAct = makeAction(":/images/open.png", tr("Open"), tr("Ctrl+O"), tr("Open the Program"), [=]{ openFile(); });
    QAction *saveAct = makeAction("", tr("&Save"), tr("Ctrl+S"), tr("SAVE"), this, SLOT(save()));
    QAction *saveAsAct = makeAction("", tr("&Save As..."), tr("Ctrl+Shift+S"), tr("SAVE AS..."), this, SLOT(saveAs()));
    QAction *printAct = makeAction("", tr("&Print"), tr("Ctrl+P"), tr("PRINT"), this, SLOT(printFile()));
    QAction *quitAct = makeAction(":/images/quit.png", tr("&Quit"), tr("Ctrl+Q"), tr("quit this Program"), this, SLOT(quitFile()));
    /* Edit Menu */
    QAction *undoAct = makeAction(":/images/undo.png", tr("&Undo"), tr("Ctrl+Z"), tr("Undo"), this, SLOT(undo()));
    QAction *redoAct = makeAction(":/images/redo.png", tr("&Redo"), tr("Ctrl+Shift+Z"), tr("Redo"), this, SLOT(redo()));
    QAction *copyAct = makeAction("", tr("&Copy"), tr("Ctrl+C"), tr("COPY"), this, SLOT(copy()));
    QAction *cutAct = makeAction("", tr("&Cut"), tr("Ctrl+X"), tr("CUT"), this, SLOT(cut()));
    QAction *pasteAct = makeAction("", tr("&Paste"), tr("Ctrl+V"), tr("PASTE"), this, SLOT(paste()));
    QAction *zoomInAct = makeAction("", tr("Zoom &In"), tr(" "), tr("ZOOM IN"), this, SLOT(zoomIn()));
    QAction *zoomOutAct = makeAction("", tr("Zoom &Out"), tr(" "), tr("ZOOM OUT"), this, SLOT(zoomOut()));

    /* Format Menu */
    QAction *fontAct = makeAction("", tr("&Font"), tr(" "), tr("FONT"), this, SLOT(setFont()));
    QAction *colorAct = makeAction("", tr("&Color"), tr(" "), tr("COLOR"), this, SLOT(setColor()));

    /*  */
    QAction *alignLeftAct = makeAction("", tr("align&Left"), tr(" "), tr("ALIGN LEFT"), this, SLOT(alignLeft()));
    QAction *alignCenterAct = makeAction("", tr("align&Center"), tr(" "), tr("ALIGN CENTER"), this, SLOT(alignCenter()));
    QAction *alignRightAct = makeAction("", tr("align&Right"), tr(" "), tr("ALIGN RIGHT"), this, SLOT(alignRight()));
    QAction *alignJustifyAct = makeAction("", tr("align&Justify"), tr(" "), tr("ALIGN JUSTIFY"), this, SLOT(alignJustify()));

    /* Window Menu */
    QAction *cascadeAct = makeAction("", tr("&Cascade"), tr("Ctrl+N"), tr("CASCADE"), this, SLOT(cascadeSubWindows()));
    QAction *tileAct = makeAction("", tr("&Tile"), tr("Ctrl+N"), tr("TILE"), this, SLOT(tileSubWindows()));
    QAction *prevAct = makeAction("", tr("&Previous"), tr(" "), tr("PREVIOUS"), this, SLOT(prev()));
    QAction *nextAct = makeAction("", tr("&Next"), tr(" "), tr("NEXT"), this, SLOT(next()));

    /* About Menu */
    QAction *aboutAct = makeAction("", tr("&About"), tr("Ctrl+Shift+A"), tr("ABOUT"), this, SLOT(about()));
    QAction *aboutQtAct = makeAction("", tr("About &Qt"), tr("Ctrl+Shift+Q"), tr("About Qt"), qApp, SLOT(aboutQt()));

    /* ****************************************** [ QMENU ] *************************************** */
    QMenu *fileMenu = menubar->addMenu("&File");    //메뉴바에 메뉴(File) 등록  QMenu *fileMenu = menubar->addMenu("File");  : File
    QMenu *editMenu = menubar->addMenu("&Edit");
    QMenu *formatMenu = menubar->addMenu("&Format");
    QMenu *windowMenu = menubar->addMenu("&Window");
    QMenu *helpMenu = menubar->addMenu("&Help");
    QMenu *toolbarMenu = menubar->addMenu("&Toolbar");

    /* FILE */
    fileMenu->addAction(newAct);                    //메뉴에 서브메뉴(new)등록   QMenu *fileMenu = menubar->addMenu("&File"); : File의 F밑에 밑줄 */
    fileMenu->addAction(openAct);                   //메뉴에 서브메뉴(open) 등록
    fileMenu->addAction(saveAct);                   //메뉴에 서브메뉴(open) 등록
    fileMenu->addAction(saveAsAct);                   //메뉴에 서브메뉴(open) 등록
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);                   //메뉴에 서브메뉴(open) 등록

    /* EDIT */
    editMenu->addAction(undoAct);                   //메뉴에 서브메뉴(open) 등록
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);

    /* FORMAT */
    formatMenu->addAction(fontAct);
    formatMenu->addAction(colorAct);
    formatMenu->addSeparator();
    QMenu *alignMenu = formatMenu->addMenu("&Align");
        alignMenu->addAction(alignLeftAct);
        alignMenu->addAction(alignCenterAct);
        alignMenu->addAction(alignRightAct);
        alignMenu->addAction(alignJustifyAct);

    windowMenu->addAction(cascadeAct);
    windowMenu->addAction(tileAct);
    windowMenu->addSeparator();
    windowMenu->addAction(prevAct);
    windowMenu->addAction(nextAct);
    windowMenu->addSeparator();

    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
    /* ***************************************** [ Dock Widget ] **************************************** */
    QWidget *w = new QWidget(this);
    QLabel *label = new QLabel("Dock Widget", w);
    label->setObjectName("docki");
    QDockWidget *dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(w);

    /* ****************************************** [ ToolBar ] *************************************** */
    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    toolbarMenu->addAction(fileToolBar->toggleViewAction());
    toolbarMenu->addAction(dock->toggleViewAction());

    QFontComboBox *fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), textedit, SLOT(setFontPointSize(qreal)));
    QDoubleSpinBox *sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), textedit, SLOT(setFontPointSize(qreal)));

    addToolBarBreak();

    QToolBar *formatToolBar = addToolBar("&Format");
    formatToolBar->addSeparator();
    formatToolBar->addWidget(fontComboBox);
    formatToolBar->addWidget(sizeSpinBox);


    /* ****************************************** [ Status Bar ] *************************************** */
    QStatusBar *statusbar = statusBar();
    QLabel *statusLabel = new QLabel(tr("Qt Editor"), statusbar);
    statusLabel->setObjectName("statusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started", 1500);

    /* ****************************************** [ MDI Area ] *************************************** */

}

QtEditor::~QtEditor() {}

/* 서브 윈도우 생성 */
template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, T shortCut,\
                              QString toolTip, QObject *recv, const char* slot) {
    QAction *act = new QAction(text, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    act->setShortcut(QString(shortCut));
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered()), recv, slot);
    return act;
}

/* 람다함수, [액션의 쉬운구현(6)~(7)] */
template <typename T, typename Functor>
QAction *QtEditor::makeAction(QString icon, QString text, T shortCut,\
                              QString toolTip, Functor lambda) {
    QAction *act = new QAction(text, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

/* ******************************************** [ SLOT() 정의(구현) ] ********************************************* */
/* FILE */
QTextEdit *QtEditor::newFile() { //Sub-Window
    qDebug("Make New File");
    mdiArea->addSubWindow(textedit);

    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
    textedit->show();
    return textedit;
}
void QtEditor::openFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Select file to open", \
                                                    QDir::home().dirName(), "Text File (*.txt *.html, *.c *.cpp *.h)");
    qDebug() << filename;
}
void QtEditor::saveFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save", \
                                                    ".", "Text File (*.txt *.html, *.c *.cpp *.h)");
    qDebug() << filename;
}
void QtEditor::saveAsFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save", \
                                                    ".", "Text File (*.txt *.html, *.c *.cpp *.h)");
    qDebug() << filename;
}
void QtEditor::printFile() {
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Accepted) {
        QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->print(&printer);
    }
}
void QtEditor::quitFile() {

}


/* Edit */
void QtEditor::undoEdit() {
    textedit->undo();
}
void QtEditor::redoEdit() {
    textedit->redo();
}
void QtEditor::cutEdit() {
    textedit->cut();
}
void QtEditor::copyEdit() {
    textedit->copy();
}
void QtEditor::pasteEdit() {
    textedit->paste();
}
void QtEditor::zoomInEdit() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->zoomIn();
    }
}
void QtEditor::zoomOutEdit() {
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->zoomIn();
    }
}

/* Format */
void QtEditor::setFontWidget() { }
void QtEditor::setTextFont(QFont) { }
void QtEditor::setTextSize(double) { }
void QtEditor::setFont() {
    bool ok;
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = QFontDialog::getFont(&ok, textedit->currentFont(), this);
    if(ok) textedit->setCurrentFont(font);
}
void QtEditor::setColor() {
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor(textedit->textColor(), this);
    if(color.isValid()) textedit->setTextColor(color);
}
void QtEditor::alignLeft() {
    textedit->setAlignment(Qt::AlignLeft);
}
void QtEditor::alignCenter() {
    textedit->setAlignment(Qt::AlignCenter);
}
void QtEditor::alignRight() {
    textedit->setAlignment(Qt::AlignRight);
}
void QtEditor::alignJustify() {
    textedit->setAlignment(Qt::AlignJustify);
}

/* WINDOW */

void QtEditor::about() {
    QMessageBox::information(this, "QtEditor", "Copyright by kiyun");
}



