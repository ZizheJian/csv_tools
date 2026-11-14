from .read_csv import read_csv
from .write_csv import write_csv

# 文件不存在或为空时写入表头。文件已有表头时，前几列必须和给出的表头一致
def _create_csv_header(csv_path:str,header:list[str]):
    data=read_csv(csv_path)
    if len(data)==0:
        write_csv(csv_path,[header],len(header),False,False)
    elif data[0][:len(header)]!=header:
        raise ValueError(f"{csv_path}已有的表头前{len(header)}列（{','.join(data[0][:len(header)])}）和给出的表头（{','.join(header)}）不一致")
