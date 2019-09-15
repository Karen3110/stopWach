#include "stopwach.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  stopWach w;
  w.show();

  return a.exec();
}
