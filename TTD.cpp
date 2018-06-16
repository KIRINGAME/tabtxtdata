
#include "TTD.h"
__TTD_SPACE_BEG__

#pragma init_seg(lib)
static std::unordered_map<std::string, columns_info>	map_columns_info;
void columns_info_insert(std::string &szName, columns_info &CI)
{
	map_columns_info.insert(std::make_pair(szName, CI));
}
columns_info* columns_info_find(std::string &szName)
{
	auto& it = map_columns_info.find(szName);
	return (it == map_columns_info.end()) ? nullptr : &(it->second);
}

value_type type_map(const char* _type)
{
	std::string type = _type;
	if (type == "int")
	{
		return e_type_int;
	}
	else if (type == "float")
	{
		return e_type_float;
	}
	else if (type == "std::string")
	{
		return e_type_string;
	}
	else if (type == "vint")
	{
		return e_type_vint;
	}
	else if (type == "vfloat")
	{
		return e_type_vfloat;
	}
	else if (type == "vstd::string")
	{
		return e_type_vstring;
	}
	assert(0);
	return e_type_string;
}




__TTD_SPACE_END__