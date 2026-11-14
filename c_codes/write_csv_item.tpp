#pragma once

#include <string>
#include <utility>
#include <vector>
#include "_write_csv_item.tpp"
#include "change_string_type.tpp"

namespace csv_tools
{
// row_info同时给出列名和值，例如{{"rel_eb",0.01},{"t",0.5}}
template<typename T1,typename T2>
void write_csv_item(const std::string &csv_path,const std::vector<std::pair<std::string,T1>> &row_info,const std::string &column_name,const T2 &value,bool sort_row=true,bool sort_column=true)
{
    std::vector<std::pair<std::string,std::string>> row_info_str;
    for(const std::pair<std::string,T1> &info:row_info)
        row_info_str.emplace_back(info.first,change_string_type(info.second));
    _write_csv_item(csv_path,row_info_str,column_name,change_string_type(value),sort_row,sort_column);
}

// row_info只给出值，按顺序对应表头的前几列
template<typename T1,typename T2>
void write_csv_item(const std::string &csv_path,const std::vector<T1> &row_info,const std::string &column_name,const T2 &value,bool sort_row=true,bool sort_column=true)
{
    std::vector<std::string> row_info_str;
    for(const T1 &info:row_info)
        row_info_str.push_back(change_string_type(info));
    _write_csv_item(csv_path,row_info_str,column_name,change_string_type(value),sort_row,sort_column);
}

// row_info只有一个值，对应表头的第一列
template<typename T1,typename T2>
void write_csv_item(const std::string &csv_path,const T1 &row_info,const std::string &column_name,const T2 &value,bool sort_row=true,bool sort_column=true)
{
    _write_csv_item(csv_path,std::vector<std::string>{change_string_type(row_info)},column_name,change_string_type(value),sort_row,sort_column);
}
}
