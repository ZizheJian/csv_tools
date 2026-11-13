#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace csv_tools
{
// 文件不存在时返回空表
inline std::vector<std::vector<std::string>> read_csv(const std::string &csv_path)
{
    using namespace std;
    ifstream file(csv_path);
    if(!file.is_open())
        return {};
    vector<vector<string>> data;
    string line;
    while(getline(file,line))
    {
        if(!line.empty()&&line.back()=='\r')
            line.pop_back();
        vector<string> row;
        stringstream stream(line);
        string item;
        while(getline(stream,item,','))
            row.push_back(item);
        if(!line.empty()&&line.back()==',')
            row.push_back("");
        data.push_back(move(row));
    }
    return data;
}
}
