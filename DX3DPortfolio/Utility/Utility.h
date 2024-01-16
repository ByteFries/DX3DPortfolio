#pragma once
namespace Utility
{
	wstring GetExtension(wstring path);

	string ToString(wstring wstr);
	wstring ToWString(string str);

	vector<string> SplitString(string oirign, string token);

	string GetFileName(string path);

	string GetFileNameWithoutExtension(string path);

	void CreateFolder(string path);

	XMFLOAT4 XMVECTORToXMFLOAT4(DirectX::XMVECTOR vector);
};