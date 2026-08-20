#pragma once

namespace csv_tools
{
using namespace std;

inline vector<vector<string>> read_csv(string csv_path)
{
    ifstream file(csv_path);
    if (!file.is_open())
        return {};
    vector<vector<string>> data;
    string line;
    while (getline(file,line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        vector<string> row;
        stringstream ss(line);
        string item;
        while (getline(ss,item,','))
            row.push_back(item);
        if (!line.empty() && line.back() == ',')
            row.push_back("");
        data.push_back(move(row));
    }
    file.close();
    return data;
}
}
