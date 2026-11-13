from ._create_csv_header import _create_csv_header

def create_csv_header(csv_path:str,header):
    _create_csv_header(csv_path,list(header) if isinstance(header,(list,tuple)) else [header])
