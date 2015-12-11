#include "save_dialog.h"
#include "ui_save_dialog.h"

#include <QStringList>
#include <QDialogButtonBox>
#include <QCoreApplication>
#include <QDir>

SaveDialog::SaveDialog( QWidget* parent )
  : QDialog( parent )
  , ui( new Ui::SaveDialog ) {

	ui->setupUi( this );
	setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );

	fd = new QFileDialog( this, "Browse" );
	fd->setFileMode( QFileDialog::Directory );

	but_save = findChild<QDialogButtonBox*>( "buttonBox" )->button( QDialogButtonBox::Save );

	in_path  = findChild<QLineEdit*>( "in_path" );
	in_path->setText( QApplication::applicationDirPath() );

	cb_presets = findChild<QComboBox*>( "cb_presets" );

	QStringList presets, presets_w;

	presets   << "640x480"   << "800x600"   << "1024x768"  << "1280x960"  <<
	             "1600x1200" << "1920x1440" << "2560x1920" << "3200x2400";
	presets_w << "640x360"   << "768x432"   << "1024x600"  << "1280x720"  <<
	             "1600x900"  << "1920x1080" << "2560x1440" << "3200x1800";

	cb_presets->insertItems( 0, presets_w );
	cb_presets->insertSeparator( 0 );
	cb_presets->insertItems( 0, presets );
	cb_presets->setCurrentIndex( 5 );

	QObject::connect( cb_presets, SIGNAL(currentIndexChanged(int)), this, SLOT(selectPreset()));
	QObject::connect( in_path, SIGNAL(textChanged(QString)), this, SLOT(updateButton(QString)));
	QObject::connect( findChild<QPushButton*>( "but_browse" ), SIGNAL(clicked(bool)),
	                  this, SLOT(selectFolder()));

	selectPreset();
}

SaveDialog::~SaveDialog() {
	delete ui;
}

void SaveDialog::selectPreset() {
	QString p = findChild<QComboBox*>( "cb_presets" )->currentText();
	QStringList wh = p.split( 'x' );
	findChild<QLineEdit*>( "in_width" )->setText( wh[0] );
	findChild<QLineEdit*>( "in_height" )->setText( wh[1] );
}

void SaveDialog::updateButton( QString s ) {
	but_save->setEnabled( !s.isEmpty() && QDir::isAbsolutePath( s ));
}

void SaveDialog::selectFolder() {
	if( fd->exec() )
		in_path->setText( fd->selectedFiles()[0] );
}
