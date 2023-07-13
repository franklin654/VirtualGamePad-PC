#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamepadinjector.hpp"
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

  public slots:
	void testGamePadInjection();

  private:
	Ui::MainWindow *ui;
	GamepadInjector injector;
};
#endif // MAINWINDOW_H
