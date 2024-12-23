#include "Framework.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(wstring path)
{
	assert(PathFileExists(path.c_str()));

	file = CreateFile
	(
		path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
}

BinaryReader::BinaryReader(string path)
{
	assert(PathFileExistsA(path.c_str()));

	file = CreateFileA
	(
		path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);
}

BinaryReader::~BinaryReader()
{
	CloseHandle(file);
}

int BinaryReader::ReadInt()
{
	int data;

	ReadFile(file, &data, sizeof(int), &size, nullptr);

	return data;
}

UINT BinaryReader::ReadUINT()
{
	UINT data;

	ReadFile(file, &data, sizeof(UINT), &size, nullptr);

	return data;
}

float BinaryReader::ReadFloat()
{
	float data;

	assert(ReadFile(file, &data, sizeof(float), &size, nullptr));

	return data;
}

string BinaryReader::ReadString()
{
	UINT dataSize = ReadUINT();

	char* data = new char[dataSize + 1];

	ReadFile(file, data, sizeof(char) * dataSize, &size, nullptr);

	data[dataSize] = '\0';

	return data;
}

wstring BinaryReader::ReadWString()
{
	UINT dataSize = ReadUINT();

	wchar_t* data = new wchar_t[dataSize + 1];

	ReadFile(file, data, sizeof(wchar_t) * dataSize, &size, nullptr);

	data[dataSize] = '\0';

	return data;
}

Vector3 BinaryReader::ReadVector3()
{
	Vector3 data;

	data.x = ReadFloat();
	data.y = ReadFloat();
	data.z = ReadFloat();

	return data;
}

XMFLOAT4 BinaryReader::ReadXMFLOAT4()
{
	XMFLOAT4 data;

	data.x = ReadFloat();
	data.y = ReadFloat();
	data.z = ReadFloat();
	data.w = ReadFloat();

	return data;
}

XMFLOAT4X4 BinaryReader::ReadFLOAT4X4()
{
	XMFLOAT4X4 data;

	ReadFile(file, &data, sizeof(XMFLOAT4X4), &size, nullptr);

	return data;
}

XMMATRIX BinaryReader::ReadXMMATRIX()
{
	XMMATRIX data;

	ReadFile(file, &data, sizeof(XMMATRIX), &size, nullptr);

	return data;
}

void BinaryReader::ReadData(OUT void** data, UINT dataSize)
{
	ReadFile(file, *data, dataSize, &size, nullptr);
}

bool BinaryReader::Succeeded()
{
	return file != INVALID_HANDLE_VALUE;
}
