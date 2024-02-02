import sys
import os

if sys.argv[1] == "1":
    # svi fajlovi u *tom direktorijumu u kojem je prepravljac*
    l = []
    for i in os.listdir("."):
        if os.path.isfile(i):
            input_file = open(i, "r")

            Lines = input_file.readlines()

            output_file = open(i, "w")

            for line in Lines:
                if line[0] == '\t':
                    output_file.write(line[1:])
                elif line[0:3] == "===":
                    output_file.write("# " + line[3:])
                else:
                    output_file.write(line)

            input_file.close()
            output_file.close()

else:
    input_file = open(sys.argv[1], "r")

    Lines = input_file.readlines()

    output_file = open(sys.argv[2], "w")

    for line in Lines:
        if line[0] == '\t':
            output_file.write(line[1:])
        elif line[0:3] == "===":
            output_file.write("# " + line[3:])
        else:
            output_file.write(line)

    input_file.close()
    output_file.close()
