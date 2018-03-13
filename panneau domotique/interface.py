#!/bin/python3
#la première ligne est pour l'execution sur unix
import pygame
import datetime
from pygame.locals import *
from sys import argv
import time
import serial
import serial.tools.list_ports #module permettant d'avoir accès à tous les ports séries disponibles 


# set up the colors
BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
RED   = (255,   0,   0)
GREEN = (  0, 255,   0)
BLUE  = ( 22, 160, 133)
fond  = ( 46,  64,  83)  #couleur de fond

# déclaration des variables (-100 pour etre sur de lire)
temp = -100
pres = -100
lum  = -100

#fonction d'affichage de texte
def drawText(texte, posX, posY , color=WHITE):
	text = font.render(texte,1,color)
	fenetre.blit(text, (posX, posY))

def drawTextInBox(texte, posX, posY ,width, height, color=BLACK, fond=WHITE):
	pygame.draw.rect(fenetre, fond, pygame.Rect(posX, posY, width, height))
	drawText(texte, posX + width/2 - len(texte) * 10, posY + height/2 -5, color)

#initialisation of pygame
pygame.init()





# _____ _____ _   _ _____ _____ ____  _____
#|  ___| ____| \ | | ____|_   _|  _ \| ____|
#| |_  |  _| |  \| |  _|   | | | |_) |  _|
#|  _| | |___| |\  | |___  | | |  _ <| |___
#|_|   |_____|_| \_|_____| |_| |_| \_\_____|


modes = pygame.display.list_modes()
if not modes:
	print("no display")
	pygame.quit()
	exit()
else:
	print('Found Resolution:'+ str(modes[0]))
	largeur = modes[0][0]
	hauteur = modes[0][1]

fenetre = pygame.display.set_mode(modes[0],pygame.FULLSCREEN)


#police d'écriture
font = pygame.font.Font(None, int(hauteur/10))


# ____   ___  ____ _____   ____  _____ ____  ___ _____ 
#|  _ \ / _ \|  _ \_   _| / ___|| ____|  _ \|_ _| ____|
#| |_) | | | | |_) || |   \___ \|  _| | |_) || ||  _| 
#|  __/| |_| |  _ < | |    ___) | |___|  _ < | || |___ 
#|_|    \___/|_| \_\|_|___|____/|_____|_| \_\___|_____|
connected = []
ser = 0

while len(connected) <= 0 and ser == 0: 

	ports_series = serial.tools.list_ports.comports()
	
	for element in ports_series:
	    connected.append(element.device)
	#print("Connected COM ports: " + str(connected)) #debug
	
	if len(connected) > 0:						# on test si plusieurs ports ont été trouvée, si oui on utilise le 1er
		ser = serial.Serial(connected[0], 9600)
		ser.flushInput()						# éfface les residus de données sur le port avant qu'on ne commence 
	else:
		pygame.draw.rect(fenetre, RED, pygame.Rect(largeur/4,hauteur/4, largeur/2,hauteur/2))
		drawText("PAS DE PORT SERIE", largeur/2-100,hauteur/2-20 ,BLACK)
		time.sleep(1)
		pygame.display.flip()
	
	#on test si on demande a fermer la fenetre
	for event in pygame.event.get():
		if event.type == KEYDOWN:
			if event.key == K_q:
				pygame.quit()
				exit()


#application de la couleur de fond
fenetre.fill(fond)

#affichage des bloc de texte
drawText("Heure"      , 10       , 10)
drawText("Température", largeur/5, hauteur/10*2+10)
drawText("Humidité"   , largeur/5, hauteur/10*4+10)
drawText("Lumière"    , largeur/5, hauteur/10*6+10)
#                 _
# _ __ ___   __ _(_)_ __
#| '_ ` _ \ / _` | | '_ \
#| | | | | | (_| | | | | |
#|_| |_| |_|\__,_|_|_| |_|


continuer = True


while continuer:


	#affichage de l'heure
	heure = datetime.datetime.now().isoformat(" ")				#récupération de l'heure
	heure = str(heure)[11:][:8]									#coupage de la chaine de caractère
	
	pygame.draw.rect(fenetre, fond, pygame.Rect(100, 10, 250, 40))
	drawText(heure, 100, 10 ,WHITE)

	#affichage des variables lue sur les capteurs
	data = str(ser.readline()) 		#récupération des onnées du port série du rapberry
	data = data[2:][:-5]  			#on retire les caractère inutiles 
	#print(data) #debug
	data_matrix = data.split(',') 	#chaque donnée avant la(,) est mise dans une case du tableau
	temp = data_matrix[0] 			#récupération da la 1ère valeur du tableau
	pres = data_matrix[1]			#récupération da la 2ème valeur
	lum  = data_matrix[2]  			#récupération da la 3ème valeur

	
	drawTextInBox(str(temp) , largeur/4,hauteur/10*3 , largeur/2 , hauteur/10 , BLUE)
	drawTextInBox(str(pres) , largeur/4,hauteur/10*5 , largeur/2 , hauteur/10 , BLUE)
	drawTextInBox(str(lum ) , largeur/4,hauteur/10*7 , largeur/2 , hauteur/10 , BLUE)
	
	#on test si on demande a fermer la fenetre
	for event in pygame.event.get():
		if event.type == QUIT:
			continuer = False
		if event.type == KEYDOWN:
			if event.key == K_q:
				continuer = False
			

	#raffraichissement de l'interface
	pygame.display.flip()

ser.close() #arrêt de lecture
pygame.quit()#Ici!

