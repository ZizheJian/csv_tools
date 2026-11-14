#pragma once

#include <string>
#include <vector>
#include "_create_csv_header.tpp"

namespace csv_tools
{
    inline void create_csv_header(const std::string &csv_path,const std::vector<std::string> &header)
    {
        _create_csv_header(csv_path,header);
    }

    // 接受任意个表头，例如create_csv_header(csv_path,"rel_eb","t")
    template<typename... Headers>
    void create_csv_header(const std::string &csv_path,const Headers &...headers)
    {
        _create_csv_header(csv_path,{std::string(headers)...});
    }
}
