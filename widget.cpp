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
    connect(mapp,SIGNAL(mapped(QString)), this, SLOT(but_add(QString)));
}

void Widget::but_add(QString str){
    ui->lineEdit->setText(ui->lineEdit->text()+str);
}

Widget::~Widget()
{
    delete ui;
}
