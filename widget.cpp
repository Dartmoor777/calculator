#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSignalMapper *mapp = new QSignalMapper(this);
    ui->lineEdit->installEventFilter(this);
    connect(ui->conversionFromList, SIGNAL(currentIndexChanged(int)), this, SLOT(onConversionListChange()));
    connect(ui->conversionToList, SIGNAL(currentIndexChanged(int)), this, SLOT(onConversionListChange()));
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
    connect(ui->ctgButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->arcctgButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->cosButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->sinButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->tanButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->arccosButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->arcsinButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->arctanButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->eButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->logButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->lnButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->expButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->lgButton, SIGNAL(clicked()), mapp, SLOT(map()));
    connect(ui->piButton, SIGNAL(clicked()), mapp, SLOT(map()));
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
    mapp->setMapping(ui->moduleButton, "abs()");
    mapp->setMapping(ui->ctgButton, "ctg()");
    mapp->setMapping(ui->arcctgButton, "arcctg()");
    mapp->setMapping(ui->cosButton, "cos()");
    mapp->setMapping(ui->sinButton, "sin()");
    mapp->setMapping(ui->tanButton, "tan()");
    mapp->setMapping(ui->arccosButton, "arccos()");
    mapp->setMapping(ui->arcsinButton, "arcsin()");
    mapp->setMapping(ui->arctanButton, "arctan()");
    mapp->setMapping(ui->eButton, "e");
    mapp->setMapping(ui->expButton, "exp()");
    mapp->setMapping(ui->logButton, "log");
    mapp->setMapping(ui->lgButton, "lg()");
    mapp->setMapping(ui->lnButton, "ln()");
    mapp->setMapping(ui->piButton, "pi");
    connect(mapp,SIGNAL(mapped(QString)), this, SLOT(but_add(QString)));
    ui->lineEdit->setFocus();
}


QLinkedList<QString> Widget::split(QString str){
    QLinkedList<QString> list;
    QRegExp split("(( *(\\+|\\-)? *((\\d+\\.\\d+)|(\\d+)|(pi)|(e)))|\\+|\\-|\\^|\\%|\\/|\\*|\\(|\\)|(abs)|(arcsin)|(arccos)|(arctan)|(sin)|(cos)|(tan)|(sqrt)|(log *\\d+)|(log)|(ln)|(exp)|(ctg)|(arcctg)|(lg))");
//    if(!split.isValid())
//        qFatal("split is invalid!");
    int pos = 0;
    while ( (pos = split.indexIn(str, pos))!= -1){					//Creating an array of glyphs
        list << split.cap(1);
        pos+=split.matchedLength(); //Regulart expression
    }
    return list;
}


//------------------------------------------------------------------------------------------------
//------Calculating function----------------------------------------------------------------------
//----------\/\/\/\/----------------------------------------------------------------------

