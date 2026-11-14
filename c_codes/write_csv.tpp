#pragma once

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <numeric>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include "is_number.tpp"

namespace csv_tools
{
    // 前query_row_key_len列是行的标识。sort_row按标识给行排序，sort_column按列名给其余的列排序
    inline void write_csv(const std::string &csv_path,std::vector<std::vector<std::string>> data,size_t query_row_key_len,bool sort_row=true,bool sort_column=true)
    {
        using namespace std;
        //////// 排序 ////////
        if(sort_row&&data.size()>1)
            stable_sort(data.begin()+1,data.end(),[&](const vector<string> &row1,const vector<string> &row2)
            {
                for(size_t column_id=0;column_id<query_row_key_len;column_id++)
                    if(int result=compare_value(row1[column_id],row2[column_id]);result!=0)
                        return result<0;
                return false;
            });
        if(sort_column&&!data.empty())
        {
            vector<size_t> column_ids(data[0].size());
            iota(column_ids.begin(),column_ids.end(),0);
            stable_sort(column_ids.begin()+query_row_key_len,column_ids.end(),[&](size_t column_id1,size_t column_id2){return data[0][column_id1]<data[0][column_id2];});
            for(vector<string> &row:data)
            {
                vector<string> sorted_row;
                for(size_t column_id:column_ids)
                    sorted_row.push_back(row[column_id]);
                row=move(sorted_row);
            }
        }
        //////// 写出csv ////////
        string output;
        for(const vector<string> &row:data)
        {
            for(size_t column_id=0;column_id<row.size();column_id++)
                output+=(column_id==0?"":",")+row[column_id];
            output+="\n";
        }
        // 先写到同一目录下的临时文件，写完再替换原文件。替换是一步完成的，中途被打断时原文件保持完整
        size_t slash_position=csv_path.find_last_of('/');
        string directory=slash_position==string::npos?"":csv_path.substr(0,slash_position+1);
        string file_name=slash_position==string::npos?csv_path:csv_path.substr(slash_position+1);
        string temp_path=directory+"."+file_name+"."+to_string(getpid())+".tmp";
        int fd=open(temp_path.c_str(),O_WRONLY|O_CREAT|O_TRUNC,0666);
        if(fd<0)
            throw runtime_error("无法写入"+csv_path+"："+strerror(errno));
        auto fail=[&](const string &step)
        {
            int error=errno;
            if(fd>=0)
                close(fd);
            unlink(temp_path.c_str());
            throw runtime_error(step+csv_path+"："+strerror(error));
        };
        for(size_t written_size=0;written_size<output.size();)
        {
            ssize_t size=write(fd,output.data()+written_size,output.size()-written_size);
            if(size<0&&errno!=EINTR)
                fail("无法写入");
            if(size>0)
                written_size+=size;
        }
        // 新文件的权限和原文件保持一致
        struct stat original_status;
        if(stat(csv_path.c_str(),&original_status)==0&&fchmod(fd,original_status.st_mode&07777)!=0)
            fail("无法设置权限：");
        if(fsync(fd)!=0)
            fail("无法写入");
        int close_result=close(fd);
        fd=-1;
        if(close_result!=0)
            fail("无法写入");
        if(rename(temp_path.c_str(),csv_path.c_str())!=0)
            fail("无法替换");
    }
}
