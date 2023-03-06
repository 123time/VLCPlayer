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
//#include<QTimer>

using namespace std;



void MainWindow::VlcPlayer(char filename[1024]) {
  libvlc_instance_t* inst;
  libvlc_media_player_t* mp;
  libvlc_media_t* m;

  libvlc_time_t length;
  int width;
  int height;
  int wait_time = 5000;

  const char *version ;
  version = libvlc_get_version();
  printf("version %s\n",version);
  inst = libvlc_new(NULL,NULL);

  char *pos = strchr(filename, ':'); //查找第一个冒号的位置
  if (pos != NULL) { //如果找到了
    cout << "The string contains a colon at position " << pos - filename << endl;
    m = libvlc_media_new_location (inst,filename);
    mp = libvlc_media_player_new_from_media(m);
    libvlc_media_release(m);
    libvlc_media_player_play(mp);
  } else { //如果没有找到
    cout << "The string does not contain a colon" << endl;
    m = libvlc_media_new_path (inst,filename);
    mp = libvlc_media_player_new_from_media(m);
    libvlc_media_release(m);
    libvlc_media_player_play(mp);
  }

  //wait until the tracks are created
  _sleep(wait_time);
  length = libvlc_media_player_get_length(mp);
  width = libvlc_video_get_width(mp);
  height = libvlc_video_get_height(mp);
  printf("Stream Duration: %ds\n", length / 1000);
  printf("Resolution: %d x %d\n", width, height);
  //Let it play
  _sleep(length - wait_time);

  //QEventLoop loop;
  //QTimer::singleShot(length-wait_time, &loop, SLOT(quit()));
  //loop.exec(); // 在5000毫秒后退出事件循环

  // Stop playing
  libvlc_media_player_stop(mp);
  libvlc_media_player_release(mp);
  libvlc_release(inst);

}
