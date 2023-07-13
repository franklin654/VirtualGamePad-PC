#include "mainwindow.hpp"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::testGamePadInjection);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::testGamePadInjection()
{
	injector.connectGamepad();
	injector.PressButton(GamepadButtons::A);
	injector.PressButton(GamepadButtons::B);
	injector.inject();
}
