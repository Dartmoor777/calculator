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
    ui->lineEdit->setText(ui->lineEdit->text()+str);
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
    QString str{ui->lineEdit->text()};
    str.chop(1);
    ui->lineEdit->setText(str);
}



//------------------------------------------------------------------------------------------------
//----------Calculating button--------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

void Widget::on_pushButton_eq_clicked()
{

//------------------------------------------------------------------------------------------------
//-----------Checking validity--------------------------------------------------------------------
//----------------\/\/\/\/------------------------------------------------------------------------
    if(ui->lineEdit->text().isEmpty())return;
    QString str{ui->lineEdit->text()};
    QRegExp validity("(((\\^|\\%|\\/|\\*|\\+|\\-|\\.){2,})|((\\^|\\%|\\/|\\*|\\+|\\-|\\(|\\)|\\ )0\\d+))|(^\\.)|\\.(\\(|\\))|(\\(|\\))\\.|\\(\\)|\\)\\(|^(0\\d)|(\\((\\^|\\%|\\/|\\*))|((\\^|\\%|\\/|\\*|\\+|\\=)\\))|(\\) *\\d)|(\\d *\\()");
//    QRegExp validity("(((\^|\%|\/|\*|\+|\-|\.){2,})|((\^|\%|\/|\*|\+|\-|\(|\)|\ )0\d+))|(^\.)|\.(\(|\))|(\(|\))\.|\(\)|\)\(|^(0\d)");
    QRegExp isInvalidChar("[^\\d\\+\\-\\/\\*\\%\\.\\^ \\(\\)]"); 							// Checking validity
    if (isInvalidChar.indexIn(str, 0)!=-1){
        QMessageBox::information(this, "", "There are invalid characters!");
        return;
    }
    if (validity.indexIn(str, 0)!=-1){
        QMessageBox::information(this, "", "Your equation is invalid!");
        return;
    }

//------------------------------------------------------------------------------------------------
//------Creating a list of previous states--------------------------------------------------------
//-------------\/\/\/\/---------------------------------------------------------------------------

    if(revertList.size()>10)revertList.removeFirst();
    revertList.append(str);
//------------------------------------------------------------------------------------------------
//---------Adding brackets------------------------------------------------------------------------
//-------------\/\/\/\/---------------------------------------------------------------------------

QRegExp regex(" *((((\\d+\\.\\d+))|(\\d+)|\\(((((\\d+\\.\\d+))|(\\d+)|) *(\\^|\\%|\\/|\\*|\\+|\\-) *((\\d+\\.\\d+)|(\\d+)))\\)) *(\\^|\\%|\\/|\\*) *((\\d+\\.\\d+)|(\\d+)|\\(((((\\d+\\.\\d+))|(\\d+)|) *(\\^|\\%|\\/|\\*|\\+|\\-) *((\\d+\\.\\d+)|(\\d+)))\\)))");
//QRegExp regex(" *((((\d+\.\d+))|(\d+)|\(((((\d+\.\d+))|(\d+)|) *(\^|\%|\/|\*|\+|\-) *((\d+\.\d+)|(\d+)))\)) *(\^|\%|\/|\*) *((\d+\.\d+)|(\d+)|\(((((\d+\.\d+))|(\d+)|) *(\^|\%|\/|\*|\+|\-) *((\d+\.\d+)|(\d+)))\)))");
    int pos{0};
    while ( (pos = regex.indexIn(str, pos))!= -1){			//Adding brackets
        QString buf1 = regex.cap(1);
        QString buf2 = buf1;
        str.replace(buf1, buf2.prepend("(")+")");
        pos+=regex.matchedLength();
        qDebug() << "Loop";
    }
    QStringList list;
    QRegExp split("((\\d+\\.\\d+)|\\d+|\\+|\\-|\\^|\\%|\\/|\\*|\\(|\\))");
    pos = 0;
    while ( (pos = split.indexIn(str, pos))!= -1){					//Creating an array of glyphs
        list << split.cap(1);
        pos+=split.matchedLength();
    }
    list.append(")");
    list.prepend("(");

//------------------------------------------------------------------------------------------------
//-----Parsing the string and calculating the result of first pare of brackets--------------------
//-----------\/\/\/\/-----------------------------------------------------------------------------

    bool notEnd{true};
   QRegularExpression digit("(\\d+)");
    while(notEnd){
        bool start = false;
        QString value, action;
        for(QList<QString>::iterator t = list.begin();t!=list.end();t++){           // Parsing the glyphs
            if(*t == "("){
                start=true;  //Showing that we've found first bracket
                value="0";  //Setting default value & action
                action="+";
                continue;
            }
            if(!start){
                notEnd=false;
                break;
            }
            if(*t=="/" || *t=="*" || *t=="-"|| *t=="+"|| *t=="^"|| *t=="%"){  			//if there no "()" it means it should be "+-/*..."
                action=*t;
                continue;
            }
            if(QRegularExpressionMatch(digit.match(*t, 0)).hasMatch() && start){    // looking for decimals
                value = calculate(value, action, *t);
                continue;
            }
            if(*t==")" && (!value.isEmpty())){			// erasing what were in brackets and generating one exact num
                for(;*t!="(";(t=list.erase(t))--);
                *t=value;
                break;
            }
        }
    }
//------------------------------------------------------------------------------------------------
//-------Final result-----------------------------------------------------------------------------
//--------\/\/\/\/--------------------------------------------------------------------------------
    ui->lineEdit->setText(list.first());
    ui->listWidget->addItem(str + "=" + list.first());
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
