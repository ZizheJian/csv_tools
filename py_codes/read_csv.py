import os,csv

# 文件不存在时返回空表，存在但读不了时open会报错
def read_csv(csv_path:str)->list[list[str]]:
    if not os.path.exists(csv_path):
        return []
    with open(csv_path,"r",newline="",encoding="utf-8") as f:
        return list(csv.reader(f))
