#pragma once

#include <cmath>
#include <cstdlib>
#include <string>

namespace csv_tools
{
    // 判断value是不是有限的数字，是的话把数值写入number。和Python版一样，inf和nan当作文字
    inline bool distinguish_value(const std::string &value,double &number)
    {
        using namespace std;
        if(value.empty()||value.find_first_of("xX")!=string::npos)
            return false;
        char *end=nullptr;
        number=strtod(value.c_str(),&end);
        return end!=value.c_str()&&*end==0&&isfinite(number);
    }

    // 排序规则：数字排在文字前面，数字从大到小，文字按字典顺序。返回负数表示str1排在前面，0表示两者相同
    inline int compare_value(const std::string &str1,const std::string &str2)
    {
        double number1=0,number2=0;
        bool is_number1=distinguish_value(str1,number1),is_number2=distinguish_value(str2,number2);
        if(is_number1!=is_number2)
            return is_number1?-1:1;
        if(is_number1)
            return number1>number2?-1:(number1<number2?1:0);
        return str1.compare(str2);
    }
}
