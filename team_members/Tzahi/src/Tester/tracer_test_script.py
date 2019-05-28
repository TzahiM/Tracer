#!/usr/bin/python

import sys

print ('Number of arguments:', len(sys.argv), 'arguments.')
print ('Argument List:', str(sys.argv))

input_lines = None
with open("output.txt", "r") as tested_input_file: # Use file to refer to the file object
    input_lines = tested_input_file.readlines()


ref_input_lines = None
with open("refference.txt", "r") as tested_refference_file: # Use file to refer to the file object
    ref_input_lines = tested_refference_file.readlines()


input_lines = None
with open("output.txt", "r") as tested_input_file: # Use file to refer to the file object
    input_lines = tested_input_file.readlines()


ref_input_lines = None
with open("refference.txt", "r") as tested_refference_file: # Use file to refer to the file object
    ref_input_lines = tested_refference_file.readlines()

line_index = 0
for in_line in input_lines:
    ref_line = ref_input_lines[line_index]
    print ( int(line_index), ":expecting:", repr(ref_line))
    in_line = input_lines[line_index]
    if in_line == ref_line:
        print( "OK")
    else:
        print ( "but recived:", repr(in_line))
    line_index +=1
