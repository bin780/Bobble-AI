import pandas as pd     # importing pandas library for reading csv file

import sys               # importing system to read from CLI

argl=sys.argv

df=pd.read_csv(argl[1],header=None)

df=df.fillna("nf")         # filling Null with 'nf'

def Permute(n):              # function to compute all permutations
    if n>=df.shape[0]:
        l=[""]
        return l
    ml=Permute(n+1)
    ans=[str(i)+str(j) for i in df.iloc[n] for j in ml if i!='nf' and j!='nf']
    return ans


output=Permute(0)     # calling the function


for i in range(len(output)-1):           # printing
    print(output[i],end=", ")
print(output[len(output)-1],end="")



