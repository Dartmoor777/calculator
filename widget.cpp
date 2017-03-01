#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSignalMapper *mapp = new QSignalMapper(this);
    connect(ui->pushButton0, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton1, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton2, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton3, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton4, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton5, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton6, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton7, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton8, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton9, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_min, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_dev, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_per, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_step, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_lfbracket, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->pushButton_rbracket, SIGNAL(clicked()), mapp, SLOT(map()));
    mapp->setMapping(ui->pushButton0, "0");
    mapp->setMapping(ui->pushButton1, "1");
    mapp->setMapping(ui->pushButton2, "2");
    mapp->setMapping(ui->pushButton3, "3");
    mapp->setMapping(ui->pushButton4, "4");
    mapp->setMapping(ui->pushButton5, "5");
    mapp->setMapping(ui->pushButton6, "6");
    mapp->setMapping(ui->pushButton7, "7");
    mapp->setMapping(ui->pushButton8, "8");
    mapp->setMapping(ui->pushButton9, "9");
    mapp->setMapping(ui->pushButton_plus, "+");
    mapp->setMapping(ui->pushButton_min, "-");
    mapp->setMapping(ui->pushButton_mul, "*");
    mapp->setMapping(ui->pushButton_dev, "/");
    mapp->setMapping(ui->pushButton_dot, ".");
    mapp->setMapping(ui->pushButton_per, "%");
    mapp->setMapping(ui->pushButton_step, "^");
    mapp->setMapping(ui->pushButton_lfbracket, "(");
    mapp->setMapping(ui->pushButton_rbracket, ")");
    connect(mapp,SIGNAL(mapped(QString)), this, SLOT(but_add(QString)));
}


QList<QString> Widget::split(QString str){
    QList<QString> list;
    QRegExp split("((\\d+\\.\\d+)|\\d+|\\+|\\-|\\^|\\%|\\/|\\*|\\(|\\))");
    int pos = 0;
    while ( (pos = split.indexIn(str, pos))!= -1){					//Creating an array of glyphs
        list << split.cap(1);
        pos+=split.matchedLength();
    }
    return list;
}


//------------------------------------------------------------------------------------------------
//------Calculating function----------------------------------------------------------------------
//----------\/\/\/\/----------------------------------------------------------------------

QString Widget::calculate(QString first, QString action, QString second){
        double fir = first.toDouble();
        double sec = second.toDouble();
        if ( action == "+") return action.setNum(fir+sec);
        if ( action == "-") return action.setNum(fir-sec);
        if ( action == "*") return action.setNum(fir*sec);
        if ( action == "/") return action.setNum(fir/sec);
        if ( action == "%") return action.setNum((int)fir%(int)sec);
        if ( action == "^") return action.setNum(qPow(fir, sec));
        qFatal("Redundant operator?");
}


//------------------------------------------------------------------------------------------------
//-----Adding button------------------------------------------------------------------------------
//-------\/\/\/\/-------------------------------------------------------------------------

void Widget::but_add(QString str){
    int cursorPosition=ui->lineEdit->cursorPosition();
    ui->lineEdit->setText(ui->lineEdit->text().insert(cursorPosition, str));
    ui->lineEdit->setCursorPosition(cursorPosition+1);
}

Widget::~Widget()
{
    delete ui;
}


//------------------------------------------------------------------------------------------------
//-----------Erasing button-----------------------------------------------------------------------
//-------------\/\/\/\/-------------------------------------------------------------------

void Widget::on_pushButton_erase_clicked(){
    if(ui->lineEdit->text().isEmpty())return;
    int cursorPosition=ui->lineEdit->cursorPosition()-1;
    ui->lineEdit->setText(ui->lineEdit->text().remove(cursorPosition, 1));
    ui->lineEdit->setCursorPosition(cursorPosition);
}


//------------------------------------------------------------------------------------------------
//-------Evaluation function----------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

