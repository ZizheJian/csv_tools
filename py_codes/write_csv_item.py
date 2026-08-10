from .change_string_type import change_string_type
from ._write_csv_item import _write_csv_item,_write_csv_item_uncertain_row_info_keys

def write_csv_item(csv_path:str,row_info,column_name:str,value,sort_row:bool=True,sort_column:bool=True):
    value=change_string_type(value)
    if type(row_info)!=dict and type(row_info)!=list:
        row_info=[change_string_type(row_info)]
        _write_csv_item_uncertain_row_info_keys(csv_path,row_info,column_name,value,sort_row,sort_column)
    elif type(row_info)==list:
        row_info=[change_string_type(item) for item in row_info]
        _write_csv_item_uncertain_row_info_keys(csv_path,row_info,column_name,value,sort_row,sort_column)
    else:
        row_info={k:change_string_type(v) for k,v in row_info.items()}
        _write_csv_item(csv_path,row_info,column_name,value,sort_row,sort_column)

def write_csv_item_2(csv_path:str,row_info1,row_info2,column_name:str,value,sort_row:bool=True,sort_column:bool=True):
    row_info=[change_string_type(row_info1),change_string_type(row_info2)]
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info,column_name,value,sort_row,sort_column)

def write_csv_item_3(csv_path:str,row_info1,row_info2,row_info3,column_name:str,value,sort_row:bool=True,sort_column:bool=True):
    row_info=[change_string_type(row_info1),change_string_type(row_info2),change_string_type(row_info3)]
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info,column_name,value,sort_row,sort_column)

def write_csv_item_4(csv_path:str,row_info1,row_info2,row_info3,row_info4,column_name:str,value,sort_row:bool=True,sort_column:bool=True):
    row_info=[change_string_type(row_info1),change_string_type(row_info2),change_string_type(row_info3),change_string_type(row_info4)]
    _write_csv_item_uncertain_row_info_keys(csv_path,row_info,column_name,value,sort_row,sort_column)