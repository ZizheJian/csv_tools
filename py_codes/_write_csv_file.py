import csv,os

def _write_csv_file(csv_path:str,data:list[list[str]]):
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
