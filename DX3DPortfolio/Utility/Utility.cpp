#include "framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{
	UINT index = path.find_last_of('.');

	return path.substr(index + 1, path.length());
}

string Utility::ToString(wstring wstr)
{
	string tmp;

	tmp.assign(wstr.begin(), wstr.end());

	return tmp;
}

wstring Utility::ToWString(string str)
{
	wstring tmp;

	tmp.assign(str.begin(), str.end());

	return tmp;
}

vector<string> Utility::SplitString(string origin, string token)
{
	vector<string> result;

	size_t cutAt = 0;


	while (cutAt != origin.npos)
	{
		cutAt = origin.find_first_of(token);

		if (cutAt > 0)
			result.push_back(origin.substr(0, cutAt));
		
		origin = origin.substr(cutAt + 1);
	}

	return result;
}

string Utility::GetFileName(string path)
{
	size_t cutAt = path.find_last_of('/');

	return path.substr(cutAt + 1);
}

string Utility::GetFileNameWithoutExtension(string path)
{
	string name = GetFileName(path);

	size_t cutAt = name.find_last_of('.');

	return name.substr(0, cutAt);
}

void Utility::CreateFolder(string path)
{
	size_t cutAt = path.find_last_of('.');

	vector<string> folders = SplitString(path, "/");

	UINT size = folders.size();

	if (cutAt != path.npos)
		size -= 1;

	string tmp = "";

	for (int i = 0; i < size; i++)
	{
		tmp += folders[i] + "/";

		if (!PathFileExistsA(tmp.c_str()))
		{
			CreateDirectoryA(tmp.c_str(), 0);
		}
	}
}
