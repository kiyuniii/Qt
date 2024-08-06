#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>
//#define WIDTH 4 -> const qint32 WIDTH = 4를 더 추천함

class QLabel;
class QPushButton;

//CalculatorButton 클래스 선언
class CalculatorWidget : public QWidget {

    /* Q_OBJECT
 * : 사용자 정의 슬롯, 사용자 정의 시그널을 위해 클래스 정의부에 추가하는 매크로
 */
    Q_OBJECT

public:
    explicit CalculatorWidget(QWidget *parent = nullptr);
    ~CalculatorWidget();
    const char ButtonChar[16][2];
private:
    QLabel* label;                  //포인터변수 선언 -> connect의 매개변수로 사용, connect(label, SIGNAL, ..., SLOT);
    QVector<QPushButton*> buttons;  //컨테이너 클래스 사용
    QString num1, op;
    bool isFirst;
    const qint32 WIDTH = 4;


    /* 사용자 정의 시그널
 * signals:
 * .h에 선언 (void형), 과거pp형으로 명명
 * 구현 X
 */
signals:

/* 사용자 정의 슬롯
 * 접근지정자 + slots:
 * .h에 선언 (void형)
 * .cpp에 정의(구현)
 */
public slots:
    void setNum();
    void setOp();
};

#endif // CALCULATORWIDGET_H
