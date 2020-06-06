#ifndef SURFACETEST_HPP
#define SURFACETEST_HPP

#include "Surface.hpp"

class Sprite;

class SurfaceTest : public Surface
{
	public:
		SurfaceTest (unsigned int width, unsigned int height, const CP_FORMAT& format);
		~SurfaceTest();

		void draw() override;

	private:
};

#endif // SURFACETEST_HPP
