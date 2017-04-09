#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSignalMapper *mapp = new QSignalMapper(this);
    ui->lineEdit->installEventFilter(this);
//    AdvancedLineEdit *lineEdit = new AdvancedLineEdit;
//    lineEdit->show();
//    ui->verticalLayout->insertWidget(1, lineEdit);
//    QVBoxLayout *vLayout = new QVBoxLayout(this);
//    vLayout->addWidget(ui->listWidget);
//    vLayout->addWidget(lineEdit);
//    vLayout->addLayout(ui->gridLayout);
//    setLayout(vLayout);
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
    connect(ui->sqrtButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->moduleButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->factButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->cosButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->sinButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->tanButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->arccosButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->arcsinButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->arctanButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->eButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->logButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->lnButton, SIGNAL(clicked()), mapp, SLOT(map()));
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

    mapp->setMapping(ui->sqrtButton, "sqrt()");
    mapp->setMapping(ui->moduleButton, "||");
    mapp->setMapping(ui->factButton, "!");
    mapp->setMapping(ui->cosButton, "cos()");
    mapp->setMapping(ui->sinButton, "sin()");
    mapp->setMapping(ui->tanButton, "tan()");
    mapp->setMapping(ui->arccosButton, "arccos()");
    mapp->setMapping(ui->arcsinButton, "arcsin()");
    mapp->setMapping(ui->arctanButton, "arctan()");
    mapp->setMapping(ui->eButton, "e");
    mapp->setMapping(ui->logButton, "log()");
    mapp->setMapping(ui->lnButton, "ln()");
    connect(mapp,SIGNAL(mapped(QString)), this, SLOT(but_add(QString)));
    ui->lineEdit->setFocus();
}


QList<QString> Widget::split(QString str){
    QList<QString> list;
    QRegExp split("((\\d+\\.\\d+)|\\d+|\\+|\\-|\\^|\\%|\\/|\\*|\\(|\\)|(arcsin)|(arccos)|(arctan)|(sin)|(cos)|(tan)|(sqrt)|(log)|(ln)|(e)|\\|)");
    if(!split.isValid())
        qFatal("split regexp is invalid!");
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
    ui->lineEdit->setFocus();
    QKeyEvent event ( QEvent::KeyPress, str[0].toLatin1(), Qt::NoModifier);
    if(eventFilter(this, &event))return;
    int cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setText(ui->lineEdit->text().insert(cursorPosition, str));
    ui->lineEdit->setCursorPosition(cursorPosition+=str.size());
    if ( (*(str.end()-1) == ')' || *(str.end()-1) == '|') && str.length() > 1 ){
        ui->lineEdit->setCursorPosition(cursorPosition-1);
        ui->lineEdit->setFocus();
        return;
    }
}

Widget::~Widget()
{
    delete ui;
}


//------------------------------------------------------------------------------------------------
//-----------Erasing button-----------------------------------------------------------------------
//-------------\/\/\/\/-------------------------------------------------------------------

void Widget::on_pushButton_erase_clicked(){
    ui->lineEdit->setText("");
    ui->lineEdit->setFocus();
}


//------------------------------------------------------------------------------------------------
//-------Evaluation function----------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

