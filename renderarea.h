#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QImage>
#include "image_renderer.h"

class RenderArea : public QWidget {

	Q_OBJECT
	public:
	explicit RenderArea( QWidget* parent = 0 );

	bool paintAlways = false;

	int exportImage( int w, int h, QString path );

	signals:

	public slots:

	protected:

		QImage imgBuf;

		void paintEvent( QPaintEvent* );
		void resizeEvent( QResizeEvent* );
		void bufRealloc();
		void getRenderParams( mfx::RenderInfo &ri );
};

#endif // RENDERAREA_H
