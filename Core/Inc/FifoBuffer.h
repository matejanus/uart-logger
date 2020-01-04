#pragma once

typedef struct FifoBufferObj
{
    unsigned int size;
    unsigned int elements;
    unsigned int writer;
    unsigned int reader;
    char* data;
} FifoBufferObj;

void Fifo_initialize( FifoBufferObj* _fifo, char* _data, int _size );
unsigned int Fifo_getNumberOfElements( FifoBufferObj* _fifo );
int Fifo_push( FifoBufferObj* _fifo, char _c );
int Fifo_push_string( FifoBufferObj* _fifo, const char* _string );
int Fifo_pop( FifoBufferObj* _fifo, char* _c );
