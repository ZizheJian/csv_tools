import math

# 判断value是不是有限的数字。是的话返回(0,-数值)，否则返回(1,原文)，排序时数字在前、从大到小，文字在后、按字典顺序
def distinguish_value(value:str)->tuple[int,float|str]:
    # 只认ASCII写成的十进制数。十六进制、空格和下划线只有C++或Python一边认，统一当作文字
    if not value.isascii() or any(char in "xX_" or char.isspace() for char in value):
        return 1,value
    try:
        number=float(value)
    except ValueError:
        return 1,value
    # inf、nan和超出double范围的数当作文字，和C++版一致
    if not math.isfinite(number):
        return 1,value
    return 0,-number
