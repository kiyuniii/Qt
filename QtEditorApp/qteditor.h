#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMessageBox>

class QLabel;
class QMdiArea;
class QTextEdit;

class QtEditor : public QMainWindow //QWidget::QMainWindow
{
    Q_OBJECT
    QMdiArea *mdiArea;

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();
private:
    template <typename T>
    QAction *makeAction(QString icon, QString text, T shortCut, QString toolTip, QObject* recv, const char* slot);

    template <typename T, typename Functor>
    QAction *makeAction(QString icon, QString text, T shortCut, QString toolTip, Functor lambda);
    QTextEdit *textedit;

public slots:
    /* File */
    QTextEdit *newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void printFile();
    void quitFile();
    /* Edit */
    void undoEdit();
    void redoEdit();
    void copyEdit();
    void cutEdit();
    void pasteEdit();
    void zoomInEdit();
    void zoomOutEdit();

    /* */
    void alignLeft();
    void alignCenter();
    void alignRight();
    void alignJustify();

    void setFontWidget();
    void setTextFont(QFont font);
    void setTextSize(qreal size);

    void setColor();
    void setFont();

    /* HELP */
    void about();
    /* ============================================= */
};
#endif // QTEDITOR_H
