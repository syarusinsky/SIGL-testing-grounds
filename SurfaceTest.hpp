#ifndef SURFACETEST_HPP
#define SURFACETEST_HPP

#include "Surface.hpp"
#include "Sprite.hpp"

class SurfaceTest : public Surface
{
	public:
		SurfaceTest (unsigned int width, unsigned int height, const CP_FORMAT& format);
		~SurfaceTest();

		void draw() override;

	private:
		Sprite m_TestSprite;
};

#endif // SURFACETEST_HPP
