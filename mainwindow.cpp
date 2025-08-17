#include "mainwindow.h"
#include "./ui_mainwindow.h"

double firstNum;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignRight);
    setWindowTitle("Qt Calculator");
    setWindowIcon(QIcon(":/Calculator Icon.png"));

    QFont font = ui->label->font();
    font.setPointSize(20);
    ui->label->setFont(font);

    connect(ui->pushButton_0,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pushButton_plusMinus,SIGNAL(released()), this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_perc,SIGNAL(released()), this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_add,SIGNAL(released()), this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_sub,SIGNAL(released()), this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_div,SIGNAL(released()), this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_mult,SIGNAL(released()), this,SLOT(binary_operation_pressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_sub->setCheckable(true);
    ui->pushButton_div->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);

    userIsTypingSecondNumber = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString buttonValue = button->text();
    QString currentLabel = ui->label->text();

    if (currentLabel == "Error") {
        ui->label->setText(buttonValue);
        userIsTypingSecondNumber = false;
        return;
    }

    if ((ui->pushButton_add->isChecked() || ui->pushButton_sub->isChecked() ||
         ui->pushButton_mult->isChecked() || ui->pushButton_div->isChecked()) && !userIsTypingSecondNumber)
    {
        ui->label->setText(buttonValue);
        userIsTypingSecondNumber = true;
    }

    else
    {
        if (currentLabel == "0")
            ui->label->setText(buttonValue);
        else
            ui->label->setText(currentLabel + buttonValue);
    }
}

void MainWindow::on_pushButton_dec_released()
{
    if(!ui->label->text().contains("."))
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if (button->text()=="+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber=labelNumber*-1;
        newLabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    if (button->text()=="%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber=labelNumber*0.01;
        newLabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }
}

void MainWindow::on_pushButton_c_released()
{
    ui->label->setText("0");
    firstNum = 0;
    userIsTypingSecondNumber = false;

    ui->pushButton_add->setChecked(false);
    ui->pushButton_sub->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_div->setChecked(false);
}


void MainWindow::on_pushButton_equal_released()
{
    double labelNumber, secondNum;
    QString newLabel;
    secondNum = ui->label->text().toDouble();

    if (ui->pushButton_add->isChecked())
    {
        labelNumber =firstNum+secondNum;
        newLabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    }

    else if (ui->pushButton_sub->isChecked())
    {
        labelNumber =firstNum-secondNum;
        newLabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_sub->setChecked(false);
    }

    else if (ui->pushButton_mult->isChecked())
    {
        labelNumber =firstNum*secondNum;
        newLabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_mult->setChecked(false);
    }

    else if (ui->pushButton_div->isChecked())
    {
        if (secondNum == 0) {
            ui->label->setText("Error");
        } else {
            labelNumber = firstNum / secondNum;
            newLabel = QString::number(labelNumber,'g',15);
            ui->label->setText(newLabel);
        }
        ui->pushButton_div->setChecked(false);
    }
}

void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    firstNum = ui->label->text().toDouble();
    button->setChecked(true);
    userIsTypingSecondNumber = false;
}
