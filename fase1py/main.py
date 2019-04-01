import sys
from math import *

class Forma:
	def __init__(self, iD, x, y):
		self.iD = iD
		self.x = x
		self.y = y

	def getTipo(self):
		return type(self).__name__

class Circulo(Forma):
	def __init__(self, iD, x, y, raio, corB, corD):
		super().__init__(id, x, y)
		self.raio = raio
		self.corB = corB
		self.corD = corD

	def getSVG(self):
		return "<circle cx=\"{}\" cy=\"{}\" r=\"{}\" stroke=\"{}\" fill=\"{}\" />\n".format(self.x, self.y, self.raio, self.corB, self.corD)

class Retangulo(Forma):
	def __init__(self, iD, x, y, h, w, corB, corD):
		super().__init__(iD, x, y)
		self.h = h
		self.w = w
		self.corB = corB
		self.corD = corD

	def getSVG(self):
		return "<rect x=\"{}\" y=\"{}\" width=\"{}\" height=\"{}\" stroke=\"{}\" fill=\"{}\" />\n".format(self.x, self.x, self.w, self.h, self.corB, self.corD)

class Texto(Forma):
	def __init__(self, iD, x, y, texto):
		super().__init__(iD, x, y)
		self.texto = texto

	def getSVG(self):
		return "<text x=\"{}\" y=\"{}\">{}</text>".format(self.x, self.y, self.texto)



def lerArgumentos(argumentos):
	global nomeArquivoEntrada, dirEntrada, nomeArquivoConsulta, dirSaida
	for i in range(1, len(argumentos)):
		if argumentos[i] == "-e":
			if i+1 >= len(argumentos):
				print("'{}' requer argumento.".format(argumentos[i]))
				return False

			dirEntrada = argumentos[i+1]
		elif argumentos[i] == "-f":
			if i+1 >= len(argumentos):
				print("'{}' requer argumento.".format(argumentos[i]))
				return False

			nomeArquivoEntrada = argumentos[i+1]
		elif argumentos[i] == "-q":
			if i+1 >= len(argumentos):
				print("'{}' requer argumento.".format(argumentos[i]))
				return False

			nomeArquivoConsulta = argumentos[i+1]
		elif argumentos[i] == "-o":
			if i+1 >= len(argumentos):
				print("'{}' requer argumento.".format(argumentos[i]))
				return False

			dirSaida = argumentos[i+1]

	if nomeArquivoEntrada is None or dirSaida is None:
		return False
	return True

def tratarDiretorio(diretorio, nomeArquivo):
	if diretorio is None:
		return nomeArquivo
	elif diretorio[len(diretorio)-1] == '/':
		return diretorio+nomeArquivo
	return diretorio+'/'+nomeArquivo

def abrirArquivo(dirAbertura, nomeArquivo, formaAbertura):
	try:
		f = open(tratarDiretorio(dirAbertura, nomeArquivo), formaAbertura)
		return f
	except IOError as e:
		print("Falha na abertura do arquivo '{}': {}".format(nomeArquivo, e))
		return None

def obterSemExtensao(arquivo):
	return arquivo[:arquivo.find('.')]

def adicionarExtensao(arquivo, extensao):
	return arquivo+'.'+extensao;

def concatenarNomes(nome1, nome2):
	return nome1+"-"+nome2

def processarArquivoEntrada(arquivoEntrada):
	global dicDados
	
	indexText = -1
	dados = arquivoEntrada.readlines()
	for linha in dados:
		comando = linha.split()[0]
		if comando == 'c':
			iD = linha.split()[1]
			raio = float(linha.split()[2])
			x = float(linha.split()[3])
			y = float(linha.split()[4])
			corB = linha.split()[5]
			corD = linha.split()[6]

			circ = Circulo(iD, x, y, raio, corB, corD)
			dicDados[iD] = circ

		elif comando == 'r':
			iD = linha.split()[1]
			w = float(linha.split()[2])
			h = float(linha.split()[3])
			x = float(linha.split()[4])
			y = float(linha.split()[5])
			corB = linha.split()[6]
			corD = linha.split()[7]


			ret = Retangulo(iD, x, y, h, w, corB, corD)
			dicDados[iD] = ret

		elif comando == 't':
			iD = indexText
			x = float(linha.split()[1])
			y = float(linha.split()[2])
			texto = linha.split()[3]

			text = Texto(iD, x, y, texto)
			dicDados[iD] = text
			indexText-=1

def escreverPontoInterno(arquivo, forma, x, y, interno):
	pontoX, pontoY = centroMassa(forma)

	if(interno):
		arquivo.write("<circle cx=\"{}\" cy=\"{}\" r=\"1\" stroke=\"green\" fill=\"green\" />\n".format(x, y))
		arquivo.write("<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"green\" />\n".format(pontoX, pontoY, x, y))
	else:
		arquivo.write("<circle cx=\"{}\" cy=\"{}\" r=\"1\" stroke=\"red\" fill=\"red\" />\n".format(x, y))
		arquivo.write("<line x1=\"{}\" y1=\"{}\" x2=\"{}\" y2=\"{}\" stroke=\"red\" />\n".format(pontoX, pontoY, x, y))

