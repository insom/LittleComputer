#!/usr/bin/python

# Copyright 2016 Aaron Brady, MIT License

import sys

PER_LINE = 8

def main(input, output):
    i = 0
    f = sys.stdin
    if input != '-':
        f = open(input, 'rb')
    while True:
        line = f.read(PER_LINE)
        for octet in line:
            output.write("o %d %d " % (i, ord(octet)))
            i = i + 1
        output.write("\n")
        if len(line) < PER_LINE:
            break

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print >>sys.stderr, "%s <filename or ->" % sys.argv[0]
        sys.exit(-1)
    main(sys.argv[1], sys.stdout)
