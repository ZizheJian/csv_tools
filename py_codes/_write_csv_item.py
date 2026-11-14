import os,csv
from .distinguish_value import distinguish_value
from ._write_csv_file import _write_csv_file

# row_info是字典时同时给出列名和值，是列表时只给出值，按顺序对应表头的前几列
def _write_csv_item(csv_path:str,row_info:dict[str,str]|list[str],column_name:str,value:str,sort_row:bool=True,sort_column:bool=True):
    if not os.path.exists(csv_path):
        data=[]
    else:
        with open(csv_path,"r",newline="",encoding="utf-8") as f:
            data=list(csv.reader(f))
    ######## row_info只给出值时，按顺序对应表头的前几列 ########
    if isinstance(row_info,list):
        if len(data)==0:
            raise ValueError(f"{csv_path}不存在或为空，并且row_info没有给出列名")
        if len(row_info)>len(data[0]):
            raise ValueError(f"{csv_path}表头长度小于row_info长度")
        row_info=dict(zip(data[0],row_info))
    if column_name in row_info:
        raise ValueError(f"要写入的列{column_name}和row_info里的键重名")
    if len(data)==0:
        data.append(list(row_info)+[column_name])
    ######## 确认header的长度和其他行相同 ########
    header=data[0]
    for row_id in range(1,len(data)):
        if len(data[row_id])>len(header):
            raise ValueError(f"第{row_id}行数据长度大于表头长度")
        data[row_id]+=[""]*(len(header)-len(data[row_id]))
    ######## 确认前几列的header和row_info的key相同 ########
    if len(row_info)>len(header):
        raise ValueError("表头长度小于row_info长度")
    key_header=header[:len(row_info)]
    if set(key_header)!=set(row_info):
        raise ValueError(f"row_info的键（{','.join(row_info)}）和表头的前{len(row_info)}列（{','.join(key_header)}）不一致")
    query_row_key=[row_info[key] for key in key_header]
    key_count=len(query_row_key)
    ######## 寻找正确的行 ########
    query_row_id=1
    while query_row_id<len(data) and data[query_row_id][:key_count]!=query_row_key:
        query_row_id+=1
    if query_row_id==len(data):
        data.append(query_row_key+[""]*(len(header)-key_count))
    ######## 寻找正确的列 ########
    if column_name not in header[key_count:]:
        header.append(column_name)
        for row_id in range(1,len(data)):
            data[row_id].append("")
    query_column_id=header.index(column_name,key_count)
    data[query_row_id][query_column_id]=value
    ######## 排序 ########
    if sort_row:
        data[1:]=sorted(data[1:],key=lambda row:tuple(distinguish_value(item) for item in row[:key_count]))
    if sort_column:
        sorted_column_ids=sorted(range(key_count,len(header)),key=lambda column_id:header[column_id])
        sorted_column_ids=list(range(key_count))+sorted_column_ids
        data=[[row[column_id] for column_id in sorted_column_ids] for row in data]
    ######## 写出csv ########
    _write_csv_file(csv_path,data)
