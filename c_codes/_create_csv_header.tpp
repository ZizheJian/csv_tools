#pragma once

#include <string>
#include <sys/stat.h>
#include <vector>
#include "write_csv.tpp"

namespace csv_tools
{
// 文件已经存在时什么都不做
inline void _create_csv_header(const std::string &csv_path,const std::vector<std::string> &header)
{
    struct stat file_status;
    if(stat(csv_path.c_str(),&file_status)==0)
        return;
    write_csv(csv_path,{header},header.size(),false,false);
}
}
