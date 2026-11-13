import os,csv
from .distinguish_value import distinguish_value
from ._write_csv_file import _write_csv_file

def _write_csv_item_uncertain_row_info_keys(csv_path:str,row_info:list[str],column_name:str,value:str,sort_row:bool=True,sort_column:bool=True):
    if not os.path.exists(csv_path):
        raise ValueError(f"{csv_path}不存在，并且row_info没有key")
    with open(csv_path,"r",newline="",encoding="utf-8") as f:
        data=list(csv.reader(f))
    if len(data)==0:
        raise ValueError(f"{csv_path}为空，并且row_info没有key")
    if len(data[0])<len(row_info):
        raise ValueError(f"{csv_path}表头长度小于row_info长度")
    row_info_keys=data[0][:len(row_info)]
    row_info={row_info_keys[column_id]:row_info[column_id] for column_id in range(len(row_info_keys))}
    _write_csv_item(csv_path,row_info,column_name,value,sort_row,sort_column)

def _write_csv_item(csv_path:str,row_info:dict[str,str],column_name:str,value:str,sort_row:bool=True,sort_column:bool=True):
    if column_name in row_info:
        raise ValueError(f"要写入的列{column_name}和row_info里的键重名")
    if not os.path.exists(csv_path):
        data=[]
    else:
        with open(csv_path,"r",newline="",encoding="utf-8") as f:
            data=list(csv.reader(f))
    if len(data)==0:
        header=list(row_info.keys())
        header.append(column_name)
        data.append(header)
    ######## 确认header的长度和其他行相同 ########
    header=data[0]
    for row_id in range(1,len(data)):
        if len(data[row_id])>len(header):
            raise ValueError(f"第{row_id}行数据长度大于表头长度")
        elif len(data[row_id])<len(header):
            data[row_id]+=[""]*(len(header)-len(data[row_id]))
    ######## 确认前几列的header和row_info的key相同 ########
    if len(row_info)>len(header):
        raise ValueError("表头长度小于row_info长度")
    key_header=header[:len(row_info)]
    if set(key_header)!=set(row_info):
        raise ValueError(f"row_info的键（{','.join(row_info)}）和表头的前{len(row_info)}列（{','.join(key_header)}）不一致")
    query_row_key=[row_info[key] for key in key_header]
    ######## 寻找正确的行 ########
    found_query_row=False
    query_row_id=1
    for query_row_id in range(1,len(data)):
        if all([data[query_row_id][column_id]==query_row_key[column_id] for column_id in range(len(query_row_key))]):
            found_query_row=True
            break
    if not found_query_row:
        data.append([""]*len(header))
        for column_id in range(len(query_row_key)):
            data[-1][column_id]=query_row_key[column_id]
        query_row_id=len(data)-1
    ######## 寻找正确的列 ########
    found_query_column=False
    query_column_id=0
    for query_column_id in range(len(query_row_key),len(header)):
        if header[query_column_id]==column_name:
            found_query_column=True
            break
    if not found_query_column:
        header.append(column_name)
        for row_id in range(1,len(data)):
            data[row_id].append("")
        query_column_id=len(header)-1
    data[query_row_id][query_column_id]=value
    ######## 排序 ########
    if sort_row:
        data[1:]=sorted(data[1:],
                        key=lambda row:tuple(distinguish_value(row[column_id]) for column_id in range(len(query_row_key))))
    if sort_column:
        sorted_column_ids=sorted(range(len(query_row_key),len(header)),key=lambda column_id:header[column_id])
        sorted_column_ids=list(range(len(query_row_key)))+sorted_column_ids
        data=[[row[column_id] for column_id in sorted_column_ids] for row in data]
    ######## 写出csv ########
    _write_csv_file(csv_path,data)
