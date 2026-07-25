#pragma once

using namespace std;

void _write_csv_item(string csv_path,vector<pair<string,string>> row_info,string column_name,string value,
    bool sort_row=true,bool sort_column=true);

void _write_csv_item_uncertain_row_info_keys(string csv_path,vector<string> row_info,string column_name,string value,
    bool sort_row=true,bool sort_column=true)
{
    vector<vector<string>> data=read_csv(csv_path);
    if (data.empty())
        throw invalid_argument(csv_path+"为空，并且row_info没有key");
    if (data[0].size()<row_info.size())
        throw invalid_argument(csv_path+"表头长度小于row_info长度");
    vector<pair<string,string>> row_info_pairs;
    for (int column_id=0;(uint64_t)column_id<row_info.size();column_id++)
        row_info_pairs.push_back(make_pair(data[0][column_id],row_info[column_id]));
    _write_csv_item(csv_path,row_info_pairs,column_name,value,sort_row,sort_column);
}

void _write_csv_item(string csv_path,vector<pair<string,string>> row_info,string column_name,string value,
    bool sort_row,bool sort_column)
{
    vector<vector<string>> data=read_csv(csv_path);
    if (data.empty())
    {
        data.push_back(vector<string>());
        for (int column_id=0;(uint64_t)column_id<row_info.size();column_id++)
            data[0].push_back(row_info[column_id].first);
    }
    //////// 确认header的长度和其他行相同 ////////
    vector<string> header=data[0];
    for (int row_id=1;(uint64_t)row_id<data.size();row_id++)
    {
        if (data[row_id].size()>header.size())
            throw invalid_argument("第"+to_string(row_id)+"行数据长度大于表头长度");
        else if (data[row_id].size()<header.size())
            data[row_id].resize(header.size(),"");
    }
    //////// 确认前几列的header和row_info的key相同 ////////
    if (row_info.size()>header.size())
        throw invalid_argument("表头长度小于row_info长度");
    vector<string> query_row_key;
    for (int column_id=0;(uint64_t)column_id<row_info.size();column_id++)
    {
        bool found_key=false;
        for (int column_id2=0;(uint64_t)column_id2<header.size();column_id2++)
            if (header[column_id]==row_info[column_id2].first)
            {
                found_key=true;
                query_row_key.push_back(row_info[column_id2].second);
                break;
            }
        if (!found_key)
            throw invalid_argument("row_info中缺少表头"+header[column_id]+"对应的值");
    }
    //////// 寻找正确的行 ////////
    bool found_query_row=false;
    int query_row_id=1;
    for (query_row_id=1;(uint64_t)query_row_id<data.size();query_row_id++)
    {
        bool is_query_row=true;
        for (int column_id=0;(uint64_t)column_id<query_row_key.size();column_id++)
            if (data[query_row_id][column_id]!=query_row_key[column_id])
            {
                is_query_row=false;
                break;
            }
        if (is_query_row)
        {
            found_query_row=true;
            break;
        }
    }
    if (!found_query_row)
    {
        query_row_id=data.size();
        data.push_back(vector<string>(header.size(),""));
        for (int column_id=0;(uint64_t)column_id<query_row_key.size();column_id++)
            data[query_row_id][column_id]=query_row_key[column_id];
    }
    //////// 寻找正确的列 ////////
    bool found_query_column=false;
    int query_column_id=0;
    for (query_column_id=query_row_key.size();(uint64_t)query_column_id<header.size();query_column_id++)
        if (header[query_column_id]==column_name)
        {
            found_query_column=true;
            break;
        }
    if (!found_query_column)
    {
        header.push_back(column_name);
        data[0].push_back(column_name);
        for (int row_id=1;(uint64_t)row_id<data.size();row_id++)
            data[row_id].push_back("");
        query_column_id=header.size()-1;
    }
    data[query_row_id][query_column_id]=value;
    //////// 写出csv ////////
    write_csv(csv_path,data,query_row_key.size(),sort_row,sort_column);
}