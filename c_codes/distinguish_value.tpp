#pragma once

namespace csv_tools
{
using namespace std;

inline bool distinguish_value(string value,double &number)
{
    if (value.empty())
        return false;
    char *end=nullptr;
    number=strtod(value.c_str(),&end);
    if (end==value.c_str() || *end!=0)
        return false;
    return true;
}

inline bool compare_string(string str1,string str2)
{
    double number1=0,number2=0;
    bool is_number1=distinguish_value(str1,number1);
    bool is_number2=distinguish_value(str2,number2);
    if (is_number1 && !is_number2)
        return true;
    else if (!is_number1 && is_number2)
        return false;
    else if (is_number1 && is_number2)
        return number1>number2;
    else
        return str1<str2;
    throw invalid_argument("无法比较"+str1+"和"+str2);
}

inline bool compare_vector_string(vector<string> vec1,vector<string> vec2)
{
    if (vec1.size()!=vec2.size())
        throw invalid_argument("无法比较长度不同的vec1和vec2");
    if (vec1.empty())
        throw invalid_argument("无法比较空的vec1和vec2");
    for (int i=0;(uint64_t)i<vec1.size();i++)
    {
        if (vec1[i]!=vec2[i])
            return compare_string(vec1[i],vec2[i]);
    }
    return false;
}
}
