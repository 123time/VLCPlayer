#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <QCoreApplication>
#include <windows.h>
#include "vlc/vlc.h"
#include "QFileDialog"
#include "QDebug"
#include "QString"
#include "QFileInfo"
#include "QDateTime"
#include <QMessageBox>
#include <QDir>  //  获取当前路径 需要
#include <QDebug>      //  调试输出用到
#include <QMessageBox>    //  显示消息框用到
#include <QDesktopServices>      //  打开链接用到
#include <QUrl>  //  打开网页需要
#include<string.h>
#include<QInputDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//配置URL按钮
void MainWindow::on_pushButton_2_clicked() {
  bool bOk = false;
  char filename[1024] = {0};
  QString sName = QInputDialog::getText(this,
                                        "网络播放地址",
                                        "请输入URL",
                                        QLineEdit::Normal,
                                        "rtmp://120.79.182.222/live/yuan",
                                        &bOk
                                       );
  if (bOk && !sName.isEmpty()) {
    ui->pushButton_4->setText("网络地址");
    ui->lineEdit->setText(sName);

    int pos = sName.indexOf(":"); //查找第一个冒号的位置
    if (pos != -1) { //如果找到了
      strcpy(filename, sName.toStdString().c_str());
      cout << "The string contains a colon at position " << pos << endl;
      VlcPlayer(filename);
    } else { //如果没有找到
      cout << "The string does not contain a colon" << endl;
    }
  } else {
    cout<<"The string does not contain a colon" << endl;
  }

}


//配置本地文件按钮
void MainWindow::on_pushButton_3_clicked() {
  QString file_name =QFileDialog::getOpenFileName(this,"open file dialog","../myvlc/","(*.flv)");
  QFileInfo info(file_name);
  QString size = QString::number(info.size());
  ui->pushButton_4->setText("文件名称");
  ui->lineEdit->setText(file_name);
  ui->pushButton_5->setText("文件大小");
  ui->lineEdit_2->setText(size+" 字节");
  QString lastModified = info.lastModified().toString();
  ui->pushButton_6->setText("创建时间");
  ui->lineEdit_3->setText(lastModified);

  char str[1024] = {0};

  string newstr = "..";
  string s = file_name.toStdString();
  string sub = "myvlc";
  size_t pos = s.find(sub); //找到子字符串的位置
  if (pos != string::npos) { //如果找到了
    newstr = newstr + s.substr(pos + sub.length()) ;
    cout <<newstr<< endl; //输出子字符串之后的部分
    newstr.copy(str, newstr.length());
    printf("------------------%s\n",str);

    VlcPlayer(str);
  } else { //如果没找到
    cout << "No match" << endl;
  }


}


