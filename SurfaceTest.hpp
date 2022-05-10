#ifndef SURFACETEST_HPP
#define SURFACETEST_HPP

#include "Surface.hpp"

class SurfaceTest : public Surface<640, 480, CP_FORMAT::RGB_24BIT>
{
	public:
		SurfaceTest();
		~SurfaceTest();

		void draw() override;

	private:
};

#endif // SURFACETEST_HPP
