# C programming exercises

To run these programs, you must first compile them:
```sh
cc -o <executable name> <c file>
```

For example, you can compile and run the hanoi program using the following commands:
```sh
$ cc -o hanoi hanoi.c
$ ./hanoi 3
2	1	0
3	0	0
------------------------------
3	1	2
------------------------------
3	0	1
0	0	2
------------------------------
0	3	1
0	0	2
------------------------------
1	3	2
------------------------------
1	2	0
0	3	0
------------------------------
0	1	0
0	2	0
0	3	0
------------------------------
Number of moves was: 7
```

A number of the programs take an input file.  input.txt has the example format needed.
