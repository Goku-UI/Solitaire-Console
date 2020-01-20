#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 1
#define MALLOC_ARRAY(TYPE, LENGTH) (TYPE*) malloc(sizeof(TYPE) * LENGTH)
#define MALLOC_PTR(TYPE) (TYPE*) malloc(sizeof(TYPE))

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

//-------------
struct ConsRGB
{
	byte r, g, b;
};

ConsRGB* NewRGB(byte r, byte g, byte b)
{
	ConsRGB* rgb = MALLOC_PTR(ConsRGB);
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return rgb;
}

void FreeRGB(ConsRGB* rgb)
{
	if(rgb)
	{
		free(rgb);
		rgb = nullptr;
	}
}

//-------------
struct ConsCell
{
	ConsRGB* foreground;
	ConsRGB* background;
	char character;
};

ConsCell* NewCell(ConsRGB* fore, ConsRGB* back, char c)
{
	ConsCell* cell = MALLOC_PTR(ConsCell);
	cell->character = c;

	if(back)
		cell->background = back;
	else
		cell->background = NewRGB(0, 0, 0);

	if(fore)
		cell->foreground = fore;
	else
		cell->foreground = NewRGB(255, 255, 255);

	return cell;
}

void FreeCell(ConsCell* cell)
{
	if(cell)
	{
		FreeRGB(cell->background);
		FreeRGB(cell->foreground);
		free(cell);
		cell = nullptr;
	}
}

//-------------
struct ConsBuffer
{
	ushort x, y;
	ConsCell ** matrix;
};

ConsBuffer* NewBuffer(ushort size_x, ushort size_y)
{
	ConsBuffer* buf = MALLOC_PTR(ConsBuffer);
	buf->matrix = MALLOC_ARRAY(ConsCell*, size_x * size_y);

	for(ushort i = 0, m = size_x * size_y; i < m; i++)
		buf->matrix[i] = nullptr;
	buf->x = size_x;
	buf->y = size_y;

	return buf;
}



