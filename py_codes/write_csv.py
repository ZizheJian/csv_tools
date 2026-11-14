import csv,os
from .sort_key import sort_key

# 前query_row_key_len列是行的标识。sort_row按标识给行排序，sort_column按列名给其余的列排序
def write_csv(csv_path:str,data:list[list[str]],query_row_key_len:int,sort_row:bool=True,sort_column:bool=True):
    ######## 排序 ########
    if sort_row:
        data=data[:1]+sorted(data[1:],key=lambda row:tuple(sort_key(item) for item in row[:query_row_key_len]))
    if sort_column and len(data)>0:
        column_ids=list(range(query_row_key_len))+sorted(range(query_row_key_len,len(data[0])),key=lambda column_id:data[0][column_id])
        data=[[row[column_id] for column_id in column_ids] for row in data]
    ######## 写出csv ########
    # 先写到同一目录下的临时文件，写完再替换原文件。替换是一步完成的，中途被打断时原文件保持完整
    directory,file_name=os.path.split(os.path.abspath(csv_path))
    temp_path=os.path.join(directory,f".{file_name}.{os.getpid()}.tmp")
    try:
        with open(temp_path,"w",newline="",encoding="utf-8") as f:
            csv.writer(f,lineterminator="\n").writerows(data)
            f.flush()
            os.fsync(f.fileno())
        # 新文件的权限和原文件保持一致
        if os.path.exists(csv_path):
            os.chmod(temp_path,os.stat(csv_path).st_mode&0o7777)
        os.replace(temp_path,csv_path)
    except BaseException:
        if os.path.exists(temp_path):
            os.remove(temp_path)
        raise
