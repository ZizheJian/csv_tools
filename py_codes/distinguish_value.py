from decimal import Decimal,InvalidOperation

def distinguish_value(value:str)->tuple[int,Decimal|str]:
    try:
        number=Decimal(value)
        if not number.is_finite():
            raise InvalidOperation
        return 0,-number
    except (InvalidOperation,ValueError):
        return 1,value
