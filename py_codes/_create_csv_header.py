import os,csv

def _create_csv_header(csv_path:str,header:list):
    if os.path.exists(csv_path):
        return
    with open(csv_path,"w",newline="") as f:
        writer=csv.writer(f)
        writer.writerow(header)