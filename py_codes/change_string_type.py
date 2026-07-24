def change_string_type(value):
    if isinstance(value,float):
        return f"{value:.15f}".rstrip("0").rstrip(".")
    return str(value)