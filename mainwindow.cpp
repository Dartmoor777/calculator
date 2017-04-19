#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    calculator = new Widget(parent);
    ui->setupUi(this);
    value = 0;
    timerSpeed = 80;// should be 80
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    timer->start(timerSpeed);
}

void MainWindow::updateProgressBar(){
    if(value == 100){
//        installEventFilter(calculator);
        setCentralWidget(calculator);
        return;
    }
    value+=1;
    ui->progressBar->setValue(value);
    timer->start(timerSpeed);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(this, "Help", "<br>For checking out man documantation on this program,<br>use the following command: <b><i>man calculator</i></b>");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "<b>Calculator V1.0</b><br>This program was created by Alex Putin.<br>In case finding bugs, please report me on my email:<br>AlexPutin@email.com");
}
