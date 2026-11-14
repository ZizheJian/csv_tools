#pragma once

#include <cmath>
#include <cstdlib>
#include <string>

namespace csv_tools
{
    // 判断value是不是有限的数字，是的话把数值写入number。inf、nan和超出double范围的数当作文字
    inline bool is_number(const std::string &value,double &number)
    {
        using namespace std;
        // 十六进制、空格和下划线只有C++或Python一边认，和Python版一样统一当作文字
        if(value.find_first_of("xX_ \t\n\v\f\r")!=string::npos)
            return false;
        char *end=nullptr;
        number=strtod(value.c_str(),&end);
        return end!=value.c_str()&&*end==0&&isfinite(number);
    }

    // 排序规则：数字排在文字前面，数字从大到小，文字按字典顺序。返回负数表示str1排在前面，0表示两者相同
    inline int compare_value(const std::string &str1,const std::string &str2)
    {
        double number1=0,number2=0;
        bool is_number1=is_number(str1,number1),is_number2=is_number(str2,number2);
        if(is_number1!=is_number2)
            return is_number1?-1:1;
        if(is_number1)
            return number1>number2?-1:(number1<number2?1:0);
        return str1.compare(str2);
    }
}
