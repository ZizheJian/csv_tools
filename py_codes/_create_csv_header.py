import os
from ._write_csv_file import _write_csv_file

def _create_csv_header(csv_path:str,header:list[str]):
    if os.path.exists(csv_path):
        return
    _write_csv_file(csv_path,[header])