QString Widget::evaluation(QString expression, QRegExp pattern){
    int pos{0};
    qDebug() << "Initial pattern:" << pattern.pattern();
    qDebug() << "Initial expression:"<< expression ;
    while ( (pos = pattern.indexIn(expression, pos))!= -1){
        QString value{"0"};
        QString action{"+"};
        QString token{""};
        int tokenCount{0};
        QString buf1 = pattern.cap(1);
        auto expressionList = split(buf1);
        qDebug() << "Position of " << buf1 << "is" << pos;
        qDebug() << "Current expression list" << expressionList;
        QRegularExpression digit("(\\d+)");
        for(auto listElement:expressionList){
                if(listElement=="/" || listElement=="*" || listElement=="^"|| listElement=="%" || listElement=="-"|| listElement=="+"){
                    if(!tokenCount){
                        action=listElement;
                        tokenCount++;
                    }
                    else{
                        token=listElement;
                        tokenCount++;
                    }
                    continue;
                }
                if(QRegularExpressionMatch(digit.match(listElement, 0)).hasMatch()){    // looking for decimals
                    if(tokenCount==2)listElement.prepend(token);
                    qDebug() << value << action << listElement << "=";
                    value = calculate(value, action, listElement);
                    qDebug() << value;
                    tokenCount=0;
                }
        }
        expression.replace(pos, buf1.length(), value);
        qDebug() << "Changed expression:" << expression;
        pos=0;
    }
    return expression;
}
//------------------------------------------------------------------------------------------------
//----------Calculating button--------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

void Widget::on_pushButton_eq_clicked()
{

QString str{ui->lineEdit->text()};
//------------------------------------------------------------------------------------------------
//-----------Checking validity--------------------------------------------------------------------
//----------------\/\/\/\/------------------------------------------------------------------------
    {
        if(str.isEmpty())return;
        QRegExp validity("(((\\^|\\%|\\/|\\*|\\+|\\-|\\.){2,})|((\\^|\\%|\\/|\\*|\\+|\\-|\\(|\\)|\\ )0\\d+))|(^\\.)|\\.(\\(|\\))|(\\(|\\))\\.|\\(\\)|\\)\\(|^(0\\d)|(\\((\\^|\\%|\\/|\\*))|((\\^|\\%|\\/|\\*|\\+|\\=)\\))|(\\) *\\d)|(\\d *\\()");
        if (validity.indexIn(str, 0)!=-1){
            QMessageBox::information(this, "", "Your equation is invalid!");
            return;
        }
        validity.setPattern("[^\\d\\+\\-\\/\\*\\%\\.\\^ \\(\\)]");
        if (validity.indexIn(str, 0)!=-1){
            QMessageBox::information(this, "", "There are invalid characters!");
            return;
        }
        int lbracket{0}, rbracket{0};
        for(auto t:str){
            if(t=='(')lbracket++;
            if(t==')')rbracket++;
        }
        if(lbracket!=rbracket){
            QMessageBox::information(this, "", "Missed a bracket?");
            return;
        }
    }

//------------------------------------------------------------------------------------------------
//------Creating a list of previous states--------------------------------------------------------
//-------------\/\/\/\/---------------------------------------------------------------------------

    if(revertList.size()>10){
        revertList.removeFirst();
        ui->listWidget->removeItemWidget(ui->listWidget->takeItem(0));
    }
    revertList.append(str);
    auto fullExpressionList = split(str);

    fullExpressionList.append(")");
    fullExpressionList.prepend("(");
    bool notEnd{true};
    while(notEnd){
        QList<QString>::iterator start{NULL};
        QString bracketBoof;
        notEnd=false;
        if(fullExpressionList.first()!="(")break;
        for(QList<QString>::iterator  t = fullExpressionList.begin();t!=fullExpressionList.end();t++){
            qDebug() << "Loop in while's for";
            notEnd=true;
            if(*t == "("){
                start=t;
                bracketBoof="";
                continue;
            }
            if(*t==")"){
                qDebug() << "Erase list:";
                for(;"("!=*t;(t=fullExpressionList.erase(t))--)qDebug() << *t;
                QRegExp square("( *(\\d+\\.\\d+|\\d+) *(\\^) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+))");
                QRegExp highOperator("( *(\\d+\\.\\d+|\\d+) *(\\*|\\/|\\%) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+))");
                QRegExp nums("( *(\\+|\\-)? *(\\d+\\.\\d+|\\d+) *(\\+|\\-) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+))");
                *t = evaluation(evaluation(evaluation(bracketBoof, square), highOperator),nums);
                break;
            }
            bracketBoof+=*t;
        }
        qDebug() << "Loop in while";
    }

//------------------------------------------------------------------------------------------------
//-------Final result-----------------------------------------------------------------------------
//--------\/\/\/\/--------------------------------------------------------------------------------
    ui->lineEdit->setText(fullExpressionList.first());
    ui->listWidget->addItem(str + "=" + fullExpressionList.first());
}

//------------------------------------------------------------------------------------------------
//------Returning of previous state---------------------------------------------------------------
//---------\/\/\/\/-------------------------------------------------------------------------------

void Widget::on_pushButton_revert_clicked()
{
    if(revertList.isEmpty())return;
    ui->lineEdit->setText(revertList.last());
    ui->listWidget->removeItemWidget(ui->listWidget->takeItem(revertList.size()-1));
    revertList.removeLast();
}
