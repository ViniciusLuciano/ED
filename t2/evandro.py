
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
				os.system("cd {} && ./siguel -e ../{} -f {} -q {}/{} -o ../saida/saidaGerada/{}".format(dirCode, dirInput, nameFiles, nameDir, filename, nameDir))
		except Exception as e:
			os.rmdir("saida/saidaGerada/{}".format(nameDir))
			print(e)
		print()
	break


'''
def isNumber(digito):
	if ord(digito) > 47 and ord(digito) < 58:
		return True
	return False

def calcular(v1, v2, o):
	if o == '+':
		return v1+v2
	elif o == '-':
		return v1-v2
	elif o == '*':
		return v1*v2
	elif o == '/':
		return v1//v2

def validar(lista):
	if not isNumber(lista[-1]) or not isNumber(lista[-2]):
		return False
	for i in range(len(lista) - 2):
		if (i % 2 == 0 and isNumber(lista[i])) or (i % 2 != 0 and not isNumber(lista[i])):
			return False
	return True


while True:
	try:
		operandos = []
		numeros = []
		dados = list(map(str, input().split()))

		if not validar(dados):
			print("Invalid expression.")
		else:
			for dado in dados:
				if isNumber(dado):
					numeros.append(int(dado))
				else:
					operandos.append(dado)


			for i in range(len(operandos)):
				v1 = numeros.pop()
				v2 = numeros.pop()
				o = operandos.pop()	

				if v2 == 0 and o == '/':
					print("Division by zero.")
					continue

				valor = calcular(v1, v2, o)
				numeros.append(valor)

			if len(numeros) == 1:
				print("The answer is {}.".format(numeros[0]))
	except EOFError:
		break

'''

