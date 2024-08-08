#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>

class QLabel;
class QMdiArea;
class QTextArea;

class QtEditor : public QMainWindow //QWidget::QMainWindow
{
    Q_OBJECT
    QMdiArea *mdiArea;

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();
private:
    QAction *makeActionMethod(QString icon, QString text, QString shortCut,\
                        QString toolTip, QObject* recv, const char* slot);
    template <typename T>
    QAction *makeActionTemplate(QString icon, QString text, T shortCut,\
                                QString toolTip, QObject* recv, const char* slot);
    template <typename T, typename Functor>
    QAction *makeActionLambda(QString icon, QString text, T shortCut,\
                                QString toolTip, Functor lambda);
    QTextEdit *textedit;

public slots:
    void openFile();
    void quitFile();
    void undoFile();
    void redoFile();
    QTextEdit *newFile();

    //void alignText();
};
#endif // QTEDITOR_H
