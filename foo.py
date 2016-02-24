#!/bin/python3
__author__ = 'radon'

import sys
import os



f = open(os.environ['OUTPUT_PATH'], 'w')


_arr_cnt = int(input())
_arr_i=0
_arr = []
while _arr_i < _arr_cnt:
    _arr_item = int(input());
    _arr.append(_arr_item)
    _arr_i+=1


res = sumOfIntegers(_arr);
f.write(str(res) + "\n")

f.close()
