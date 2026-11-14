import numbers
from .change_string_type import change_string_type
from ._write_csv_item import _write_csv_item

# row_info是字典{列名:值}，或者按表头顺序排列的值（列表或单个值）。值可以是整数、小数或字符串
def write_csv_item(csv_path:str,row_info:dict[str,int|float|str]|list[int|float|str]|int|float|str,column_name:str,value:int|float|str,sort_row:bool=True,sort_column:bool=True):
    value=change_string_type(value)
    if isinstance(row_info,dict):
        row_info={key:change_string_type(item) for key,item in row_info.items()}
        _write_csv_item(csv_path,row_info,column_name,value,sort_row,sort_column)
    elif isinstance(row_info,(list,str,numbers.Real)):
        # 没有给出列名时，按顺序对应表头的前几列
        if isinstance(row_info,list):
            row_info=[change_string_type(item) for item in row_info]
        else:
            row_info=[change_string_type(row_info)]
        _write_csv_item(csv_path,row_info,column_name,value,sort_row,sort_column)
    else:
        raise TypeError(f"row_info只能是字典、列表、整数、小数或字符串，不能是{type(row_info).__name__}")
