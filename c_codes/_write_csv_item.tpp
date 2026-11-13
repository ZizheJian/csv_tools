#pragma once

#include <algorithm>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "read_csv.tpp"
#include "write_csv.tpp"

namespace csv_tools
{
inline void _write_csv_item(const std::string &csv_path,const std::vector<std::pair<std::string,std::string>> &row_info,const std::string &column_name,const std::string &value,bool sort_row=true,bool sort_column=true)
{
    using namespace std;
    if(any_of(row_info.begin(),row_info.end(),[&](const pair<string,string> &info){return info.first==column_name;}))
        throw invalid_argument("要写入的列"+column_name+"和row_info里的键重名");
    vector<vector<string>> data=read_csv(csv_path);
    if(data.empty())
    {
        data.push_back(vector<string>());
        for(const pair<string,string> &info:row_info)
            data[0].push_back(info.first);
    }
    //////// 确认header的长度和其他行相同 ////////
    vector<string> header=data[0];
    for(size_t row_id=1;row_id<data.size();row_id++)
    {
        if(data[row_id].size()>header.size())
            throw invalid_argument("第"+to_string(row_id)+"行数据长度大于表头长度");
        data[row_id].resize(header.size(),"");
    }
    //////// 确认前几列的header和row_info的key相同 ////////
    if(row_info.size()>header.size())
        throw invalid_argument("表头长度小于row_info长度");
    vector<string> key_header(header.begin(),header.begin()+row_info.size()),row_info_keys;
    for(const pair<string,string> &info:row_info)
        row_info_keys.push_back(info.first);
    if(set<string>(key_header.begin(),key_header.end())!=set<string>(row_info_keys.begin(),row_info_keys.end()))
    {
        auto join=[](const vector<string> &names){string text;for(size_t i=0;i<names.size();i++)text+=(i?",":"")+names[i];return text;};
        throw invalid_argument("row_info的键（"+join(row_info_keys)+"）和表头的前"+to_string(row_info.size())+"列（"+join(key_header)+"）不一致");
    }
    vector<string> query_row_key;
    for(const string &key:key_header)
        query_row_key.push_back(find_if(row_info.begin(),row_info.end(),[&](const pair<string,string> &info){return info.first==key;})->second);
    //////// 寻找正确的行 ////////
    size_t query_row_id=1;
    while(query_row_id<data.size()&&!equal(query_row_key.begin(),query_row_key.end(),data[query_row_id].begin()))
        query_row_id++;
    if(query_row_id==data.size())
    {
        data.push_back(vector<string>(header.size(),""));
        copy(query_row_key.begin(),query_row_key.end(),data.back().begin());
    }
    //////// 寻找正确的列 ////////
    size_t query_column_id=query_row_key.size();
    while(query_column_id<header.size()&&header[query_column_id]!=column_name)
        query_column_id++;
    if(query_column_id==header.size())
    {
        data[0].push_back(column_name);
        for(size_t row_id=1;row_id<data.size();row_id++)
            data[row_id].push_back("");
    }
    data[query_row_id][query_column_id]=value;
    //////// 写出csv ////////
    write_csv(csv_path,data,query_row_key.size(),sort_row,sort_column);
}

// row_info只给出值时，按顺序对应表头的前几列
inline void _write_csv_item_uncertain_row_info_keys(const std::string &csv_path,const std::vector<std::string> &row_info,const std::string &column_name,const std::string &value,bool sort_row=true,bool sort_column=true)
{
    using namespace std;
    vector<vector<string>> data=read_csv(csv_path);
    if(data.empty())
        throw invalid_argument(csv_path+"为空，并且row_info没有key");
    if(data[0].size()<row_info.size())
        throw invalid_argument(csv_path+"表头长度小于row_info长度");
    vector<pair<string,string>> row_info_pairs;
    for(size_t column_id=0;column_id<row_info.size();column_id++)
        row_info_pairs.emplace_back(data[0][column_id],row_info[column_id]);
    _write_csv_item(csv_path,row_info_pairs,column_name,value,sort_row,sort_column);
}
}
