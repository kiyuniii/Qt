#include "calculatorwidget.h"

//CalculatorButton 생성자 정의
CalculatorWidget::CalculatorWidget(QWidget *parent)
    : QWidget{parent},

    ButtonChar{
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+",
    } //초기화 리스트
{
    /* label = new QLabel("0", this);
     * 이미 헤더에서 선언되어 'QLabel *'는 생략된 상태
     *
     * "객체의 동적생성"
     * * 객체 동적생성:    Circle *p = new Circle(radius);
     * * 객체배열 동적생성: Circle *p = new Circle[3]{Circle(1), Circle(2), Circle(3)};
     * : 객체가 차지하고 있는 메모리영역을 가리키는 포인터를 생성
     * : 해당 포인터는 '->'를 통해 객체의 멤버에 접근
     * : '.'는 객체포인터가 아닌 객체가 멤버에 접근할 때 사용
     *
     * 따라서 label은 "객체 포인터 변수", 객체의 메모리값을 저장 */
    label = new QLabel("0", this);
    label->setGeometry(10, 5, 230, 40);
    /* 열거형 상수(enum values)
     * Qt::AlignRight   텍스트, 콘텐츠를 위젯의 오른쪽 정렬
     * Qt::AlignVCenter 텍스트, 콘텐츠를 위젯의 수직중앙 정렬
     *
     * 논리연산자가 아닌 비트연산자를 사용 (각 정렬옵션이 고유한 비트위치를 가지기 때문)
     *
     */
    label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    //QPushButton *buttons = new QPushButton;

    //buttons[][] <-> ButtonChar[][]
    for(int y=0; y<WIDTH; y++) {
        for(int x=0; x<WIDTH; x++) {
            /* buttons.append(new QPushButton(ButtonChar[x+y*WIDTH], this));
             * *
             */
            buttons.append(new QPushButton(ButtonChar[x+y*WIDTH], this));
            buttons.at(x+y*WIDTH)->setGeometry(5+60*x, 50+60*y, 60, 60);
        }
    }

    //연결_숫자(0~9)
    /*
     * connect(buttons.at(13), SIGNAL(clicked()), this, SLOT(setNum()));
     * == connect(buttons.at(13), &QPushButton::clicked, this, &CalculatorWidget::setNum);
     * QPushButton -> clicked(), CalculatorWidget(사용자정의) -> setNum()*/
    connect(buttons.at(0), &QPushButton::clicked, this, &CalculatorWidget::setNum);

    /* connect()의 3번째 인자가 'this'인 경우 생략가능
     * SIGNAL과 SLOT은 타입만 서로 넘겨줄 수 있고, 서로 같은 타입이어야 한다.*/
    connect(buttons.at(1), SIGNAL(clicked()), SLOT(setNum()));
    connect(buttons.at(2), SIGNAL(clicked()), SLOT(setNum()));
    connect(buttons.at(4), SIGNAL(clicked()), SLOT(setNum()));
    connect(buttons.at(5), SIGNAL(clicked()), SLOT(setNum()));
    connect(buttons.at(6), SIGNAL(clicked()), SLOT(setNum()));
    connect(buttons.at(8), SIGNAL(clicked()), SLOT(setNum()));
    connect(buttons.at(10), SIGNAL(clicked()), SLOT(setNum()));
    connect(buttons.at(12), SIGNAL(clicked()), SLOT(setNum()));

    //연결_'C'
    /* 람다 함수
     * connect(quit, &QPushButton::clicked, qApp, &QApplication::quit);
     * connect(quit, &QPushButton::clicked, [] () { qApp->quit(); });
     * [] : 캡쳐리스트 -> '=': '값'으로 캡쳐, '&': '참조'로 캡쳐
    connect(buttons.at(9), SIGNAL(clicked()), SLOT(setNum()));
     *
     * QLabel -> setText()
     * QLabel *label; : label = QLabel형 포인터
     *
     * &QPushButton::clicked -> Compile 가능
     * SIGNAL(clicked()) -> Compile 에러 (No Matching member function for call to 'connect' */

    /* text(): 위젯의 현재 텍스트를 반환  QString text();
     * setText(): 위젯의 텍스트를 설정   void setText(const QString &)*/
    connect(buttons.at(13), &QPushButton::clicked, this, [=]() { label->setText("0");});
    //연결_연산자
    connect(buttons.at(3), SIGNAL(clicked()), SLOT(setOp()));
    connect(buttons.at(7), SIGNAL(clicked()), SLOT(setOp()));
    connect(buttons.at(11), SIGNAL(clicked()), SLOT(setOp()));
    connect(buttons.at(15), SIGNAL(clicked()), SLOT(setOp()));
    //연결_'='
    connect(buttons.at(14), &QPushButton::clicked, this, [=]() {

        /* result 변수를 qreal 타입으로 선언, 초기화
         * qreal은 Qt에서 사용하는 실수 타입
         * 'float' 또는 'double'을 사용할 수 있으며 기본적으로 'qreal'은 'double'로 정의됨
         * 플랫폼 간의 호환성과 Qt의 내부계산에서 일관성을 유지하기 위해 사용*/
        qreal result = 0;   //==double result = 0;
        isFirst = true;
        // Qstring num1, op;
        if(op == "+") result = num1.toDouble() + label->text().toDouble();
        else if(op == '-') result = num1.toDouble() - label->text().toDouble();
        else if(op == 'x') result = num1.toDouble() * label->text().toDouble();
        else if(op == '/') {

            /* if(label->text().toDouble()) result = num1.toDouble() / label->text().toDouble();
             * Q. 왜 if의 조건문 내 '!=0'이 없어도 가능한걸까?
             * A. if의 조건문 ()내에 0이 아닌 값이 오면 true로 평가되므로 이는 해당 조건문의 실행조건과 같다.
             */
            if(label->text().toDouble()) result = num1.toDouble() / label->text().toDouble();
            else {
                label->setText("Error: Cannot divide by Zero");
                /* return;
                 * 람다함수의 실행을 중지하고 제어를 호출된 곳으로 반환
                 */
                return;
            }
        }
        label->setText(QString::number(result));    //result(qreal형)을 string형으로 변환, number() = QString클래스의 멤버
    });
    setMinimumSize(250, 295);
    setMaximumSize(250, 295);
    setWindowTitle("Calculator");
}

