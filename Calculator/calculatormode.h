#ifndef CALCULATORMODE_H
#define CALCULATORMODE_H

#include <QWidget>

//CalculatorMode 클래스 선언
class CalculatorMode : public QWidget {
private:
    int num1;
    char op;
    int num2;
    Q_OBJECT
public:
    explicit CalculatorMode(QWidget *parent = nullptr);
    CalculatorMode(int num1=0, char op=' ', int num2=0);
    void input();
    double doCalculate();
signals:
};

#endif // CALCULATORMODE_H
