/********************************************************
Copyright 1996-2005, Pixel Software Corporation, 
All rights reserved.

Module name:	tab text data
Purpose:		deal with table frome txt
Author: xuequn
Compiler: Microsoft Visual C++ 2010
History: 2018-6-12


*********************************************************/
#pragma  once

#define __TTD_SPACE_BEG__	namespace TTD {
#define __TTD_SPACE_END__	}

#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>
__TTD_SPACE_BEG__
#define TTD_TITLE 5
//********************************************************
// 记录每个表的列信息（第几列、类型）
//**************************
// 字段类型
enum value_type
{
	e_type_int		= 0,
	e_type_float	= 1,
	e_type_string	= 2,
	e_type_vint		= 3,
	e_type_vfloat	= 4,
	e_type_vstring	= 5,
	e_type_max
};
// 行信息的描述
class column_info
{
public:
	int							i_column;			//计数当前是第几列，0开始
	value_type					e_value;				//值类型
	int							i_offset;			//类成员的偏移量
};
// 行信息的汇总
class columns_info
{
public:
	std::vector<column_info>		vColumns;
};

//********************************************************
// 每个表的基础模板类
template<class T>
class TTDBase
{
public:
	std::vector< T* >		m_lines;
	std::string				m_name;
	bool					parse_data(const char* szPath);
	T*						get_line(int iLineNum);
	void					set_line(int iLineNum, T*);
};

void columns_info_insert(std::string &szName, columns_info &CI);
columns_info* columns_info_find(std::string &szName);

template<class T>
bool TTDBase<T>::parse_data(const char* szPath)
{
	if (szPath == NULL || strlen(szPath) == 0)
	{
		return false;
	}
	auto p_columns = columns_info_find(m_name);
	if (p_columns == nullptr)
	{
		return false;
	}
	char* pData = nullptr;

	// get data
	FILE *fp = fopen(szPath, "rb");
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		long count = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		pData = new char[count + 1];
		memset(pData, 0, count + 1);
		if (fread(pData, 1, count, fp) != count)
		{
			delete pData;
			pData = nullptr;
		}
		fclose(fp);
	}

	//parser data
	if (pData == nullptr)
	{
		return false;
	}
	char temp[512];
	const char* beg = pData;
	const char* pos = pData;
	std::vector< std::vector<std::string> > txtData;
	while (true)
	{
		std::vector<std::string> list;
		while (true)
		{
			if (*pos == '\t')
			{
				memset(temp, 0, 512);
				strncpy(temp, beg, pos - beg);
				list.push_back(std::string(temp));
				beg = pos + 1;
			}
			else if (*pos == '\r')
			{
				strncpy(temp, beg, pos - beg);
				list.push_back(std::string(temp));
				txtData.push_back(list);
				pos += 2; //跳过\n
				beg = pos;
				break;
			}
			pos++;
		}

		if (*pos == '\0')
		{
			break;
		}
	}

	auto vColumns = p_columns->vColumns;
	for (size_t i = 0, i_end = txtData.size(); i < i_end; i++)
	{
		//读取每行文本
		std::vector<std::string>& txtLine = txtData[i];
		//创建每行对象
		T* p = new T();
		m_lines.push_back(p);

		for (size_t j = 0, j_end = vColumns.size(); j < j_end; j++)
		{
			std::string txt = "";
			if (txtLine.size() > j)
			{
				txt = txtLine[j];
			}

			int i_column = vColumns[j].i_column;
			int e_value = vColumns[j].e_value;
			int i_offset = vColumns[j].i_offset;

			switch (e_value)
			{
			case e_type_int:
			{
				*(int*)((char*)p + i_offset) = atoi(txt.c_str());
			}
			break;
			case e_type_float:
			{
				*(float*)((char*)p + i_offset) = (float)atof(txt.c_str());
			}
			break;
			case e_type_string:
			{
				*(std::string*)((char*)p + i_offset) = txt.c_str();
			}
			break;
			case e_type_vint:
			{
				if (txt.size() == 0)
				{
					break;
				}
				do
				{
					size_t index1 = txt.find_first_of('*');
					size_t index2 = txt.find_first_of('|');
					size_t index = index1<index2 ? index1 : index2;
					std::string temp = txt.substr(0, index);
					(*(std::vector<int>*)((char*)p + i_offset)).push_back(atoi(temp.c_str()));
					if (index == std::string::npos)
					{
						break;
					}
					else
					{
						txt = txt.substr(index + 1);
					}
				} while (txt.size() > 0);
			}
			break;
			case e_type_vfloat:
			{
				if (txt.size() == 0)
				{
					break;
				}
				do
				{
					size_t index1 = txt.find_first_of('*');
					size_t index2 = txt.find_first_of('|');
					size_t index = index1<index2 ? index1 : index2;
					std::string temp = txt.substr(0, index);
					(*(std::vector<float>*)((char*)p + i_offset)).push_back(atof(temp.c_str()));
					if (index == std::string::npos)
					{
						break;
					}
					else
					{
						txt = txt.substr(index + 1);
					}
				} while (txt.size() > 0);
			}
			break;
			case e_type_vstring:
			{
				if (txt.size() == 0)
				{
					break;
				}
				do
				{
					size_t index1 = txt.find_first_of('*');
					size_t index2 = txt.find_first_of('|');
					size_t index = index1<index2 ? index1 : index2;
					std::string temp = txt.substr(0, index);
					(*(std::vector<std::string>*)((char*)p + i_offset)).push_back(temp);
					if (index == std::string::npos)
					{
						break;
					}
					else
					{
						txt = txt.substr(index + 1);
					}
				} while (txt.size() > 0);
			}
			break;
			default:
				assert(false && "invalid type");
				break;
			}

		}
	}



	return true;
}

