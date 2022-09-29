import os
import sys


class CFile:
    def __init__(self, lines):
        self.includes = []
        self.lines = []
        for line in lines:
            if line.startswith('#include'):
                self.includes.append(line)
            else:
                self.lines.append(line)
       

class Main:
    def __init__(self):
        self.included_files = [CFile(open('src/'+file, 'r').readlines()) for file in os.listdir('src') if file.endswith('.c')]
        self.main_file = open('main.c', 'r').readlines()

        self.includes = []
        self.lines = []
        for line in self.main_file:
            if line.startswith('#include'):
                self.includes.append(line)
            else:
                self.lines.append(line)
        
        for i in [file.includes for file in self.included_files]:
            self.includes.extend(i)
        self.all_includes = list(set(self.includes))
        self.body_code = []
        for i in [file.lines for file in self.included_files]:
            self.body_code.extend(i)
        self.body_code.extend(self.lines)
    
    def write_main(self):
        with open('combined_main.c', 'w') as f:
            f.writelines(self.all_includes)
            f.writelines(self.body_code)


if len(sys.argv) == 2 and sys.argv[1] == 'combine':
    main = Main()
    main.write_main()
    quit(0)
else:
    print("Please provide a valid argument")
    quit(1)


