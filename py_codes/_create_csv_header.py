import os,csv
from ._write_csv_file import _write_csv_file

# 文件不存在或为空时写入表头。文件已有表头时，前几列必须和给出的表头一致
def _create_csv_header(csv_path:str,header:list[str]):
    data=[]
    if os.path.exists(csv_path):
        with open(csv_path,"r",newline="",encoding="utf-8") as f:
            data=list(csv.reader(f))
    if len(data)==0:
        _write_csv_file(csv_path,[header])
    elif data[0][:len(header)]!=header:
        raise ValueError(f"{csv_path}已有的表头前{len(header)}列（{','.join(data[0][:len(header)])}）和给出的表头（{','.join(header)}）不一致")
