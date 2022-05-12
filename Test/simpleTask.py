import os 
import sys 

def writePyramids(filePath, baseSize, count, char):
    f = open(filePath, "w+")
    wline = []
    mid = (int)(baseSize/2)
    ind = baseSize - mid
    start = 1
    for i in range(0,mid):
        s = ""
        blank = " " * ind 
        cval = char * start
        s = blank + cval + blank + "\n"
        wline.append(s)
        ind = ind - 1
        start = start + 2

    f.writelines(wline)
    f.close()
    return ""

if __name__ == "__main__":
    print("Hello World")
    z = writePyramids('pyramid13_test.txt', 13, 6, 'X')