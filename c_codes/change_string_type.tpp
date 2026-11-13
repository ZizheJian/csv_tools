#pragma once

#include <cmath>
#include <cstdio>
#include <string>
#include <type_traits>

namespace csv_tools
{
// 保留15位有效数字，去掉计算误差带来的尾数，再写成不用科学计数法的形式，例如1.23e-10写成0.000000000123
inline std::string format_decimal(double value)
{
    using namespace std;
    if(!isfinite(value))
        return isnan(value)?"nan":(value>0?"inf":"-inf");
    char buffer[32];
    snprintf(buffer,sizeof(buffer),"%.14e",value);
    string text=buffer;
    size_t e_position=text.find('e');
    string sign=text[0]=='-'?"-":"";
    string digits;
    for(size_t i=sign.size();i<e_position;i++)
        if(text[i]!='.')
            digits+=text[i];
    // 数值等于0.digits乘以10的point次方，point也就是小数点前面的位数
    int point=stoi(text.substr(e_position+1))+1,digit_num=digits.size();
    string result;
    if(point<=0)
        result="0."+string(-point,'0')+digits;
    else if(point>=digit_num)
        result=digits+string(point-digit_num,'0');
    else
        result=digits.substr(0,point)+"."+digits.substr(point);
    if(result.find('.')!=string::npos)
    {
        while(result.back()=='0')
            result.pop_back();
        if(result.back()=='.')
            result.pop_back();
    }
    return sign+result;
}

template<typename T>
std::string change_string_type(const T &value)
{
    using namespace std;
    if constexpr(is_floating_point_v<T>)
        return format_decimal(value);
    else if constexpr(is_integral_v<T>&&!is_same_v<T,bool>&&!is_same_v<T,char>)
        return to_string(value);
    else if constexpr(is_convertible_v<const T&,string>)
        return string(value);
    else
        static_assert(!sizeof(T),"change_string_type只接受整数、小数和字符串");
}
}
