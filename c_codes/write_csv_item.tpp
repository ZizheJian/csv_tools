#pragma once

namespace csv_tools
{
using namespace std;

template<typename T> string change_string_type(T value);

template<typename T1,typename T2>
void write_csv_item(string &csv_path,vector<pair<string,T1>> row_info,string column_name,T2 value,
    bool sort_row=true,bool sort_column=true)
{
    vector<pair<string,string>> row_info_str;
    for (auto &p:row_info)
        row_info_str.push_back(make_pair(p.first,change_string_type(p.second)));
    _write_csv_item(csv_path,row_info_str,column_name,change_string_type(value),sort_row,sort_column);
}

template<typename T1,typename T2>
void write_csv_item(string &csv_path,vector<T1> row_info,string column_name,T2 value,bool sort_row=true,bool sort_column=true)
{
    vector<string> row_info_str;
    for (auto &p:row_info)
        row_info_str.push_back(change_string_type(p));
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info_str,column_name,change_string_type(value),sort_row,sort_column);
}

template<typename T1,typename T2>
void write_csv_item(string &csv_path,T1 row_info,string column_name,T2 value,bool sort_row=true,bool sort_column=true)
{
    vector<string> row_info_str;
    row_info_str.push_back(change_string_type(row_info));
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info_str,column_name,change_string_type(value),sort_row,sort_column);
}

template<typename T1,typename T2,typename T3>
void write_csv_item_2(string &csv_path,T1 row_info1,T2 row_info2,string column_name,T3 value,bool sort_row=true,bool sort_column=true)
{
    vector<string> row_info_vec;
    row_info_vec.push_back(change_string_type(row_info1));
    row_info_vec.push_back(change_string_type(row_info2));
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info_vec,column_name,change_string_type(value),sort_row,sort_column);
}

template<typename T1,typename T2,typename T3,typename T4>
void write_csv_item_3(string &csv_path,T1 row_info1,T2 row_info2,T3 row_info3,string column_name,T4 value,bool sort_row=true,bool sort_column=true)
{
    vector<string> row_info_vec;
    row_info_vec.push_back(change_string_type(row_info1));
    row_info_vec.push_back(change_string_type(row_info2));
    row_info_vec.push_back(change_string_type(row_info3));
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info_vec,column_name,change_string_type(value),sort_row,sort_column);
}

template<typename T1,typename T2,typename T3,typename T4,typename T5>
void write_csv_item_4(string &csv_path,T1 row_info1,T2 row_info2,T3 row_info3,T4 row_info4,string column_name,T5 value,bool sort_row=true,bool sort_column=true)
{
    vector<string> row_info_vec;
    row_info_vec.push_back(change_string_type(row_info1));
    row_info_vec.push_back(change_string_type(row_info2));
    row_info_vec.push_back(change_string_type(row_info3));
    row_info_vec.push_back(change_string_type(row_info4));
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info_vec,column_name,change_string_type(value),sort_row,sort_column);
}
}
