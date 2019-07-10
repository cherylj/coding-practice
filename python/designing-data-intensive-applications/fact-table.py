from run_length_encoding import RunLengthEncoding

instruction = 'Enter your command:  a <offset>, q <offset>, <p> to print, or <x> to exit.\n'

encoding = RunLengthEncoding()

command = raw_input(instruction)
while command != 'x':
    parts = command.split(' ')
    if parts[0] == 'a':
        if len(parts) != 2:
            print 'The add command requires you to specify an offset!\n'
        else:
            encoding.add(int(parts[1]))
    elif parts[0] == 'p':
        print encoding
    elif parts[0] == 'q':
        if len(parts) != 2:
            print 'The query command requires you to specify an offset!\n'
        else:
            print '{}'.format(encoding.contains(int(parts[1])))
    command = raw_input(instruction)
