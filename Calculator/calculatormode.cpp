#include "calculatormode.h"
#include <iostream>
using namespace std;

//CalculatorMode 생성자,멤버 정의
CalculatorMode::CalculatorMode(QWidget *parent)
    : QWidget{parent}       //부모클래스(QWidget)의 생성자 중 매개변수가 하나(parent)인 생성자를 상속한다.
{ }

CalculatorMode::CalculatorMode(int num1, char op, int num2)
    : num1(num1), op(op), num2(num2)
{ }

void CalculatorMode::input()
{
    cin >> num1 >> op >> num2;
}

double CalculatorMode::doCalculate() {
    double result;
    switch(op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
        default: result = 0;                    // ***
    }
    return result;
}
