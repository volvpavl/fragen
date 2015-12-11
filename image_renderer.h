#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

namespace mfx {

struct RenderInfo {

	int w, h;
	void* buf;

	double scale_x = 2.0, scale_y = 2.0,
				 const_x = -0.123, const_y = 0.723,
				 origin_x = 0.0, origin_y = 0.0,
				 mod_threshold = 4.0;

	int max_depth = 32, oversampling = 0, auto_scale = 0;

	RenderInfo( int width, int height, void* buffer )
		: w( width )
		, h( height )
		, buf( buffer ) {
	}
};

class ImageRenderer {

	public:
	static void renderJulia( RenderInfo& ri );
};
}

#endif    // IMAGERENDERER_H
