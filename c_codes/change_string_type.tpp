#pragma once

namespace csv_tools
{
using namespace std;

template<typename T>
string change_string_type(T value)
{
    if constexpr(is_same<T,float>::value || is_same<T,double>::value)
    {
        char buf[128];
        snprintf(buf,sizeof(buf),"%.15f",value);
        for (;;)
            if (buf[strlen(buf)-1]=='0')
                buf[strlen(buf)-1]=0;
            else
                break;
        if (buf[strlen(buf)-1]=='.')
            buf[strlen(buf)-1]=0;
        return string(buf);
    }
    else if constexpr(is_same<T,char*>::value)
        return string(value);
    else if constexpr(is_same<T,const char*>::value)
        return string(value);
    else if constexpr(is_same<T,string>::value)
        return value;
    else
        throw runtime_error("change_string_type 只能接受float,double,char*,const char*,string类型的参数");
}
}
