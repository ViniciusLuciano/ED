'''
Forma dos diretorios:
-> local
  -> pastaCodigo
     -> makefile
  -> pastaTestes
  -> script.py

Forma de uso:
python3 script.py pastaCodigo pastaTestes
'''

import os
import time
import sys
import shutil

dirCode = sys.argv[1]
dirInput = sys.argv[2]

os.system("cd {} && make siguel".format(dirCode))

for __, __, files in os.walk(dirInput):

	try:
		os.mkdir("saida")
	except:
		shutil.rmtree("saida")
		os.mkdir("saida")
	#os.mkdir("saida")

	for nameFiles in files:
		if nameFiles != "bairro.geo":
			print(nameFiles)
			os.system("cd {} && ./siguel -e ../{} -f bairro.geo -q {} -o ../saida/".format(dirCode, dirInput, nameFiles))
	break
