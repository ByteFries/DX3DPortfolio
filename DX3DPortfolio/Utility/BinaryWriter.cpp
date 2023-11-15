#include "framework.h"
#include "BinaryWriter.h"

BinaryWriter::BinaryWriter(string path)
{
	_file = CreateFileA(
		path.c_str(),
		GENERIC_WRITE,
		0, 0,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
}

BinaryWriter::BinaryWriter(wstring path)
{
	_file = CreateFile(
		path.c_str(),
		GENERIC_WRITE,
		0, 0,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
}

BinaryWriter::~BinaryWriter()
{
	CloseHandle(_file);
}

void BinaryWriter::WriteData(int data)
{
	WriteFile(_file, &data, sizeof(int), &_size, nullptr);
}

void BinaryWriter::WriteData(UINT data)
{
	WriteFile(_file, &data, sizeof(UINT), &_size, nullptr);
}

void BinaryWriter::WriteData(float data)
{
	WriteFile(_file, &data, sizeof(float), &_size, nullptr);
}

void BinaryWriter::WriteData(string data)
{
	WriteData((UINT)data.size());

	const char* str = data.c_str();

	WriteFile(_file, str, sizeof(char) * data.size(), &_size, nullptr);
}

void BinaryWriter::WriteData(wstring data)
{
	WriteData((UINT)data.size());

	const wchar_t* str = data.c_str();

	WriteFile(_file, str, sizeof(wchar_t) * data.size(), &_size, nullptr);
}

void BinaryWriter::WriteData(Vector3 data)
{
	WriteData(data.x);
	WriteData(data.y);
	WriteData(data.z);
}

void BinaryWriter::WriteData(XMFLOAT4 data)
{
	WriteData(data.x);
	WriteData(data.y);
	WriteData(data.z);
	WriteData(data.w);
}

void BinaryWriter::WriteData(void* data, UINT dataSize)
{
	WriteFile(_file, &data, dataSize, &_size, nullptr);
}

void BinaryWriter::WriteData(XMFLOAT4X4 data)
{
	WriteFile(_file, &data, sizeof(XMFLOAT4X4), &_size, nullptr);
}

void BinaryWriter::WriteData(XMMATRIX data)
{
	WriteFile(_file, &data, sizeof(XMMATRIX), &_size, nullptr);
}

void BinaryWriter::WriteData(size_t data)
{
	WriteData((UINT)data);
}