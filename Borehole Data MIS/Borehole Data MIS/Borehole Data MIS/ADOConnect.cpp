#pragma once
#include "stdafx.h"
#include "ADOConnect.h"

ADOConnect::ADOConnect(void)
{
	bstrSQL = "";
}

ADOConnect::~ADOConnect(void)
{
}

bool ADOConnect::OnitConnect()
{
	bool errStatus = false;
	try
	{
		m_pConnection.CreateInstance(__uuidof(Connection));
		if(m_pConnection->Open(bstrSQL,"","",adModeUnknown) >= 0)
		{
				errStatus = true;
		}
	}
	catch(_com_error e)
	{
		e.Description();
		return errStatus;
	}
	return errStatus;
}

_RecordsetPtr& ADOConnect::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if(m_pConnection == NULL)
		{
			OnitConnect();
			m_pRecordset.CreateInstance(__uuidof(Recordset));
			m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockUnspecified,adCmdText);
		}
		else
		{
			m_pRecordset.CreateInstance(__uuidof(Recordset));
			m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockUnspecified,adCmdText);
		}
	}
	catch(_com_error e)
	{
		e.Description();
	}
	return m_pRecordset;
}

BOOL ADOConnect::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{
		if(NULL == m_pConnection)
		{
			OnitConnect();
		}
		m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		e.Description();
		return false;
	}
}

void ADOConnect::ExitConnect()
{
	if(m_pRecordset != NULL)
	{
		m_pRecordset->Close();
	}
	m_pConnection->Close();	 
}