#include "mainwindow.h"
#include "ui_mainwindow.h"

// 类的构造函数的具体事项
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);//将plainTextEdit作为中央窗口
}

// 析构函数的具体实现
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->plainTextEdit->setPlainText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(fileName);
    currentFile = fileName;

    // 尝试以只读模式打开文件
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Can not open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName); // 设置主窗体名称

    QTextStream in(&file); // 初始化文件流

    QString text = in.readAll();// 从文件中读取文本
    ui->plainTextEdit->setPlainText(text); // 将文本放入窗体中

    file.close();//关闭文件流
}



void MainWindow::on_actionSave_as_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Save as");

    QFile file(fileName);

    //尝试以只写模式打开文件
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Can not save file");
        return;
    }

    currentFile=fileName;
    setWindowTitle(fileName);

    QTextStream out(&file);// 文本流初始化
    QString text=ui->plainTextEdit->toPlainText();// 从窗体中获取文本
    out<<text;//输出为文件
    file.close();// 文件流关闭
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;// 声明一个打印机类
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer,this);// 完成对于打印机类的配置

    if(pDialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this,"Warning","Can not access printer");
        return;
    }

    ui->plainTextEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_actionSave_triggered()
{
    QFile file(currentFile);

    //尝试以只写模式打开文件
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Can not save file");
        return;
    }

    QTextStream out(&file);// 文本流初始化
    QString text=ui->plainTextEdit->toPlainText();// 从窗体中获取文本
    out<<text;//输出为文件
    file.close();// 文件流关闭
}

