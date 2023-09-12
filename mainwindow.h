#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRxSerialPort1();

    void on_OpenCloseButton_clicked();

    void on_ClearButton_clicked();

    void on_SendButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *QSerialPort1;
};
#endif // MAINWINDOW_H
