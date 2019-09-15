#ifndef STOPWACH_H
#define STOPWACH_H

#include <QWidget>
#include <QLCDNumber>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QTime>
#include <QEvent>
#include <iostream>
namespace Ui {
  class stopWach;
}

class stopWach : public QWidget
{
  Q_OBJECT

public:
  explicit stopWach(QWidget *parent = nullptr);
  ~stopWach();
private slots:
  void startCLickedSlot();
  void stopCLickedSlot();
private:
  Ui::stopWach *ui;

  QVBoxLayout *vLayout;
  QHBoxLayout *hLayout;
  QLCDNumber *lcd;
  QPushButton *start;
  QPushButton *stop;
  QTimer * timer;
  QTime *time;
  bool working;

  void showTimerOnDisplay(const QTime*);//shows time on Display
  void setView();// configs front panel view
  void setDefalutColors(); //  configs front panel colors

  void addRemoveStopButton(const bool); //  if true add button on front panel
  void setTextStart(const bool); // true?start:resume
  void setTextStop(const bool); //  true? stop:reset
 };

#endif // STOPWACH_H