def escreverRetaCentros(arquivo, forma1, forma2):
	forma1X, forma1Y = centroMassa(forma1)
	forma2X, forma2Y = centroMassa(forma2)

	distancia = distCentroMassa(forma1, forma2)

	posX = (forma1X + forma2X)/2
	posY = (forma1Y + forma2Y)/2

	arquivo.write("<line x1=\"{}\" y1=\"{}\" x2=\"{}\" y2=\"{}\" stroke=\"black\" />\n".format(forma1X, forma1Y, forma2X, forma2Y))
	arquivo.write("<text x=\"{}\" y=\"{}\">{}</text>\n".format(posX, posY, distancia))


def retanguloDelimitador(arquivo, forma1, forma2, colidem):
	xMin = xMax = yMin = yMax = largura = altura = 0

	if forma1.getTipo() == 'Circulo' and forma2.getTipo() == 'Circulo':
		xMin = forma1.x - forma1.raio if forma1.x - forma1.raio < forma2.x - forma2.raio else forma2.x - forma2.raio 
		yMin = forma1.y - forma1.raio if forma1.y - forma1.raio < forma2.y - forma2.raio else forma2.y - forma2.raio
		xMax = forma1.x + forma1.raio if forma1.x + forma1.raio > forma2.x + forma2.raio else forma2.x + forma2.raio 
		yMax = forma1.y + forma1.raio if forma1.y + forma1.raio > forma2.y + forma2.raio else forma2.y + forma2.raio

	elif forma1.getTipo() == 'Retangulo' and forma2.getTipo() == 'Retangulo':
		xMin = forma1.x if forma1.x < forma2.x else forma2.x
		yMin = forma1.y if forma1.y < forma2.y else forma2.y
		xMax = forma1.x + forma1.w if forma1.x + forma1.w > forma2.x + forma2.w else forma2.x + forma2.w 
		yMax = forma1.y + forma1.h if forma1.y + forma1.h > forma2.y + forma2.h else forma2.y + forma2.h

	else:
		#Forçar a ser forma1-> Ciruclo e forma2->Retangulo
		if forma1.getTipo() == 'Retangulo' and forma2.getTipo() == 'Circulo':
			forma3 = forma1 
			forma1 = forma2
			forma2 = forma3

		xMin = forma1.x - forma1.raio if forma1.x - forma1.raio < forma2.x else forma2.x
		yMin = forma1.y - forma1.raio if forma1.y - forma1.raio < forma2.y else forma2.y
		xMax = forma1.x + forma1.raio if forma1.x + forma1.raio > forma2.x + forma2.w else forma2.x + forma2.w
		yMax = forma1.y + forma1.raio if forma1.y + forma1.raio > forma2.y + forma2.h else forma2.y + forma2.h
		

	largura = xMax - xMin
	altura = yMax - yMin


	if colidem:
		arquivo.write("<rect x=\"{}\" y=\"{}\" width=\"{}\" height=\"{}\" stroke=\"black\" fill-opacity=\"0\" />\n".format(xMin, yMin, largura, altura))
	else:
		arquivo.write("<rect x=\"{}\" y=\"{}\" width=\"{}\" height=\"{}\" stroke=\"black\" fill-opacity=\"0\" stroke-dasharray=\"5\" />\n".format(xMin, yMin, largura, altura))


