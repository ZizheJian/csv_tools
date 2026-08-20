from ._create_csv_header import _create_csv_header

def create_csv_header(csv_path:str,header):
    if type(header)!=list:
        _create_csv_header(csv_path,[header])
    else:
        _create_csv_header(csv_path,header)

def create_csv_header_2(csv_path:str,header1:str,header2:str):
    _create_csv_header(csv_path,[header1,header2])

def create_csv_header_3(csv_path:str,header1:str,header2:str,header3:str):
    _create_csv_header(csv_path,[header1,header2,header3])

def create_csv_header_4(csv_path:str,header1:str,header2:str,header3:str,header4:str):
    _create_csv_header(csv_path,[header1,header2,header3,header4])
