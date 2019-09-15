#include "stopwach.h"
#include "ui_stopwach.h"

stopWach::stopWach(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::stopWach)
{
  ui->setupUi(this);

  vLayout=new QVBoxLayout(this);
  hLayout=new QHBoxLayout();
  timer=new QTimer;
  time=new QTime();
  start=new QPushButton("START",this);
  stop=new QPushButton("",this);
  lcd=new QLCDNumber(this);

  vLayout->addWidget(lcd);
  vLayout->addLayout(hLayout);
  hLayout->addWidget(start);

  setView();
  setDefalutColors();

  working=false;
  time->setHMS(0,0,0,0);
  timer->setInterval(1);

  connect(start,SIGNAL(clicked()),this,SLOT(startCLickedSlot()));
  connect(stop,SIGNAL(clicked()),this,SLOT(stopCLickedSlot()));
  connect(timer,SIGNAL(timeout()),this,SLOT(startCLickedSlot()));
}

void  stopWach::setView(){
  stop->setHidden(true);
  setFixedSize(280,200);
  start->setFixedSize(QSize(125,50));
  stop->setFixedSize(QSize(125,50));
  lcd->setDigitCount(11);
  lcd->display(QString("00:00:00:00"));
  lcd->setFixedSize(240,50);
}
void stopWach::setDefalutColors(){
  start->setStyleSheet("color:rgb(0,255,0); border: 5px solid rgb(0,255,0); border-radius: 25px;font-size: 23px;font-weight: bold;");
  stop->setStyleSheet("color:rgb(255,0,0); border: 5px solid rgb(255,0,0); border-radius: 25px;font-size: 23px;font-weight: bold;");
  lcd->setStyleSheet("color: rgb(0,255,0);");
}
void stopWach::showTimerOnDisplay(const QTime* time){
 lcd->display(tr("%1:%2:%3:%4")
               .arg(time->hour()<10?tr("0%1").arg(time->hour()):tr("%1").arg(time->hour()))
               .arg(time->minute()<10?tr("0%1").arg(time->minute()):tr("%1").arg(time->minute()))
               .arg(time->second()<10?tr("0%1").arg(time->second()):tr("%1").arg(time->second()))
               .arg(time->msec()<10?tr("0%1").arg(time->msec()):time->msec()<100?tr("%1").arg(time->msec()):tr("%1").arg(time->msec()/10))
               );
}
void stopWach::startCLickedSlot(){
  addRemoveStopButton(true);

  if(!working){
    working=true;
    setTextStart(true);
  }
  timer->start();
  *time=time->addMSecs(1);
  showTimerOnDisplay(time);
  start->setDisabled(true);

}
void stopWach::stopCLickedSlot(){
  if(!working){
      addRemoveStopButton(false);
      setTextStart(true);
    }
 else{
    working=false;
    start->setDisabled(false);
    setTextStop(false);
    setTextStart(false);
  }
  timer->stop();
}

void stopWach::addRemoveStopButton(const bool flag){
  if(flag){
    hLayout->addWidget(stop);
    stop->setHidden(false);
    setTextStop(true);
    }
  else {
      hLayout->removeWidget(stop);
      stop->setHidden(true);
      time->setHMS(0,0,0,0);
      showTimerOnDisplay(time);
    }
}
void stopWach::setTextStart(const bool flag){
  flag?start->setText("START"):start->setText("RESUME");
}
void stopWach::setTextStop(const bool flag){
  flag?stop->setText("STOP"):stop->setText("RESET");
}
stopWach::~stopWach()
{
  delete hLayout;
  delete vLayout;
  delete stop;
  delete start;
  delete lcd;
  delete time;
  delete timer;
  delete ui;
}
