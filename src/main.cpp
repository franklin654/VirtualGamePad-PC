#include "mainwindow.hpp"

#include <QApplication>
#include <QtGlobal>
#include <stdio.h>
#include <stdlib.h>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QByteArray localMsg = msg.toLocal8Bit();
	switch (type)
	{
	case QtDebugMsg:
		fprintf(stdout, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtInfoMsg:
		fprintf(stdout, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtWarningMsg:
		fprintf(stdout, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line,
				context.function);
		break;
	case QtCriticalMsg:
		fprintf(stdout, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line,
				context.function);
		break;
	case QtFatalMsg:
		fprintf(stdout, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		abort();
	}
}

int main(int argc, char *argv[])
{
	qInstallMessageHandler(myMessageOutput); // Install the handler
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
