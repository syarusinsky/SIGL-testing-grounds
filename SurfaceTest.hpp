#ifndef SURFACETEST_HPP
#define SURFACETEST_HPP

#include "Surface.hpp"

#define NUM_CORES 32

class SurfaceTest : public Surface<640, 480, CP_FORMAT::RGB_24BIT, NUM_CORES>
{
	public:
		SurfaceTest();
		~SurfaceTest();

		void draw(SoftwareGraphics<640, 480, CP_FORMAT::RGB_24BIT, NUM_CORES>* graphics) override;

	private:
};

#endif // SURFACETEST_HPP
