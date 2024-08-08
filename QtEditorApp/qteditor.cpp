#include "qteditor.h"
#include <QTextEdit>
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


/* ****************************************** [ Menu Bar ] *************************************** */
    QMenuBar *menubar = new QMenuBar(this);         //여기서 menubar는 카멜표기법을 사용하지 않는데, 이미 클래스에 property가 있기 때문
    setMenuBar(menubar);                            //QMenuBar *menubar = this->menuBar();

    /* 1.일반적인 방법으로 구현
     * File Menu */
    QAction *newAct = new QAction(QIcon(":/images/new.png"), "&new", this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("make new file"));      //아래에 생성되는 상태바가 있어야 statusTip이 보인다.
    connect(newAct, SIGNAL(triggered()), SLOT(newFile()));;
    /* Open Menu */
    QAction *openAct = new QAction(QIcon(":/images/open.png"), "&Open", this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("make new file"));
    connect(openAct, SIGNAL(triggered()), SLOT(openFile()));;

    /* 2.메소드, Quit Menu */
    QAction *quitAct = makeActionMethod(":/images/quit.png", tr("&Quit"), tr("Ctrl+Q"), tr("quit this Program"), this, SLOT(quitFile()));
    QAction *undoAct = makeActionMethod(":/images/undo.png", tr("&Undo"), tr("Ctrl+Z"), tr("Undo"), this, SLOT(undoFile()));
    QAction *redoAct = makeActionMethod(":/images/redo.png", tr("&Redo"), tr("Ctrl+Shift+Z"), tr("Redo"), this, SLOT(redoFile()));

    /* 3. 템플릿,  */
    /* 4. 람다함수,  */
    /* File */

    /* Align */
    QAction *alignLeftAct = new QAction("&Left", this);
    QAction *alignCenterAct = new QAction("&Center", this);
    QAction *alignRightAct = new QAction("&Right", this);
    QAction *alignJustifyAct = new QAction("&Justify", this);
    connect(alignLeftAct, &QAction::triggered, this, [=](){ textedit->setAlignment(Qt::AlignLeft); });
    connect(alignCenterAct, &QAction::triggered, this, [=](){ textedit->setAlignment(Qt::AlignCenter); });
    connect(alignRightAct, &QAction::triggered, this, [=](){ textedit->setAlignment(Qt::AlignRight); });
    connect(alignJustifyAct, &QAction::triggered, this, [=](){ textedit->setAlignment(Qt::AlignJustify); });

    /* 메뉴바(menubar)에 메뉴(File)등록 */
    QMenu *fileMenu = menubar->addMenu("&File");    //메뉴바에 메뉴(File) 등록  QMenu *fileMenu = menubar->addMenu("File");  : File
    QMenu *editMenu = menubar->addMenu("&Edit");
    //QMenu *windowMenu = menubar->addMenu("&Window");
    QMenu *toolbarMenu = menubar->addMenu("&Toolbar");
    QMenu *formatMenu = menubar->addMenu("&Format");

    fileMenu->addAction(newAct);                    //메뉴에 서브메뉴(new)등록   QMenu *fileMenu = menubar->addMenu("&File"); : File의 F밑에 밑줄 */
    fileMenu->addAction(openAct);                   //메뉴에 서브메뉴(open) 등록
    fileMenu->addAction(quitAct);                   //메뉴에 서브메뉴(open) 등록
    editMenu->addAction(undoAct);                   //메뉴에 서브메뉴(open) 등록
    editMenu->addAction(redoAct);
    QMenu *alignMenu = formatMenu->addMenu("&Align");
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);

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

QTextEdit *QtEditor::newFile() {
    qDebug("Make New File");
    QTextEdit *textedit = new QTextEdit;
    mdiArea->addSubWindow(textedit);
    textedit->show();
    return textedit;
}

void QtEditor::openFile() {
    qDebug("Open existing File");
}
/* <QApplication> */
void QtEditor::quitFile() {
    qApp->quit();
    qDebug("Quit this Program");
}

/* <QTextEdit> */
void QtEditor::undoFile() {
    textedit->undo();
    qDebug("Undo Program");
}
void QtEditor::redoFile() {
    textedit->redo();
    qDebug("Redo Program");
}


/* 메소드, [액션의 쉬운구현(1)~(3)] */
QAction *QtEditor::makeActionMethod(QString icon, QString text, QString shortCut,\
                              QString toolTip, QObject* recv, const char* slot) {
    QAction *act = new QAction(text, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered()), recv, slot);
    return act;
}

/* 템플릿, [액션의 쉬운구현(4)~(5)] */
template <typename T>
QAction *QtEditor::makeActionTemplate(QString icon, QString text, T shortCut,\
                                      QString toolTip, QObject* recv, const char* slot) {
    QAction *act = new QAction(text, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered()), recv, slot);
    return act;
}

/* 람다함수, [액션의 쉬운구현(6)~(7)] */
template <typename T, typename Functor>
QAction *QtEditor::makeActionLambda(QString icon, QString text, T shortCut,\
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

