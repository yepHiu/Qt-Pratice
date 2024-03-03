#include "calculator.h"
#include "ui_calculator.h"

double calcVal =0.0;
double memSum=0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

// 构造函数
// 在这里可以实现窗口初始化时候该有的操作
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);


    ////////////////////////////////////////自定义的初始化内容//////////////////////////////////////
    // 初始化显示窗口内容
    // ui->Display是一个指向UI界面中名为Display的QLabel对象的指针。setText()函数用于设置该标签的文本内容
    // 使用QString::number将值转换为文本内容
    ui->Display->setText(QString::number(calcVal));

    // 将数字按钮的released信号与NumPressed槽函数进行链接
    QPushButton *numButtons[10];// 创建指针数组
    //分配slot
    for(int i=0; i<10;i++){ // 分配槽函数
        QString buttName = "Button" + QString::number(i);
        numButtons[i]=Calculator::findChild<QPushButton *>(buttName);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(NumPressed()));// 点击任何数字按钮的时候NumPressed将会被调用
    }

    // 将信号与槽函数进行链接
    connect(ui->Add,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,SLOT(MathButtonPressed()));

    // 等号按键信号链接
    connect(ui->Equal,SIGNAL(released()),this,SLOT(EqualButtonPressed()));
    // 符号按键信号链接
    connect(ui->ChangeSign,SIGNAL(released()),this,SLOT(ChangeNumberSign()));
    // 清零按键信号链接
    connect(ui->Clear,SIGNAL(released()),this,SLOT(ClearButtonPressed()));
    // Mem按键信号链接
    connect(ui->MemAdd,SIGNAL(released()),this,SLOT(MemButtonPressed()));
    connect(ui->MemGet,SIGNAL(released()),this,SLOT(MemButtonPressed()));
    connect(ui->MemClear,SIGNAL(released()),this,SLOT(MemButtonPressed()));



}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();// 获取发送信号按钮的指针
    QString butVal = button->text();// 读取该按钮的按钮值，也就是按钮上的文本内容
    QString displayVal = ui->Display->text();

    // 获取显示模块中的文本内容
    if((displayVal.toDouble()==0)||displayVal.toDouble()==0.0f){
        ui->Display->setText(butVal);// 如果是0或者0.0，将文本设置为被点击按钮的值 也就是获取数字
    }else{
        QString newVal=displayVal+butVal;// 不是就将点击的按钮值最佳到显示的文本后面
        double dblNewVal=newVal.toDouble();// 更新新的浮点数据
        ui->Display->setText(QString::number(dblNewVal,'g',16));// 将新的文本这是为浮点数并使用科学计数法表示，并保留16位
    }
}

/**
 * @brief Calculator::MathButtonPressed
 */
void Calculator::MathButtonPressed(){

    divTrigger=false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();// 获取的显示的文本内容
    calcVal=displayVal.toDouble();// 将获取的文本内容转为浮点数

    QPushButton *button = (QPushButton *)sender(); //获取发送信号的按钮指针
    QString butVal=button->text();// 获取这个按钮的内容

    // 按钮根据运算符号进行分类
    if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0){
        divTrigger=true;
    }else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0){
        multTrigger=true;
    }else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0){
        addTrigger=true;
    }else if(QString::compare(butVal,"-",Qt::CaseInsensitive)==0){
        subTrigger=true;
    }

    // 清空显示
    ui->Display->setText("");
}

/**
 * @brief Calculator::EqualButtonPressed
 */
void Calculator::EqualButtonPressed(){
    double solution = 0.0;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    // 判断是什么运算
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution=calcVal+dblDisplayVal;
        }else if(subTrigger){
            solution=calcVal-dblDisplayVal;
        }else if(multTrigger){
            solution=calcVal*dblDisplayVal;
        }else if(divTrigger){
            solution=calcVal/dblDisplayVal;
        }else{

        }
    }

    // 显示计算结果
    ui->Display->setText(QString::number(solution));
}

/**
 * @brief Calculator::ChangeNumberSign
 */
void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();

    // 声明表达式的时候，编译器推荐声明一个正常的
    static QRegularExpression reg("[-+]?[0-9.]*");// 声明一个正则表达规则
    if(reg.match(displayVal).hasMatch()){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        // 显示更改后的文本
        ui->Display->setText(QString::number(dblDisplayValSign));

    }
}

/**
 * @brief ClearButtonPressed
 */
void Calculator::ClearButtonPressed(){
    ui->Display->setText("");
    calcVal=0.0;
    memSum=0.0;
}

/**
 * @brief MemButtonPressed
 */
void Calculator::MemButtonPressed(){
    QPushButton *button=(QPushButton *)sender();// 获取
    QString butVal=button->text();// 获取文本

    QString displayVal=ui->Display->text();
    double dbleDisplayVal=displayVal.toDouble();

    if(QString::compare(butVal,"M+",Qt::CaseInsensitive)==0){
        memSum+=dbleDisplayVal;
        ui->Display->setText("");
    }else if(QString::compare(butVal,"M-",Qt::CaseInsensitive)==0){
        memSum-=dbleDisplayVal;
        ui->Display->setText("");
    }else if(QString::compare(butVal,"M",Qt::CaseInsensitive)==0){
        ui->Display->setText(QString::number(memSum));
    }else{

    }

}
