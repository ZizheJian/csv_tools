#pragma once

namespace csv_tools
{
using namespace std;

inline void _create_csv_header(string &csv_path,vector<string> header);

inline void create_csv_header(string &csv_path,vector<string> header)
{
    _create_csv_header(csv_path,header);
}

inline void create_csv_header(string &csv_path,string header)
{
    _create_csv_header(csv_path,{header});
}

inline void create_csv_header(string &csv_path,string header1,string header2)
{
    _create_csv_header(csv_path,{header1,header2});
}

inline void create_csv_header(string &csv_path,string header1,string header2,string header3)
{
    _create_csv_header(csv_path,{header1,header2,header3});
}

inline void create_csv_header(string &csv_path,string header1,string header2,string header3,string header4)
{
    _create_csv_header(csv_path,{header1,header2,header3,header4});
}
}
