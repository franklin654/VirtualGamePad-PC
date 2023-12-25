#pragma once

#include "preferences.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

  private slots:
	void launch_server();

  private:
	Ui::MainWindow *ui;
	Preferences *p = nullptr;
};
