# csv_tools

**English** | [中文](README_CN.md)

`csv_tools` fills experiment results into a CSV table one value at a time. Each write uses the leading columns, such as the error bound, to find the row and the column name to find the column, then stores the value there. Missing rows and columns are added automatically. The repository provides a C++ version and a Python version that write files in the same format.

## How values are written

- Rows are sorted by the leading columns: numbers come before text, numbers go from largest to smallest, and text is in alphabetical order. The remaining columns are sorted by name. Setting `sort_row` or `sort_column` to `false` turns sorting off.
- Decimals keep 15 significant digits without scientific notation. For example, `1.23e-10` is written as `0.000000000123`.
- Each write goes to a temporary file in the same directory, which then replaces the original file, so an interrupted write leaves the original file intact.

## Python

Requires Python 3.10 or later. When the repository is a submodule at `third_party/csv_tools`:

```python
from third_party.csv_tools.py_codes.write_csv_item import write_csv_item
from third_party.csv_tools.py_codes.create_csv_header import create_csv_header

write_csv_item("result.csv",{"rel_eb":0.01,"trial":1},"psnr",62.5)
create_csv_header("result2.csv",["rel_eb","t"])
write_csv_item("result2.csv",[0.01,0.5],"br",3.2)
```

- When `row_info` is a dictionary, it gives both the column names and the values.
- When `row_info` is a list or a single value, its items match the leading header columns in order, so the file must already have a header. `create_csv_header` creates one and does nothing when the file already exists.

## C++

Requires C++17 or later. Add the directory as a CMake subdirectory and link the target:

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

Values can be integers, decimals or strings.

### Limitation

Values written by the C++ version must not contain commas, double quotes or line breaks, and the C++ version cannot read CSV files that contain them. The Python version has no such limitation.
