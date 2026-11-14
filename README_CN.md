# csv_tools

[English](README.md) | **中文**

`csv_tools`把实验结果一项一项地填进CSV表格。每次填写时，用前几列（例如误差界）找到对应的行，再按列名找到对应的列，把值写进去。找不到的行和列会自动添加。仓库提供C++版和Python版，两者写出的文件格式相同。

## 写入规则

- 行按前几列排序：数字排在文字前面，数字从大到小，文字按字典顺序。其余的列按列名排序。把`sort_row`或`sort_column`设为`false`可以关掉排序。
- 值可以是整数、小数或字符串，Python版也接受numpy的整数和小数。布尔值和其他类型会报错。
- 小数保留15位有效数字，不用科学计数法，例如`1.23e-10`写成`0.000000000123`。
- 写入时先写到同一目录下的临时文件，写完再替换原文件，中途被打断时原文件保持完整。

## Python

需要Python 3.10或更新的版本。仓库以子模块形式放在`third_party/csv_tools`时：

```python
from third_party.csv_tools.py_codes.write_csv_item import write_csv_item
from third_party.csv_tools.py_codes.create_csv_header import create_csv_header

write_csv_item("result.csv",{"rel_eb":0.01,"trial":1},"psnr",62.5)
create_csv_header("result2.csv",["rel_eb","t"])
write_csv_item("result2.csv",[0.01,0.5],"br",3.2)
```

- `row_info`是字典时，同时给出列名和值。
- `row_info`是列表或单个值时，按顺序对应表头的前几列，这时文件必须已经有表头，可以先用`create_csv_header`创建。文件已经有表头时，`create_csv_header`会检查表头的前几列和给出的是否一致，不一致就报错。

## C++

需要C++17或更新的版本。在CMake里把目录加为子目录，再链接目标：

```cmake
add_subdirectory(third_party/csv_tools/c_codes ${CMAKE_BINARY_DIR}/csv_tools_build)
target_link_libraries(my_target PRIVATE csv_tools)
```

```cpp
#include <csv.hpp>

csv_tools::create_csv_header("result.csv","rel_eb","t");
csv_tools::write_csv_item("result.csv",std::vector<double>{0.01,0.5},"br",3.2);
csv_tools::write_csv_item("result.csv",std::vector<std::pair<std::string,double>>{{"rel_eb",0.01},{"t",0.5}},"psnr",62.5);
```

### 限制

C++版写入的值里不能有逗号、双引号和换行，也读不了含有这些字符的CSV。Python版没有这个限制。
