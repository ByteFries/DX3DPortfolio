#include "framework.h"
#include "DXBuffer.h"

DXBuffer::~DXBuffer()
{
	_buffer->Release();
}