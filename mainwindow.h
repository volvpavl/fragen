#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "renderarea.h"
#include "save_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
	explicit MainWindow( QWidget* parent = 0 );
	~MainWindow();

	QString makeFileName( int w, int h );

	public slots:
	void aboutBox();
	protected:
	bool eventFilter( QObject*, QEvent* );
	void updateLineEdit( QObject* dial );

	RenderArea *rArea;
	SaveDialog *sd;

	protected slots:
	void triggerAutoUpdate(int);
	void updateRenderer();
	void saveDialog();

	private:
	Ui::MainWindow* ui;
};

#endif    // MAINWINDOW_H
