#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSerialPort1= new QSerialPort(this);
    connect(QSerialPort1,&QSerialPort::readyRead,this,&MainWindow::onRxSerialPort1);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ClearButton_clicked()
{
    //LIMPIAMOS EL PLAIN TEXT EDIT
    ui->plainTextEdit->clear();
}





void MainWindow::onRxSerialPort1(){
    //SI HAY NUEVOS DATOS INGRESANDO LOS LEEMOS Y ESCRIBIMOS EN EL PLAIN TEXT EDIT
    char *buffer;
    int cont;
    QString str;
    int i;
    cont=QSerialPort1->bytesAvailable();
    if(cont<=0){
        return;//se retorna si no hay datos realmente
    }

    buffer = new char[cont];
    QSerialPort1->read(buffer,cont);

    for(i=0;i<cont;i++){
        str = str + QString(buffer[i]);
    }

    ui->plainTextEdit->appendPlainText(str);


    delete[] buffer;
}


void MainWindow::on_OpenCloseButton_clicked()
{
    //ABRIMOS O CERRAMOS EL PUERTO
    if(QSerialPort1->isOpen()){
        QSerialPort1->close();
        ui->OpenCloseButton->setText("OPEN");

    }else{

        QSerialPort1->setPortName(ui->lineEdit_2->text());
        QSerialPort1->setBaudRate(QSerialPort::Baud115200);
        if(QSerialPort1->open(QSerialPort::ReadWrite)){
            ui->OpenCloseButton->setText("CLOSE");
        }
    }
}



void MainWindow::on_SendButton_clicked()
{
    char bufTx[256];
    int i;
    if(QSerialPort1->isOpen() && ui->lineEdit->text()!=""){
        for(i=0;i<ui->lineEdit->text().length();i++){
            bufTx[i]=ui->lineEdit->text().toUtf8().data()[i];
        }
        QSerialPort1->write(bufTx,ui->lineEdit->text().length());
    }




}

