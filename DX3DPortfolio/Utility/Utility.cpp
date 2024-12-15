#include "Framework.h"
#include "Utility.h"

/*

wstring Utility::GetProjectDir()
{
    WCHAR path[128];
    GetCurrentDirectory(128, path);

    wstring dir = path;

    return dir + L"/";
}

wstring Utility::GetTextureDir()
{
    return GetProjectDir() + L"_Texture/";
}

wstring Utility::GetTextDataDir()
{
    return GetProjectDir() + L"_TextData/";
}



*/

bool Utility::StartWith(string str, string prefix)
{
    return str.find(prefix, 0) == 0;
}

bool Utility::StartWith(wstring wstr, string prefix)
{
    string str = ToString(wstr);
    return str.find(prefix, 0) == 0;
}

vector<string> Utility::Split(string str, string delimiter)
{
    vector<string> result;
    int index = 0;
    string token = "";

    while ((index = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, index);
        result.push_back(token);
        str.erase(0, index + delimiter.length());
    }

    result.push_back(str);

    return result;
}

string Utility::GetFileName(string path)
{
    size_t cutAt = path.find_last_of('/');

    return path.substr(cutAt + 1);
}

wstring Utility::ToWString(string str)
{
    wstring wstr;
    return wstr.assign(str.begin(), str.end());
}

string Utility::ToString(wstring wstr)
{
    string str;
    return str.assign(wstr.begin(), wstr.end());
}

wstring Utility::GetExtension(wstring path)
{
    UINT index = path.find_last_of('.');

    return path.substr(index + 1);
}

string Utility::GetExtension(string path)
{
    UINT index = path.rfind('.');

    if (index == -1)
        return string();

    return path.substr(index + 1);
}

void Utility::CreateFolder(string path)
{
    path = GetFolderNameWithoutExtension(path);

    vector<string> split = Split(path, "/");

    string tmp = "";

    for (size_t i = 0; i < split.size(); i++)
    {
        tmp += split[i];

        if (!PathFileExistsA(tmp.c_str()))
        {
            CreateDirectoryA(tmp.c_str(), 0);
        }
        tmp += "/";
    }

}

float Utility::Clamp(float value, float min, float max)
{
    return (value < min) ? min : (value > max ? max : value);
}

string Utility::GetFileNameWithoutExtension(string path)
{
    string name = GetFileName(path);

    size_t cutAt = name.find_last_of('.');

    return name.substr(0, cutAt);
}

string Utility::GetFolderNameWithoutExtension(string path)
{
    size_t cutAt = path.find_last_of('/');

    return path.substr(0, cutAt + 1);
}
