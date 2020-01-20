#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 1
#define MALLOC_ARRAY(TYPE, LENGTH) (TYPE*) malloc(sizeof(TYPE) * LENGTH)
#define MALLOC_PTR(TYPE) (TYPE*) malloc(sizeof(TYPE))

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

//IMPORTANT: we assume that the terminal handles the Escapes Sequences.
//Escape Sequences: \x1b[...
//------------
inline void ConsMoveCursor(ushort x, ushort y)
{
	printf("\x1b[%i;%iH", y, x);
}

inline void ConsSetForegroundColor(byte r, byte g, byte b)
{
	printf("\x1b[38;2;%i;%i;%im", r, g, b);
}

inline void ConsSetBackgroundColor(byte r, byte g, byte b)
{
	printf("\x1b[48;2;%i;%i;%im", r, g, b);
}

inline void ConsSetBufferSize(ushort x, ushort y)
{
	printf("\x1b[%i;%it", y, x);
}

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

void FreeBuffer(ConsBuffer* buf)
{
	if(buf)
	{
		for(ushort i = 0, m = buf->x * buf->y; i < m; i++)
			FreeCell(buf->matrix[i]);
		free(buf->matrix);
		free(buf);
		buf = nullptr;
	}
}

ConsCell* GetBufferCell(ushort x, ushort y, ConsBuffer* buf)
{
	if(buf) //if "buf" is not nullptr (if it exists into the memory)
		if((x < buf->x) && (y < buf->y)) //if the coordinates respects the buffer's size
			return buf->matrix[y * buf->x + x];
	//if it fails:
	return nullptr; 
}

void PrintBuffer(ushort x, ushort y, ConsBuffer* buf)
{
	if(buf)
	{
		for(ushort i = 0; i < buf->y; i++)
		{
			for(ushort j = 0; j < buf->x; j++)
			{
				int index = y * buf->x + x;
				ConsCell* cell = buf->matrix[index];
				putchar();
			}
		}
	}
}