QString Widget::evaluation(QString expression, QRegExp pattern){
    int pos{0};
//    qDebug() << "Initial pattern:" << pattern.pattern();
//    qDebug() << "Initial expression:"<< expression ;
    while ( (pos = pattern.indexIn(expression, pos))!= -1){
        QString value{"0"};
        QString action{"+"};
        QString token{""};
        int tokenCount{0};
        QString buf1 = pattern.cap(1);
        auto expressionList = split(buf1);
//        qDebug() << "Position of " << buf1 << "is" << pos;
//        qDebug() << "Current expression list" << expressionList;
        QRegularExpression digit("(\\d+)");
        for(auto listElement:expressionList){
                if(listElement=="/" || listElement=="*" || listElement=="^"||
                        listElement=="%" || listElement=="-"|| listElement=="+"){
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
//                    qDebug() << value << action << listElement << "=";
                    value = calculate(value, action, listElement);
//                    qDebug() << value;
                    tokenCount=0;
                }
        }
        expression.replace(pos, buf1.length(), value);
//        qDebug() << "Changed expression:" << expression;
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
//        QRegExp validity("(((\^|\%|\/|\*|\+|\-|\.){2,})|((\^|\%|\/|\*|\+|\-|\(|\)|\ )0\d+))|(^\.)|\.(\(|\))|(\(|\))\.|\(\)|\)\(|^(0\d)|(\((\^|\%|\/|\*))|((\^|\%|\/|\*|\+|\=)\))|(\) *\d)|(\d *\()");
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
        if(fullExpressionList.first()!="(")break;
        QList<QString>::iterator start{NULL};
        QString bracketBoof;
        notEnd=false;
        for(QList<QString>::iterator  t = fullExpressionList.begin();t!=fullExpressionList.end();t++){
//            qDebug() << "Loop in while's for";
            notEnd=true;
            if(*t == "("){
                start=t;
                bracketBoof="";
                continue;
            }
            if(*t==")"){
//                qDebug() << "Erase list:";
                for(;"("!=*t;(t=fullExpressionList.erase(t))--);
                QRegExp square("( *(\\d+\\.\\d+|\\d+) *(\\^) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+))");
                QRegExp highOperator("( *(\\d+\\.\\d+|\\d+) *(\\*|\\/|\\%) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+))");
                QRegExp nums("( *(\\+|\\-)? *(\\d+\\.\\d+|\\d+) *(\\+|\\-) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+))");
                *t = evaluation(evaluation(evaluation(bracketBoof, square), highOperator),nums);
                break;
            }
            bracketBoof+=*t;
        }
//        qDebug() << "Loop in while";
    }

//------------------------------------------------------------------------------------------------
//-------Final result-----------------------------------------------------------------------------
//--------\/\/\/\/--------------------------------------------------------------------------------
    ui->lineEdit->setText(fullExpressionList.first());
    ui->listWidget->addItem(str + "=" + fullExpressionList.first());
    ui->lineEdit->setFocus();
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
    ui->lineEdit->setFocus();
}



void Widget::on_lineEdit_textChanged(const QString &arg1)
{
//    QString str = arg1;
//    int cursorPosition = ui->lineEdit->cursorPosition();
//    if( (cursorPosition) > str.size() || (cursorPosition == 0))
//        return;
//    if ( (str[cursorPosition-1] == ')' && str[cursorPosition] == ')')
//         || (str[cursorPosition-1] == '|' && str[cursorPosition] == '|') ){
//        ui->lineEdit->setText(str.remove(cursorPosition,1));
//        ui->lineEdit->setCursorPosition(cursorPosition+1);
//    }
}


bool Widget::eventFilter(QObject *watched, QEvent *event){
    if( (event->type() == QEvent::KeyPress) ){
        QKeyEvent* keyEvent= (QKeyEvent *)event;
        QString str = ui->lineEdit->text();
        int cursorPosition = ui->lineEdit->cursorPosition();
        QRegularExpression doubleOperators("(\\^|\\%|\\/|\\*|\\+|\\-|\\.|\\)|\\|)");
//        if(!doubleOperators.isValid()) qFatal("Error in doubleOperators regexp!");

        if ( ((cursorPosition-1) >= 0) &&
                (QRegularExpressionMatch(doubleOperators.match((QString)keyEvent->key())).hasMatch()) &&
                 (str[cursorPosition] == (QChar)keyEvent->key())){
            ui->lineEdit->setCursorPosition(cursorPosition+1);
            return true;
        }
        doubleOperators.setPattern("(\\^|\\%|\\/|\\*|\\+|\\-|\\.)");
//        if(!doubleOperators.isValid()) qFatal("Error in doubleOperators regexp!");
        if ( ((cursorPosition-1) >= 0) &&
                (QRegularExpressionMatch(doubleOperators.match((QString)keyEvent->key())).hasMatch()) &&
                 (str[cursorPosition-1] == (QChar)keyEvent->key()))
            return true;


        if ( ((QString)keyEvent->key() == "(")){
            ui->lineEdit->insert("()");
            ui->lineEdit->setCursorPosition(cursorPosition+1);
            return true;
        }
        if ((QString)keyEvent->key() == "|"){
            ui->lineEdit->insert("||");
            ui->lineEdit->setCursorPosition(cursorPosition+1);
            return true;
        }
        if ( ((cursorPosition-1) >= 0) &&
                (keyEvent->key() == Qt::Key_Backspace) &&
                ( ((str[cursorPosition] == ')') && (str[cursorPosition-1] == '(')) ||
                  ((str[cursorPosition] == '|') && (str[cursorPosition-1] == '|'))) ){
            str.remove(cursorPosition-1, 2);
            ui->lineEdit->setText(str);
            ui->lineEdit->setCursorPosition(cursorPosition-1);
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}



// correct oversteping double brackets
