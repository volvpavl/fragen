
#include <QPainter>
#include <QRectF>
#include <QLineEdit>
#include <QCheckBox>
#include "mainwindow.h"
#include "renderarea.h"

RenderArea::RenderArea( QWidget* parent )
  : QWidget( parent ) {
}

int RenderArea::exportImage( int w, int h, QString path ) {

	int *buf = new int[w*h];

	mfx::RenderInfo ri( w, h, buf );

	getRenderParams( ri );

	mfx::ImageRenderer::renderJulia( ri );

	QImage *img = new QImage( (unsigned char*)buf, w, h, QImage::Format_RGB32 );

	bool result = img->save( path, "png" );

	delete   img;
	delete[] buf;

	return (int)!result;
}

void RenderArea::paintEvent( QPaintEvent* ) {

	bufRealloc();

	mfx::RenderInfo ri( width(), height(), imgBuf.bits() );

	getRenderParams( ri );

	mfx::ImageRenderer::renderJulia( ri );

	QPainter p( this );

	p.drawImage( 0, 0, imgBuf );
}

void RenderArea::resizeEvent( QResizeEvent* e ) {
	if( paintAlways )
		repaint();
}

void RenderArea::bufRealloc() {

	if( imgBuf.width() == width() && imgBuf.height() == height() )
		return;

	QImage img( width(), height(), QImage::Format_RGB32 );

	imgBuf = img;
}

#define loadParam(param) ri.param = w->findChild<QLineEdit*>( "in_" #param )->text().toDouble();

void RenderArea::getRenderParams( mfx::RenderInfo& ri ) {

	QMainWindow* w = qobject_cast<QMainWindow*>( this->window() );

	QLineEdit *e = w->findChild<QLineEdit*>( "cb_oversampling" );
	//ri.oversampling = e->text().toDouble();

	QCheckBox *cb = w->findChild<QCheckBox*>( "cb_auto_scale" );

	ri.auto_scale = cb->isChecked() ? 1 : 0;

	loadParam( const_x );
	loadParam( const_y );
	loadParam( scale_x );
	loadParam( scale_y );
	loadParam( max_depth );
	loadParam( mod_threshold );
}
