#pragma once
#ifndef _CONVERTCHARSET_H_
#define _CONVERTCHARSET_H_

#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
using namespace std;
//ascii 转 Unicode   
wstring Acsi2WideByte(string& strascii)  
{  
	int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);  
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)  
	{  
		throw exception("Invalid UTF-8 sequence.");  
	}  
	if (widesize == 0)  
	{  
		throw exception("Error in conversion.");  
	}  
	vector<wchar_t> resultstring(widesize);  
	int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);  


	if (convresult != widesize)  
	{  
		throw exception("La falla!");  
	}  

	return wstring(&resultstring[0]);  
}  

//Unicode 转 Utf8   
string Unicode2Utf8(const wstring& widestring)  
{  
	int utf8size = WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);  
	if (utf8size == 0)  
	{  
		throw exception("Error in conversion.");  
	}  

    vector<char> resultstring(utf8size);  

	int convresult = WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);  

	if (convresult != utf8size)  
	{  
		throw exception("La falla!");  
	}  

	return string(&resultstring[0]);  
}  

//ascii 转 Utf8   
string ASCII2UTF_8(string& strAsciiCode)  
{  
	string strRet("");  
	//先把 ascii 转为 unicode   
	wstring wstr = Acsi2WideByte(strAsciiCode);  
	//最后把 unicode 转为 utf8   
	strRet = Unicode2Utf8(wstr);  
	return strRet;  
}  

bool CopyIcon(string filePath,string fileName)
{
	ofstream ofout;
	ifstream ifin;
	filePath += fileName;
	ofout.open(filePath,ios::out|ios::binary|ios::trunc);
	ifin.open(fileName,ios::in|ios::binary);
	if(ofout.fail())
	{
		ofout.close();
		return false;
	}
	char ch = ifin.get();
	while(!ifin.eof())
	{
		ofout.put(ch);
		ch = ifin.get();
	}
	ifin.close();
	ofout.close();
	return true;
}
#endif