def processarArquivoConsulta(arquivoConsulta, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida):
	global dicDados

	nomeArquivoEntrada = obterSemExtensao(nomeArquivoEntrada)
	nomeArquivoConsulta = obterSemExtensao(nomeArquivoConsulta)
	nomeArqSaida = concatenarNomes(nomeArquivoEntrada, nomeArquivoConsulta)

	arquivoSVG = abrirArquivo(dirSaida, adicionarExtensao(nomeArqSaida, "svg"), "w")
	arquivoTxt = abrirArquivo(dirSaida, adicionarExtensao(nomeArqSaida, "txt"), "w")

	arquivoSVG.write("<svg> \n")
	for forma in dicDados.values():
		arquivoSVG.write(forma.getSVG())


	dados = arquivoConsulta.readlines()

	for linha in dados:
		comando = linha.split()[0]
		if comando == "o?":
			arquivoTxt.write(linha)

			j = linha.split()[1]
			k = linha.split()[2]
			forma1 = dicDados[j]
			forma2 = dicDados[k]

			if(formasSobrepoem(forma1, forma2)):
				arquivoTxt.write("SIM\n\n")
				retanguloDelimitador(arquivoSVG, forma1, forma2, True)
			else:	
				arquivoTxt.write("NAO\n\n")
				retanguloDelimitador(arquivoSVG, forma1, forma2, False)

		elif comando == "i?":
			arquivoTxt.write(linha)

			j = linha.split()[1]
			x = float(linha.split()[2])
			y = float(linha.split()[3])
			forma = dicDados[j]

			if(pontoInternoForma(forma, x, y)):
				arquivoTxt.write("SIM\n\n")
				escreverPontoInterno(arquivoSVG, forma, x, y, True)
			else:	
				arquivoTxt.write("NAO\n\n")
				escreverPontoInterno(arquivoSVG, forma, x, y, False)

		elif comando == "d?":
			arquivoTxt.write(linha)

			j = linha.split()[1]
			k = linha.split()[2]
			forma1 = dicDados[j]
			forma2 = dicDados[k]

			arquivoTxt.write(str(distCentroMassa(forma1, forma2))+"\n\n")
			escreverRetaCentros(arquivoSVG, forma1, forma2)

		elif comando == "bb":

			sufixo = linha.split()[1]
			cor = linha.split()[2]

			nomeSvgBB = concatenarNomes(nomeArqSaida, sufixo)
			arqSvgBB = abrirArquivo(dirSaida,adicionarExtensao(nomeSvgBB, "svg"), "w")
			arqSvgBB.write("<svg>\n")
			if arqSvgBB is None:
				sys.exit()

			for forma in dicDados.values():
				if forma.getTipo() == 'Circulo':
					arqSvgBB.write(forma.getSVG())

					# Retangulo q delimita a forma
					minX = forma.x - forma.raio
					minY = forma.y - forma.raio
					lado = 2*forma.raio

					arqSvgBB.write("<rect x=\"{}\" y=\"{}\" width=\"{}\" height=\"{}\" stroke=\"{}\" fill-opacity=\"0\" />\n".format(minX, minY, lado, lado, cor))

				elif forma.getTipo() == 'Retangulo':
					arqSvgBB.write(forma.getSVG())

					# Elipse dentro do retangulo
					posX, posY = centroMassa(forma)

					arqSvgBB.write("<ellipse cx=\"{}\" cy=\"{}\" rx=\"{}\" ry=\"{}\" stroke=\"{}\" fill-opacity=\"0\" />\n".format(posX, posY, forma.w/2, forma.h/2, cor))

			arqSvgBB.write("</svg>")
			arqSvgBB.close()

	
	arquivoSVG.write("</svg>")
	arquivoSVG.close()
	arquivoTxt.close()

def distancia(x1, y1, x2, y2):
	return sqrt((x1-x2)**2 + (y1-y2)**2)

def clamp(num, inicio, fim):
	x = inicio if num < inicio else num
	x = fim if num > fim else x
	return x

def formasSobrepoem(a, b):
	if a.getTipo() == 'Circulo' and b.getTipo() == 'Circulo':
		return distancia(a.x, a.y, b.x, b.y) < a.raio + b.raio
	elif a.getTipo == 'Retangulo' and b.getTipo() == 'Retangulo':
		return (a.x < b.x + b.w) and (a.x + a.w > b.x) and (a.y < b.y + b.h) and (a.y + a.h > b.y)
	else:
		#Forçar a ser a-> Ciruclo e b->Retangulo
		if a.getTipo() == 'Retangulo' and b.getTipo() == 'Circulo':
			c = a 
			a = b 
			b = c

		xProx = clamp(a.x, b.x, b.x+b.w)
		yProx = clamp(a.y, b.y, b.y+b.h)

		return distancia(a.x, a.y, xProx, yProx) < a.raio

def pontoInternoForma(forma, x, y):
	if forma.getTipo() == 'Circulo':
		return distancia(forma.x, forma.y, x, y) < forma.raio
	elif forma.getTipo() == 'Retangulo':
		return x >= forma.x and x <= forma.x+forma.w and y >= forma.y and y <= forma.y+forma.h 

def centroMassa(forma):
	if forma.getTipo() == 'Circulo':
		return forma.x, forma.y
	elif forma.getTipo() == 'Retangulo':
		return forma.x + forma.w/2, forma.y + forma.h/2

def distCentroMassa(forma1, forma2):
	forma1X, forma1Y = centroMassa(forma1)
	forma2X, forma2Y = centroMassa(forma2)
	return distancia(forma1X, forma1Y, forma2X, forma2Y)



#globais aqui
nomeArquivoEntrada = dirEntrada = nomeArquivoConsulta = dirSaida = None
dicDados = {}

def main():
	certo = lerArgumentos(sys.argv)
	if not certo:
		sys.exit("Falha na leitura dos argumentos")

	arquivoEntrada = abrirArquivo(dirEntrada, nomeArquivoEntrada, "r")
	if arquivoEntrada is None:
		sys.exit()
	processarArquivoEntrada(arquivoEntrada)
	arquivoEntrada.close()

	nomeArqSaida = obterSemExtensao(nomeArquivoEntrada)
	arquivoSaidaSVG = abrirArquivo(dirSaida, adicionarExtensao(nomeArqSaida, "svg"), "w")

	arquivoSaidaSVG.write("<svg>\n")
	for forma in dicDados.values():
		arquivoSaidaSVG.write(forma.getSVG())
	arquivoSaidaSVG.write("</svg>")
	arquivoSaidaSVG.close()

	print(nomeArquivoConsulta)
	if nomeArquivoConsulta is not None:
		arquivoConsulta = abrirArquivo(dirEntrada, nomeArquivoConsulta, "r")
		if arquivoConsulta is None:
			sys.exit()
		processarArquivoConsulta(arquivoConsulta, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida)


if __name__ == '__main__':
	main()