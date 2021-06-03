#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDockWidget>




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
    void clickedbutton();
    void choosenoption(int index);
    void clickedbutton2();
    void lineinput(QString str);
private:
    int param;
    double x;
    double y;
    Ui::MainWindow *ui;

    QPushButton* button;
    QPushButton* button2;
    QLineEdit* line;
    QComboBox* box;
};
#endif // MAINWINDOW_H
