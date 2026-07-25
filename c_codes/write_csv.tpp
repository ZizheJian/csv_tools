#pragma once

using namespace std;

void write_csv(string csv_path,vector<vector<string>> data,int query_row_key_len,bool sort_row=true,bool sort_column=true)
{
    vector<string> header=data[0];
    //////// 排序 ////////
    if (sort_row)
        for (int row_id_1=1;(uint64_t)row_id_1<data.size();row_id_1++)
            for (int row_id_2=row_id_1+1;(uint64_t)row_id_2<data.size();row_id_2++)
            {
                vector<string> row_key_1(data[row_id_1].begin(),data[row_id_1].begin()+query_row_key_len);
                vector<string> row_key_2(data[row_id_2].begin(),data[row_id_2].begin()+query_row_key_len);
                if (!compare_vector_string(row_key_1,row_key_2))
                    swap(data[row_id_1],data[row_id_2]);
            }
    if (sort_column)
        for (int column_id_1=query_row_key_len;(uint64_t)column_id_1<header.size();column_id_1++)
            for (int column_id_2=column_id_1+1;(uint64_t)column_id_2<header.size();column_id_2++)
                if (header[column_id_1]>header[column_id_2])
                {
                    swap(header[column_id_1],header[column_id_2]);
                    for (int row_id=0;(uint64_t)row_id<data.size();row_id++)
                        swap(data[row_id][column_id_1],data[row_id][column_id_2]);
                }
    //////// 写出csv ////////
    string output_str;
    for (int row_id=0;(uint64_t)row_id<data.size();row_id++)
    {
        for (int column_id=0;(uint64_t)column_id<data[row_id].size();column_id++)
        {
            output_str+=data[row_id][column_id];
            if ((uint64_t)column_id<data[row_id].size()-1)
                output_str+=",";
        }
        output_str+="\n";
    }
    FILE *f=fopen(csv_path.c_str(),"w");
    fwrite(output_str.c_str(),sizeof(char),output_str.size(),f);
    fclose(f);
}