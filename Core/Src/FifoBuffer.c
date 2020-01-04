#include "FifoBuffer.h"


void Fifo_initialize( FifoBufferObj* _fifo, char* _data, int _size )
{
    _fifo->size = _size;
    _fifo->elements = 0;
    _fifo->writer = 0;
    _fifo->reader = 0;
    _fifo->data = _data;
}

unsigned int Fifo_getNumberOfElements( FifoBufferObj* _fifo )
{
	return _fifo->elements;
}

int Fifo_push( FifoBufferObj* _fifo, char _c )
{
    if( _fifo->elements < _fifo->size )
    {
        _fifo->data[_fifo->writer] = _c;
        _fifo->writer++;
        if( _fifo->writer == _fifo->size )
            _fifo->writer = 0;
        _fifo->elements++;
        return 1;
    }
    return 0;
}

int Fifo_push_string( FifoBufferObj* _fifo, const char* _string )
{
	unsigned int ctr = 0;
	while( _string[ctr] != 0 )
	{
		if( Fifo_push( _fifo, _string[ctr] ) == 0 )
			return 0;
		ctr++;
	}
    return 1;
}

int Fifo_pop( FifoBufferObj* _fifo, char* _c )
{
    if( _fifo->elements > 0 )
    {
        *_c = _fifo->data[_fifo->reader];
        _fifo->reader++;
        if( _fifo->reader == _fifo->size )
            _fifo->reader = 0;
        _fifo->elements--;
        return 1;
    }
    return 0;
}