template<class T>
T* TTDBase<T>::get_line(int iLineNum)
{
	iLineNum = iLineNum + TTD_TITLE;
	if (iLineNum >= m_lines.size() || iLineNum < TTD_TITLE)
	{
		return nullptr;
	}
	return m_lines[iLineNum];
}

template<class T>
void TTDBase<T>::set_line(int iLineNum, T* _Data)
{
	mLines[iLineNum] = _Data;
}
//********************************************************
// 构造每行的基础定义
#define TTD_ENTER(name) \
		class l_##name { public:
#define TTD_COL(type, var) type var;
#define TTD_ARR(type, var) std::vector<type> var;
#define TTD_LEAVE() };
#include "Def.h"
#include "Undef.h"


//********************************************************
// 构造每个表的实例化模板的定义
#define TTD_ENTER(name) \
		class t_##name :public TTDBase<l_##name>{ 	\
						public:\
							t_##name() { m_name = #name; }\
							t_##name(const char* path) { m_name = #name; parse_data(path);}
						
#define TTD_COL(type, var)
#define TTD_ARR(type, var)
#define TTD_LEAVE() };
#include "Def.h"
#include "Undef.h"

//**************************
// 字段处理函数
value_type type_map(const char* _type);
void columns_info_insert(std::string &, columns_info&);

#define TTD_ENTER(name) \
		class column_info_##name \
		{ \
public:\
			typedef l_##name l_data_t; \
			column_info_##name() \
			{\
				columns_info _CSInfo;\
				std::string sName = #name;\
				unsigned int column = 0;
#define TTD_COL(type, var)\
				{\
					column_info i; \
					i.i_column = column; column++; \
					i.i_offset = offsetof(l_data_t, var); \
					i.e_value = type_map(#type);\
					_CSInfo.vColumns.push_back(i);\
				}
#define TTD_ARR(type, var)\
				{\
					column_info i; \
					i.i_column = column; column++;\
					i.i_offset = offsetof(l_data_t, var); \
					i.e_value = type_map("v"#type);\
					_CSInfo.vColumns.push_back(i);\
				}
#define TTD_LEAVE()\
				columns_info_insert(sName, _CSInfo);\
			}\
		};
#include "Def.h"
#include "Undef.h"

//********************************************************
// 真正生成记录
#define TTD_ENTER(name) \
		static column_info_##name _c_i_##name;
#define TTD_COL(type, var)
#define TTD_ARR(type, var)
#define TTD_LEAVE()
#include "Def.h"
#include "Undef.h"


__TTD_SPACE_END__





