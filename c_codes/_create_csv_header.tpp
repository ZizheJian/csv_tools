#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include "_join_with_comma.tpp"
#include "read_csv.tpp"
#include "write_csv.tpp"

namespace csv_tools
{
    // 文件不存在或为空时写入表头。文件已有表头时，前几列必须和给出的表头一致
    inline void _create_csv_header(const std::string &csv_path,const std::vector<std::string> &header)
    {
        using namespace std;
        vector<vector<string>> data=read_csv(csv_path);
        if(data.empty())
            write_csv(csv_path,{header},header.size(),false,false);
        else if(data[0].size()<header.size()||!equal(header.begin(),header.end(),data[0].begin()))
        {
            vector<string> existing_header(data[0].begin(),data[0].begin()+min(data[0].size(),header.size()));
            throw invalid_argument(csv_path+"已有的表头前"+to_string(header.size())+"列（"+_join_with_comma(existing_header)+"）和给出的表头（"+_join_with_comma(header)+"）不一致");
        }
    }
}
