
#pragma once
#ifndef ADOCONNECT_H
#define ADOCONNECT_H
#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
	no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")

class ADOConnect
{
public:
	ADOConnect(void);
	~ADOConnect(void);
public:
	//方法
	bool OnitConnect();               //用于连接数据库
	_RecordsetPtr &GetRecordSet(_bstr_t bstrSQL);           //用于打开记录集
	BOOL ExecuteSQL(_bstr_t bstrSQL);                       //执行SQL语句，操作数据库
	void ExitConnect();                                     //断开数据库连接和关闭记录集
public:
	_ConnectionPtr m_pConnection; //连接对象
	_RecordsetPtr  m_pRecordset;  //记录集对象
	_bstr_t bstrSQL;
};
#endif