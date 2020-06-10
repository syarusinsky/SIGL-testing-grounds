#include "SurfaceTest.hpp"

#include <math.h>

#include "Graphics.hpp"
#include "Sprite.hpp"


class Font;
class Sprite;

extern Font* my_font_ptr;
extern Sprite* test_sprite_ptr;

typedef struct square
{
	float topLeftX;
	float topLeftY;
	float topRightX;
	float topRightY;
	float bottomRightX;
	float bottomRightY;
	float bottomLeftX;
	float bottomLeftY;
} Square;

typedef struct triangle
{
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
} Triangle;

Square my_square = { 0.2f, 0.2f, 0.8f, 0.1f, 0.8f, 0.7f, 0.2f, 0.8f };
Triangle my_triangle = { 0.5f, 0.3f, 0.2f, 0.6f, 0.8f, 0.6f };
float incr = 0.01f;

SurfaceTest::SurfaceTest (unsigned int width, unsigned int height, const CP_FORMAT& format) :
	Surface (width, height, format)
{
	m_Graphics->setColor( 1.0f, 1.0f, 1.0f );
	m_Graphics->setFont( my_font_ptr );
}

SurfaceTest::~SurfaceTest()
{
}

void SurfaceTest::draw()
{
	m_Graphics->setColor( 0.0f, 0.0f, 0.0f );
	m_Graphics->fill();

	/*
	m_Graphics->setColor( 1.0f, 1.0f, 1.0f );

	static float x = 1.0f;
	static float xIncr = 0.1f;
	m_Graphics->drawLine( 1.5f, x, -0.5f, 0.5f );
	x += xIncr;

	if (x >= 3.0f)
	{
		xIncr = -0.1f;
	}
	else if (x <= -2.0f)
	{
		xIncr = 0.1f;
	}
	*/

	static float blue = 0.1f;
	m_Graphics->setColor( 0.73f, 0.56f, blue );

	static bool flip = false;
	if (!flip)
	{
		my_square.topLeftX     += incr;
		my_square.bottomLeftX  += incr;
		my_square.topRightX    -= incr;
		my_square.bottomRightX -= incr;
		blue                   += incr;

		if (my_square.topLeftX >= 0.8f)
		{
			my_square.topLeftX     = 0.8f;
			my_square.bottomLeftX  = 0.8f;
			my_square.topRightX    = 0.2f;
			my_square.bottomRightX = 0.2f;
			flip = !flip;
		}
	}
	else
	{
		my_square.topLeftX     -= incr;
		my_square.bottomLeftX  -= incr;
		my_square.topRightX    += incr;
		my_square.bottomRightX += incr;
		blue                   -= incr;

		if (my_square.topLeftX <= 0.2f)
		{
			my_square.topLeftX     = 0.2f;
			my_square.bottomLeftX  = 0.2f;
			my_square.topRightX    = 0.8f;
			my_square.bottomRightX = 0.8f;
			flip = !flip;
		}
	}

	m_Graphics->drawQuad(
			my_square.topLeftX,     my_square.topLeftY,
			my_square.topRightX,    my_square.topRightY,
			my_square.bottomRightX, my_square.bottomRightY,
			my_square.bottomLeftX,  my_square.bottomLeftY   );

	m_Graphics->setColor( 1.0f, 0.1f, blue );

	m_Graphics->drawTriangle( my_triangle.x1, my_triangle.y1, my_triangle.x2, my_triangle.y2, my_triangle.x3, my_triangle.y3 );

	m_Graphics->drawTriangle ( 0.1f, 0.4f, 0.0f, 0.2f, 0.0f, 0.6f );

	m_Graphics->setColor( 0.2f, 0.9f, blue );

	m_Graphics->drawBoxFilled( 0.7f, 0.2f, 0.9f, 0.5f );

	m_Graphics->setColor( 0.5f, 0.5f, 0.5f );

	static float lineXEnd = -2.0f;
	static float lineIncr = 0.1f;
	m_Graphics->drawLine( 0.5f, 1.0f, lineXEnd, -2.0f );
	lineXEnd += lineIncr;
	if (lineXEnd <= -2.0f)
	{
		lineIncr = 0.1f;
	}
	else if (lineXEnd >= 3.0f)
	{
		lineIncr = -0.1f;
	}

	m_Graphics->setColor( 0.1f, 0.8f, 0.5f );

	static float trianglePixelX = 0.0f;
	static float trianglePixelY = 0.0f;
	static float trianglePixelXIncr = 0.005f;
	static float trianglePixelYIncr = 0.002f;

	m_Graphics->drawTriangleFilled( trianglePixelX, trianglePixelY, 0.7f, 0.7f, 0.3f, 0.3f );

	trianglePixelX += trianglePixelXIncr;
	if (trianglePixelX >= 1.0f)
	{
		trianglePixelX = 1.0f;
		trianglePixelXIncr = -0.005f;
	}
	else if (trianglePixelX <= 0.0f)
	{
		trianglePixelX = 0.0f;
		trianglePixelXIncr = 0.005f;
	}

	trianglePixelY += trianglePixelYIncr;
	if (trianglePixelY >= 1.0f)
	{
		trianglePixelY = 1.0f;
		trianglePixelYIncr = -0.002f;
	}
	else if (trianglePixelY <= 0.0f)
	{
		trianglePixelY = 0.0f;
		trianglePixelYIncr = 0.002f;
	}

	m_Graphics->setColor( 1.0f, 0.7f, 0.7f );

	m_Graphics->drawQuadFilled( trianglePixelX, trianglePixelY, 0.6f, 0.4f, 0.6f, 0.6f, 0.5f, 0.6f );

	m_Graphics->setColor( 0.3f, 1.0f, 0.3f );

	static float boxPixelXStart = -0.05f;
	static float boxPixelYStart = -0.05f;
	static float boxPixelIncr = 0.01f;

	m_Graphics->drawBoxFilled( boxPixelXStart, boxPixelYStart, boxPixelXStart + 0.1f, boxPixelYStart + 0.1f );

	boxPixelXStart += boxPixelIncr;
	boxPixelYStart += boxPixelIncr;

	if (boxPixelXStart >= 2.0f)
	{
		boxPixelIncr = -0.01f;
	}
	else if (boxPixelXStart <= -1.0f)
	{
		boxPixelIncr = 0.01f;
	}

	static float originX = 0.5f;
	static float originY = 0.5f;
	static float originXIncr = -0.05f;
	static float originYIncr = -0.02f;
	m_Graphics->setColor( 1.0f, 1.0f, 1.0f );
	m_Graphics->drawCircleFilled( originX, originY, 0.2f );

	originX += originXIncr;
	originY += originYIncr;

	if (originX < -0.5f)
	{
		originX = -0.5f;
		originXIncr = 0.05f;
	}
	else if (originX > 1.5f)
	{
		originX = 1.5f;
		originXIncr = -0.05f;
	}

	if (originY < -0.5f)
	{
		originY = -0.5f;
		originYIncr = 0.02f;
	}
	else if (originY > 1.5f)
	{
		originY = 1.5f;
		originYIncr = -0.02f;
	}

	static float textScale = 10.0f;
	static float textScaleIncr = -0.1f;
	static float textX = 0.5f;
	static float textY = 0.5f;
	static float textXMov = -0.01f;
	static float textYMov = 0.005f;
	m_Graphics->setColor( 0.5f, 1.0f, 1.0f );
	m_Graphics->drawText( textX, textY, "siike", textScale );
	textScale += textScaleIncr;
	textX += textXMov;
	textY += textYMov;
	if ( textScale > 10.0f || textScale < 0.5f ) textScaleIncr = textScaleIncr * -1.0f;
	if ( textX > 1.2f || textX < -0.5f) textXMov = textXMov * -1.0f;
	if ( textY < -0.2f || textY > 1.0f ) textYMov = textYMov * -1.0f;

	static float spriteScale = 1.5f;
	static float spriteScaleIncr = -0.01f;
	static float spriteX = 0.2f;
	static float spriteY = 0.2f;
	static float spriteXMov = 0.005f;
	static float spriteYMov = -0.01f;
	static int   spriteRotDegrees = 0;
	static int   spriteRotIncr = 1;
	test_sprite_ptr->setRotationAngle( spriteRotDegrees );
	test_sprite_ptr->setScaleFactor( spriteScale );
	m_Graphics->drawSprite( spriteX, spriteY, *test_sprite_ptr );
	spriteScale += spriteScaleIncr;
	spriteX += spriteXMov;
	spriteY += spriteYMov;
	spriteRotDegrees += spriteRotIncr;
	if ( spriteScale > 1.5f || spriteScale < 0.2f ) spriteScaleIncr = spriteScaleIncr * -1.0f;
	if ( spriteX > 0.9f || spriteX < -0.1f ) spriteXMov = spriteXMov * -1.0f;
	if ( spriteY > 0.7f || spriteY < -0.2f ) spriteYMov = spriteYMov * -1.0f;
	if ( spriteRotDegrees > 1023 || spriteRotDegrees < -2000 ) spriteRotIncr * -1;

	/* old test code to draw to a sprite
	m_Graphics->setFrameBuffer( &m_TestSprite );
	m_Graphics->setColor( 1.0f, 1.0f, 1.0f );
	m_Graphics->fill();
	m_Graphics->setColor( 0.0f, 0.0f, 0.0f );
	m_Graphics->drawCircleFilled( 0.5f, 0.5f, 0.2f );

	m_Graphics->setFrameBuffer( m_FrameBuffer );
	m_Graphics->drawSprite( 0.5f, 0.5f, m_TestSprite );
	*/
}
