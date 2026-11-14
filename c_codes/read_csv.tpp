#pragma once

#include <cerrno>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <vector>

namespace csv_tools
{
    // 文件不存在时返回空表，存在但读不了时报错
    inline std::vector<std::vector<std::string>> read_csv(const std::string &csv_path)
    {
        using namespace std;
        struct stat file_status;
        if(stat(csv_path.c_str(),&file_status)!=0&&errno==ENOENT)
            return {};
        ifstream file(csv_path);
        if(!file.is_open())
            throw runtime_error("无法读取"+csv_path+"："+strerror(errno));
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
