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
	os.mkdir("saida/saidaGerada")

	for nameFiles in files:

		nameDir = nameFiles[:-4]
		print("Executando {}...".format(nameFiles))
		os.mkdir("saida/saidaGerada/{}".format(nameDir))
		time.sleep(0.5)

		try:
			for filename in os.listdir("{}/{}".format(dirInput, nameDir)):
				print(filename)
				os.system("cd {} && valgrind ./siguel -e ../{} -f {} -q {}/{} -o ../saida/saidaGerada/{}".format(dirCode, dirInput, nameFiles, nameDir, filename, nameDir))
		except Exception as e:
			os.rmdir("saida/saidaGerada/{}".format(nameDir))
			print(e)
		print()
	break
