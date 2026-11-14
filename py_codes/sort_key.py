import math

# 排序时一格对应的键：有限的数字返回(0,-数值)，其他返回(1,原文)。这样数字排在文字前面、从大到小，文字按字典顺序
def sort_key(value:str)->tuple[int,float|str]:
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
