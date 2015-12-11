#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fg_version.h"

#include <QLineEdit>
#include <QDial>
#include <QCheckBox>
#include <QMessageBox>
#include <QDir>
#include <QFile>

MainWindow::MainWindow( QWidget* parent )
	: QMainWindow( parent )
	, ui( new Ui::MainWindow ) {

	ui->setupUi( this );

	for( QDial* o : this->findChildren<QDial*>() ) {
		o->installEventFilter( this );
		updateLineEdit( o );
	}
	for( QLineEdit* o : this->findChildren<QLineEdit*>() )
		o->installEventFilter( this );

	rArea = this->findChild<RenderArea*>( "renderArea" );
	sd = new SaveDialog();

	QObject::connect( findChild<QCheckBox*>( "cb_autoPaint" ), SIGNAL(stateChanged(int)),
	                  this, SLOT(triggerAutoUpdate(int)));

	QObject::connect( findChild<QAbstractButton*>( "btn_update" ), SIGNAL(clicked(bool)),
	                  this, SLOT(updateRenderer()));

	QObject::connect( findChild<QAction*>( "act_save_as" ), SIGNAL(triggered(bool)),
	                  this, SLOT(saveDialog()));

	QObject::connect( findChild<QAction*>( "actionAbout" ), SIGNAL(triggered(bool)),
	                  this, SLOT(aboutBox()));

	triggerAutoUpdate( 1 );
}

MainWindow::~MainWindow() {
	delete ui;
}

QString MainWindow::makeFileName( int w, int h ) {

	QString s = "img_jls_" + findChild<QLineEdit*>( "in_const_x" )->text() +
	                   "_" + findChild<QLineEdit*>( "in_const_y" )->text() +
	                   "_" + QString::number( w ) + "x" + QString::number( h );

	return s.replace( '-', "_" );
}

bool MainWindow::eventFilter( QObject* o, QEvent* e ) {
	if( e->type() == QEvent::MouseButtonRelease || e->type() == QEvent::Wheel ) {
		if( o->objectName().startsWith( "k_" ) ) {
			updateLineEdit( o );
			if( rArea->paintAlways )
				rArea->repaint();
		}
	} else if( e->type() == QEvent::KeyRelease ) {
		if( o->objectName().startsWith( "in_" ) ) {
			QString name = "k_" + o->objectName().mid( 3 );
			QDial* d     = this->findChild<QDial*>( name );
			double val = qobject_cast<QLineEdit*>( o )->text().toDouble() * 1000.0;
			d->setValue( (int)val );
			if( rArea->paintAlways )
				rArea->repaint();
		}
	}
	return false;
}

void MainWindow::updateLineEdit( QObject* o ) {
	QString name = "in_" + o->objectName().mid( 2 );
	QLineEdit* l = this->findChild<QLineEdit*>( name );
	double val = qobject_cast<QDial*>( o )->value() / 1000.0;
	l->setText( QString::number( val, 'f', 3 ) );
}

void MainWindow::aboutBox() {
	QMessageBox::about( this,
	                    "About",
	                    "Fractal Image Generator\n"
	                    "ver. " FRAGEN_VERSION "\n\n"
	                    "https://github.com/volvpavl/fragen\n\n"
	                    "(c) 2015 Vladimir Volosunov" );
}

void MainWindow::saveDialog() {
	if( sd->exec() ) {
		int w = sd->findChild<QLineEdit*>( "in_width" )->text().toInt();
		int h = sd->findChild<QLineEdit*>( "in_height" )->text().toInt();
		QString path = sd->in_path->text() + "/" + makeFileName( w, h ) + ".png";
		QDir d( sd->in_path->text() );
		QFile f( path );

		if( !d.exists() )
			if( !d.mkpath( sd->in_path->text() ))
				QMessageBox::warning( this, "Warning", "Failed to create directory:\n" + sd->in_path->text() );

		if( f.exists() )
			if( QMessageBox::question( this, "Warning", "File `" + path + "` already exists.\nOverwrite?" )
			    == QMessageBox::No )
				return;

		this->setEnabled( false );

		if( rArea->exportImage( w, h, path ))
			QMessageBox::warning( this, "Warning", "Failed to save file:\n" + path );

		this->setEnabled( true );
	}
}

void MainWindow::triggerAutoUpdate( int state ) {
	rArea->paintAlways = (bool)state;
	if( state )
		rArea->repaint();
}

void MainWindow::updateRenderer() {
	rArea->repaint();
}
