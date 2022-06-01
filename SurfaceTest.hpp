#ifndef SURFACETEST_HPP
#define SURFACETEST_HPP

#include "Surface.hpp"

#define NUM_THREADS 6

class SurfaceTest : public Surface<640, 480, CP_FORMAT::RGB_24BIT, NUM_THREADS>
{
	public:
		SurfaceTest();
		~SurfaceTest();

		void loadMesh (const std::string& filePath);

		void draw(SoftwareGraphics<640, 480, CP_FORMAT::RGB_24BIT, NUM_THREADS>* graphics) override;

	private:
		Mesh m_Mesh;
};

#endif // SURFACETEST_HPP
