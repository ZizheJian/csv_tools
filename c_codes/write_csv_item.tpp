#pragma once

#include <string>
#include <utility>
#include <vector>
#include "_write_csv_item.tpp"
#include "change_string_type.tpp"

namespace csv_tools
{
    // row_info里的一个值，可以是整数、小数或字符串，构造时就转成文字，这样同一个row_info里可以混用不同类型
    struct csv_value
    {
        std::string text;
        template<typename T>
        csv_value(const T &value):text(change_string_type(value)){}
        operator std::string() const{return text;}
    };

    // row_info同时给出列名和值，例如{{"task","tpost20"},{"rel_eb",0.01},{"trial",1}}，值的类型可以混用
    template<typename T>
    void write_csv_item(const std::string &csv_path,const std::vector<std::pair<std::string,csv_value>> &row_info,const std::string &column_name,const T &value,bool sort_row=true,bool sort_column=true)
    {
        std::vector<std::pair<std::string,std::string>> row_info_str;
        for(const std::pair<std::string,csv_value> &info:row_info)
            row_info_str.emplace_back(info.first,info.second.text);
        _write_csv_item(csv_path,row_info_str,column_name,change_string_type(value),sort_row,sort_column);
    }

    // row_info只给出值，按顺序对应表头的前几列。要混用不同类型时用std::vector<csv_value>
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
