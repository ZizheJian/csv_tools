#pragma once

#include <string>
#include <vector>

namespace csv_tools
{
// 用逗号把多个名字连起来，用在报错信息里
inline std::string _join_with_comma(const std::vector<std::string> &names)
{
    std::string text;
    for(size_t name_id=0;name_id<names.size();name_id++)
        text+=(name_id?",":"")+names[name_id];
    return text;
}
}