QString Widget::calculate(QString first, QString action, QString second){
        QChar firstGlyph = first[0] == '-' ? '-' : '+';
        QChar secondGlyph = second[0] == '-' ? '-' : '+';
        first.replace(QRegExp("(^(\\+|\\-)? *(e)$)"), (firstGlyph + e));
        first.replace(QRegExp("(^(\\+|\\-)? *(pi)$)"), (firstGlyph  + pi));
        second.replace(QRegExp("(^(\\+|\\-)? *(e)$)"), (secondGlyph + e));
        second.replace(QRegExp("(^(\\+|\\-)? *(pi)$)"), (secondGlyph + pi));
        double fir = first.toDouble();
        double sec = second.toDouble();
        if ( action == "-") return (action.setNum(fir-sec)).replace(QRegExp("e\\+"), "E");
        if ( action == "+") return (action.setNum(fir+sec)).replace(QRegExp("e\\+"), "E");
        if ( action == "*") return (action.setNum(fir*sec)).replace(QRegExp("e\\+"), "E");
        if ( action == "/") return (action.setNum(fir/sec)).replace(QRegExp("e\\+"), "E");
        if ( action == "%") return (action.setNum((int)fir%(int)sec)).replace(QRegExp("e\\+"), "E");
        if ( action == "^") return (action.setNum(qPow(fir, sec))).replace(QRegExp("e\\+"), "E");
        if ( action == "sin") return (action.setNum(qSin(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "cos") return (action.setNum(qCos(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "tan") return (action.setNum(qTan(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "arcsin") return (action.setNum(qAsin(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "arccos") return (action.setNum(qAcos(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "arctan") return (action.setNum(qAtan(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "log") return (action.setNum(log(sec)/log(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "lg") return (action.setNum(log(fir)/log(10))).replace(QRegExp("e\\+"), "E");
        if ( action == "ln") return (action.setNum(qLn(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "exp") return (action.setNum(qExp(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "sqrt") return (action.setNum(qSqrt(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "ctg") return (action.setNum(1.0/qTan(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "arcctg") return (action.setNum((pi.toDouble())/2.0 - qAtan(fir))).replace(QRegExp("e\\+"), "E");
        if ( action == "abs") return (action.setNum(qAbs(fir))).replace(QRegExp("e\\+"), "E");
        return "";
//        qFatal("Redundant operator?");
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
    if ( (*(str.end()-1) == ')')  && (str.length() > 1) ){
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
    while ( (pos = pattern.indexIn(expression, pos))!= -1){
        QString value{"0"};
        QString action{"+"};
        QString token{""};
        int tokenCount{0};
        QString buf1 = pattern.cap(1);
        auto expressionList = split(buf1);
        QRegularExpression digit("(\\d+|((e|pi){1}))");
//        if(!digit.isValid())
//            qFatal("Digit is invalid");
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
                    value = calculate(value, action, listElement);
                    tokenCount=0;
                }
        }
        expression.replace(pos, buf1.length(), value);
        pos=0;
    }
    if(!expression.isEmpty() && /*QRegExp("^(\\+|\\-)").exactMatch(expression)*/ expression[0].isDigit())
//        expression.prepend("+");
         expression = expression.toDouble() >= 0 ? expression.prepend("+") : expression ;
    return expression;
}
//------------------------------------------------------------------------------------------------
//----------Calculating button--------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

void Widget::on_pushButton_eq_clicked()
{
    QString str{ui->lineEdit->text()};

//------------validity Checking block------------------------------------------------
    {
        QRegExp validity;
        QString validatedString;
        if(str.isEmpty())return;
        int pos{0};
        str.replace(validity, validatedString);
        validatedString = str;
        validity.setPattern("(((\\^|\\%|\\/|\\*|\\+|\\-|\\(|\\)|\\ )0\\d+))|(^\\.)|\\.(\\(|\\))|(\\(|\\))\\.|\\(\\)|^(0\\d)|(\\((\\^|\\%|\\/|\\*))|((\\^|\\%|\\/|\\*|\\+|\\=)\\))|(\\) *\\d|(\\^|\\%|\\/|\\*|\\+|\\-|\\.){2,}|(\\) *\\w)|(\\d+\\.\\d+(\\.(\\d+)?){1,}))|(( +\\. *)|( *\\. +))|(\\d+\\.\\d+|\\d+) +(\\d+\\.\\d+|\\d+)|\\|");
//        if(!validity.isValid())
//            qFatal("error in first validity regexp!");
        if (validity.indexIn(str, 0)!=-1){
            ui->conversionLabel->setText("Your equation is invalid!");
            return;
        }
        validity.setPattern("(((abs)|(exp)|(lg)|(arcsin)|(arccos)|(arctan)|(sin)|(cos)|(tan)|(ln)|(log *(\\d+\\.\\d+|\\d+))|(log)|(sqrt)|(ctg)|(arcctg)) *\\()");//(log *(\\d+|\\(.+\\)) *\\(.+\\))
//        if(!validity.isValid())
//            qFatal("error in validity regexp!") ;
        pos = 0;
        while ((pos = validity.indexIn(validatedString, pos)) != -1){
            QString buf{validity.cap(1)};
            if(QRegExp("log *\\(").exactMatch(buf)){
                validatedString.insert( (validatedString.indexOf(QRegExp("\\) *\\("), pos)+1), "+");
            }
            validatedString.replace(pos, buf.length(), "(");
            pos = 0;
        }
        validatedString.replace(QRegExp("(e)|(pi)"), "(1)");
        validity.setPattern("([^\\d\\+\\-\\/\\*\\%\\.\\^\\(\\)\\| ]|(\\d *\\())|\\) *\\(");
        if (validity.indexIn(validatedString, 0)!=-1){
            ui->conversionLabel->setText("Your equation is invalid!");
            return;
        }
        int lbracket{0}, rbracket{0};
        for(auto t:str){
            if(t=='(')lbracket++;
            if(t==')')rbracket++;
        }
        if(lbracket!=rbracket){
            ui->conversionLabel->setText("Missed a bracket?");
            return;
        }
    }
//------------------------------------------------------------------------------------------------
//------Creating a list of previous states--------------------------------------------------------
//-------------\/\/\/\/---------------------------------------------------------------------------


    if(ui->listWidget->count() > 20){
        ui->listWidget->removeItemWidget(ui->listWidget->takeItem(0));
    }
    auto fullExpressionList = split(str);

    fullExpressionList.append(")");
    fullExpressionList.prepend("(");
    bool notEnd{true};
    while(notEnd){
        if(fullExpressionList.first()!="(")break;
        QLinkedList<QString>::iterator start{0};
        QString bracketBoof;
        notEnd=false;
        for(QLinkedList<QString>::iterator  t = fullExpressionList.begin();t!=fullExpressionList.end();t++){
            notEnd=true;
            if(*t == "("){
                start=t;
                bracketBoof="";
                continue;
            }
            if(*t==")"){
                for(;(start)!=t;(t=fullExpressionList.erase(t))--);
                QRegExp square("( *(\\d+\\.\\d+|\\d+|(pi)|(e)) *(\\^) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+|(pi)|(e)))");
                QRegExp highOperator("( *(\\+|\\-)? *(\\d+\\.\\d+|\\d+|(pi)|(e)) *(\\*|\\/|\\%) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+|(pi)|(e)))");
                QRegExp nums("( *(\\+|\\-)? *(\\d+\\.\\d+|\\d+|(pi)|(e)) *(\\+|\\-) *(\\+|\\-)? *(\\d+\\.\\d+|\\d+|(pi)|(e)))");
//                if( (!square.isValid()) || (!highOperator.isValid()) || (!nums.isValid()))
//                    qFatal("something is invalid");



                *t = evaluation(evaluation(evaluation(bracketBoof, square), highOperator),nums);
                QRegExp logWithNum ("(log *(\\+|\\-)?\\d+)");
                if ((t != fullExpressionList.begin()) &&
                       logWithNum.exactMatch(*(t-1)) ){
                    (t-1)->remove(QRegExp("(log *)"));
                    *(t-1) = calculate(*(t-1), "log", *t);
                    fullExpressionList.erase(t);
                } else if((t != fullExpressionList.begin()) &&
                          QRegExp("(log *)").exactMatch(*(t-1))){
                    (t-1)->append(*t);
                    fullExpressionList.erase(t);
                    break;
                }

                highOperator.setPattern("((abs)|(exp)|(lg)|(arcsin)|(arccos)|(arctan)|(sin)|(cos)|(tan)|(ln)|log|(sqrt)|(ctg)|(arcctg))");
//                if(!highOperator.isValid())
//                    qFatal("second highOperation is invalid");
                if((t != fullExpressionList.begin()) && highOperator.exactMatch(*(t-1))){ //checking whether it's a function  ((*(t-1))[0].isLetter())
                    *(t-1) = calculate(*t, *(t-1));  //writing in previous position where was a function's name
                    fullExpressionList.erase(t);
                }
                break;
            }
            if((*(t))[0].isLetter() && !(QRegExp("^(\\+|\\-)? *(e|pi){1} *$").exactMatch(*t)) )
                continue;
            bracketBoof+=*t;
        }
    }

//------------------------------------------------------------------------------------------------
//-------Final result-----------------------------------------------------------------------------
//--------\/\/\/\/--------------------------------------------------------------------------------
    fullExpressionList.first().remove("+");
    fullExpressionList.first().replace(QRegExp("E"), "*10^");
    auto selectedList = ui->listWidget->selectedItems();
    if(selectedList.count() > 0){
        selectedList.first()->setText(str + "=" + fullExpressionList.first());
        ui->listWidget->clearSelection();
    } else
        ui->listWidget->addItem(str + "=" + fullExpressionList.first());
    ui->lineEdit->setText(fullExpressionList.first());
    ui->lineEdit->setFocus();
}

//------------------------------------------------------------------------------------------------
//------Returning of previous state---------------------------------------------------------------
//---------\/\/\/\/-------------------------------------------------------------------------------

void Widget::on_pushButton_revert_clicked()
{
    if(ui->lineEdit->text().isEmpty())return;
    int cursorPosition = ui->lineEdit->cursorPosition();
    if( ((cursorPosition-1) >= 0)){
        ui->lineEdit->setText(ui->lineEdit->text().remove((cursorPosition-1), 1));
        ui->lineEdit->setCursorPosition(cursorPosition-1);
    }
    ui->lineEdit->setFocus();
}



void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit->text();
    if(str.isEmpty()){
    ui->conversionLabel->setText(" " + ui->conversionFromList->currentText() +
                                 " = " + " " + ui->conversionToList->currentText());
                                 return;
    }
    QRegExp isFirstDigit("^((\\+)|(\\-))?((\\d+\\.\\d+)|(\\d+))$");
    if(!isFirstDigit.exactMatch(str) || str.length() > 10)
        return;
    double conversionValues[]{1.0, 0.0175, 1.111};
    QString to, strFrom;
    double from = (str.toDouble() / (conversionValues[ui->conversionFromList->currentIndex()]));
    to.setNum(from * conversionValues[ui->conversionToList->currentIndex()]);
    ui->conversionLabel->setText(strFrom.setNum(str.toDouble())+ " " + ui->conversionFromList->currentText() +
                                 " = " + to + " " + ui->conversionToList->currentText());
}


bool Widget::eventFilter(QObject *watched, QEvent *event){
    if( (event->type() == QEvent::KeyPress) ){
        QKeyEvent* keyEvent= (QKeyEvent *)event;
        QString str = ui->lineEdit->text();
        int cursorPosition = ui->lineEdit->cursorPosition();
        QRegularExpression doubleOperators("(\\^|\\%|\\/|\\*|\\+|\\-|\\.)");
//        if(!doubleOperators.isValid()) qFatal("Error in doubleOperators regexp!");
        if (
                (QRegularExpressionMatch(doubleOperators.match((QString)keyEvent->key())).hasMatch()) &&
                (QRegularExpressionMatch(doubleOperators.match((QString)str[cursorPosition]))).hasMatch()
             ){
            ui->lineEdit->setCursorPosition(cursorPosition+1);
            return true;
        }

        if (
           (QChar)keyEvent->key() == (')') &&
           ((QChar)keyEvent->key() == str[cursorPosition])
            ){
            ui->lineEdit->setCursorPosition(cursorPosition+1);
            return true;
        }
        if ( (QChar)keyEvent->key() == '(' ){
            if( str.length() > (cursorPosition) &&
                ((str[cursorPosition]).isDigit()) )
            return QObject::eventFilter(watched, event);
            ui->lineEdit->insert("()");
            ui->lineEdit->setCursorPosition(cursorPosition+1);
            return true;
        }

        doubleOperators.setPattern("(\\^|\\%|\\/|\\*|\\+|\\-|\\.)");
        if ( ((cursorPosition-1) >= 0) &&
                (QRegularExpressionMatch(doubleOperators.match((QString)keyEvent->key())).hasMatch()) &&
             (QRegularExpressionMatch(doubleOperators.match((QString)str[cursorPosition-1]))).hasMatch())
            return true;

        if ( ((cursorPosition-1) >= 0) &&
                (keyEvent->key() == Qt::Key_Backspace) &&
                 ((str[cursorPosition] == ')') && (str[cursorPosition-1] == '(')) ){
            str.remove(cursorPosition-1, 2);
            ui->lineEdit->setText(str);
            ui->lineEdit->setCursorPosition(cursorPosition-1);
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}



void Widget::on_listWidget_itemClicked(QListWidgetItem *item)
{
   ui->lineEdit->setText(item->text().remove(QRegExp("=.+")));
   ui->lineEdit->setFocus();
}

void Widget::on_saveButton_3_clicked()
{
    ui->listWidget->clearSelection();
    ui->lineEdit->setFocus();
}

//remove item button
void Widget::on_saveButton_2_clicked()
{
    ui->lineEdit->setFocus();
    if(!ui->listWidget->currentItem())
        return;
    delete ui->listWidget->currentItem();
    ui->listWidget->clearSelection();
}

void Widget::on_delAllButton_clicked()
{
    ui->listWidget->clear();
    ui->lineEdit->setFocus();
}

void Widget::on_saveButton_clicked()
{
    ui->lineEdit->setFocus();
    if(ui->lineEdit->text().isEmpty())
        return;
    ui->memoryList->addItem(ui->lineEdit->text());
}

void Widget::on_delButton_clicked()
{
    ui->lineEdit->setFocus();
    if(ui->memoryList->currentText().isEmpty())
        return;
    ui->memoryList->removeItem(ui->memoryList->currentIndex());
}

void Widget::on_pasteButton_clicked()
{
    ui->lineEdit->setFocus();
    QString str{ui->memoryList->currentText()};
    if(str.isEmpty())
        return;
    int cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setText(ui->lineEdit->text().insert(cursorPosition,
                                                      str));
    ui->lineEdit->setCursorPosition(cursorPosition+=str.size());
}

void Widget::onConversionListChange(){
    on_lineEdit_textChanged(ui->lineEdit->text());
}
