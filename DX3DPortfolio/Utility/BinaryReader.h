#pragma once
class BinaryReader
{
public:
	BinaryReader(wstring path);
	BinaryReader(string path);

	~BinaryReader();

	int        ReadInt();
	UINT       ReadUINT();
	float      ReadFloat();
	string     ReadString();
	wstring    ReadWString();
	Vector3    ReadVector3();
	XMFLOAT4    ReadXMFLOAT4();
	XMFLOAT4X4 ReadFloat4X4();
	XMMATRIX     ReadMatrix();

	void ReadData(OUT void** data, UINT dataSize);

	bool Succeeded();

private:
	HANDLE _file = nullptr;
	DWORD  _size = 0;
};

