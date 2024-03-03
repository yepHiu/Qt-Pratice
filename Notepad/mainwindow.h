#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile> // 文件流管理
#include <QFileDialog> // 负责文件相关的操作
#include <QTextStream> // Qt文本流
#include <QMessageBox>  // 消息窗口
#include <QPrinter> // 打印流
#include <QPrintDialog> // 打印的相关操作

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    MainWindow(QWidget *parent = nullptr);// 说明这个窗口是没有父项的
    //析构函数
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile="";// 目前处于编辑中文件的文件名

};
#endif // MAINWINDOW_H