//소멸자 정의
CalculatorWidget::~CalculatorWidget() {
    delete label;   //메모리 동적할당 해제
    buttons.clear();
    //Q_FOREACH(auto b, buttons) delete b;
}

//setNum()
void CalculatorWidget::setNum() {

    /* dynamic_cast == C++ 스타일 명시적 캐스팅
     * * 캐스팅 = 데이터 타입 변환과정
     *
     * * sender()가 반환하는 '포인터'가 'QPushButton' 타입인지 확인하고 맞다면 'QPushButton
     * * * 맞다면 'QPushButton' 타입의 포인터로 button을 정의
     * * * 아니면 nullptr의 포인터로 button을 정의
     *
     * 'QPushButton *'는 없어도 될 것 같지만, 포인터변수 'button'가 이전에 선언되지 않았으므로 작성함.
    */

    /* sender()
     * : QObject(클래스)의 멤버함수
     * - 현재 실행중인 슬롯이 시그널에 의해 호출되었을 때, 그 시그널을 보낸 객체의 포인터를 반환
     * connect(sender(), SIGNAL(signal), receiver, SLOT(slot));
     * * receiver()란 멤버함수는 없으며, 해당 자리엔 '시그널을 받을 객체'를 내가 설정하면 되는거다. */

    /*
     */
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    QString buttonStr;
    if(button != nullptr) buttonStr = button->text();
    if(label != nullptr) {
        QString labelStr = label->text();
        label->setText((labelStr == "0" || isFirst)?buttonStr:labelStr+buttonStr);
        isFirst = false;
    }
}

void CalculatorWidget::setOp() {

}
/* 2차원 -> 1차원 알고리즘
 * for(int y=0; y<WIDTH; y++) {
 *    for(int x=0; x<WIDTH; x++) {
 *       QPushButton *button = new QPushButtutton[x+y*WIDTH] = new QPushButton(ButtonChar[x+y*WIDTH], this);
 *       //QPushButon
 *
 * [y][x] : y=row, x=col;
 * [0][0] [0][1] [0][2] [0][3]    0  1  2  3
 * [1][0] [1][1] [1][2] [1][3]    4  5  6  7    ex)[3][2] = 14
 * [2][0] [2][1] [2][2] [2][3]    8  9 10 11    x = 2, y = 3
 * [3][0] [3][1] [3][2] [3][3]   12 13 14 15    -> 2 + 3*4 = 14
*/

