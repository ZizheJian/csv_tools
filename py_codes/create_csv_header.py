from ._create_csv_header import _create_csv_header

def create_csv_header(csv_path:str,header:list[str]|str):
    if not isinstance(header,(list,str)):
        raise TypeError(f"header只能是列表或字符串，不能是{type(header).__name__}")
    _create_csv_header(csv_path,header if isinstance(header,list) else [header])
