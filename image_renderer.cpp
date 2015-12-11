
#include "image_renderer.h"
#include <cstdint>

#define mod(x,y) ( x*x + y*y )

void mfx::ImageRenderer::renderJulia( mfx::RenderInfo& ri ) {

	//unsigned int *buf = (unsigned int*)ri.buf;

	double &c_x = ri.const_x,
				 &c_y = ri.const_y,
	       dens_y = ri.scale_y / ri.h,
	       dens_x = ri.auto_scale ? dens_y : ri.scale_x / ri.w;

	for( int i = 0; i < ri.h; i++ )
		for( int j = 0; j < ri.w; j++ ) {

			double x = ( 2 * j - ri.w ) * dens_x,
						 y = ( 2 * i - ri.h ) * dens_y,
			       tmp;

			int k = -1;

			while( ++k < ri.max_depth && mod( x, y ) < ri.mod_threshold ) {
				tmp = x;
				x   = x * x - y * y + c_x;
				y   = 2.0 * tmp * y + c_y;
			}

			int col = (int)( (double)k * 255.0 / ri.max_depth );

			((int*)ri.buf)[i * ri.w + j] = col << 16 | col << 8 | col;
		}
}
