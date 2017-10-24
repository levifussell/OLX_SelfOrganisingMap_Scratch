import numpy as np
import pandas as pd
import csv

def run():
    print("hello world")

    fileLocation = '../../../Datasets/OXL_Hackerrank/user_data/user_data.csv'
    # with open(fileLocation, 'rb') as csvfile:
        # reader = csv.reader(csvfile, delimeter = ' ', quotechar = '\"')
        # data = np.zeros(len(reader), 1);
        # for row in reader:
            # data[i] = row
    # data = np.genfromtxt(fileLocation, delimiter = ',')
    df = pd.read_csv(fileLocation, sep = ',', header=None)
    print(df.values)

if __name__ == "__main__":
    run()
