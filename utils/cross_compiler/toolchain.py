import os
import subprocess
from subprocess import call

print("You need Python Interpreter (python V2.7 or above) , and git for this installaton");

if(os.path.isdir("cross/")) :
	print("Seems Like You Already Have The Cross Compiler");
else:
	print("Installing the CROSS COMPILER (x86,x86_64,MIPS,ARMV7)");
	os.system("git clone https://github.com/rm-hull/barebones-toolchain cross");