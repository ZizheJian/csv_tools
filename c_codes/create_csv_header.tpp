#pragma once

using namespace std;

void _create_csv_header(string &csv_path,vector<string> header);

void create_csv_header(string &csv_path,vector<string> header)
{
    _create_csv_header(csv_path,header);
}

void create_csv_header(string &csv_path,string header)
{
    _create_csv_header(csv_path,{header});
}

void create_csv_header(string &csv_path,string header1,string header2)
{
    _create_csv_header(csv_path,{header1,header2});
}

void create_csv_header(string &csv_path,string header1,string header2,string header3)
{
    _create_csv_header(csv_path,{header1,header2,header3});
}

void create_csv_header(string &csv_path,string header1,string header2,string header3,string header4)
{
    _create_csv_header(csv_path,{header1,header2,header3,header4});
}