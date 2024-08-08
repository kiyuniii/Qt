#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

class QtEditor : public QMainWindow //QWidget::QMainWindow
{
    Q_OBJECT

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
public slots:
    void newFile();
    void openFile();
    void quitFile();
    void undoFile();
};
#endif // QTEDITOR_H
