#pragma once

namespace csv_tools
{
using namespace std;

inline void _create_csv_header(string &csv_path,vector<string> header)
{
    FILE *f=fopen(csv_path.c_str(),"r");
    if (f!=NULL)
    {
        fclose(f);
        return;
    }
    vector<vector<string>> data;
    data.push_back(header);
    write_csv(csv_path,data,header.size(),false,false);
}
}
