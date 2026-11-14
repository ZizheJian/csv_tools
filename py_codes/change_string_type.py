import math,numbers
from decimal import Decimal

# 只接受整数、小数和字符串，numpy的整数和小数也算。bool在Python里也算整数，和C++版一样不接受
def change_string_type(value:int|float|str)->str:
    if isinstance(value,bool):
        raise TypeError(f"change_string_type只接受整数、小数和字符串，不能是{type(value).__name__}")
    if isinstance(value,numbers.Integral):
        return str(int(value))
    if isinstance(value,numbers.Real):
        value=float(value)
        if not math.isfinite(value):
            return str(value)
        # 保留15位有效数字，去掉计算误差带来的尾数，再写成不用科学计数法的形式，例如1.23e-10写成0.000000000123
        text=format(Decimal(f"{value:.15g}"),"f")
        return text.rstrip("0").rstrip(".") if "." in text else text
    if isinstance(value,str):
        return str(value)
    raise TypeError(f"change_string_type只接受整数、小数和字符串，不能是{type(value).__name__}")
