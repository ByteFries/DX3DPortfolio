#pragma once

namespace Utility
{
	wstring ToWString(string str);
	string ToString(wstring wstr);

	bool StartWith(string str, string prefix);
	bool StartWith(wstring wstr, string prefix);

	vector<string> Split(string str, string delimiter);

	string GetFileName(string path);

	wstring GetExtension(wstring path);
	string GetExtension(string path);

	string GetFileNameWithoutExtension(string path);
	string GetFolderNameWithoutExtension(string path);

	void CreateFolder(string path);

	float Clamp(float value, float min, float max);

	//wstring GetProjectDir();
	//wstring GetTextureDir();
	//wstring GetTextDataDir();
}