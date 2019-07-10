# fact-tables

This command will let you enter in offsets (which represent row numbers that contain a particular value) and store them in a run-length encoding.  You can run it with:
```
python fact-tables.py
```

# Commands
The following commands are supported:
## add
The add command (a) requires an offset to add into the run-length encoding:
```
$ python fact-table.py 
Enter your command:  a <offset>, q <offset>, <p> to print, or <x> to exit.
a 100
```
## query
The query command (q) also requires an offset and will print either True or False if the offset is found in the run-length encoding:
```
Enter your command:  a <offset>, q <offset>, <p> to print, or <x> to exit.
q 20
False
Enter your command:  a <offset>, q <offset>, <p> to print, or <x> to exit.
q 1000
False
```
## print
The print command (p) will print the string representation of the run length encoding:
```
Enter your command:  a <offset>, q <offset>, <p> to print, or <x> to exit.
p
start: 10, length: 6
start: 50, length: 1
start: 75, length: 5
start: 100, length: 2
start: 105, length: 1
```
## exit
The exit command (x) will end the program
