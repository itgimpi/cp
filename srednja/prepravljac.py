import sys
import os

if sys.argv[1] == "1":
    # svi fajlovi u *tom direktorijumu u kojem je prepravljac*
    l = []
    for i in os.listdir("."):
        if os.path.isfile(i) and i[len(i) - 3:len(i)] == ".md":
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
elif sys.argv[1] == "2":
    working_dir = sys.argv[2]
    os.chdir(os.path.join(os.getcwd(), working_dir))
    for i in os.listdir():
        c = 0
        s = ' '
        if i[len(i) - 3:len(i)] == ".md":
            file = open(i, "r", encoding="UTF-8")
            Lines = file.readlines()
            for j in Lines:
                c += 1
                if c == 6:
                    s = j[2:len(j)-1]
                    os.mkdir(s)
                    break          
            file.close()
            os.rename(i, os.path.join(s, i))  
        
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
