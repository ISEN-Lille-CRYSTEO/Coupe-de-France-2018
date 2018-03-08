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
BLUE  = (22, 160, 133)
fond  = ( 46, 64, 83)  #couleur de fond

# déclaration des variables (-100 pour etre sur de lire)
temp = -100
pres = -100
lum  = -100

#fonction d'affichage de texte
def drawText(texte, posX, posY , color=WHITE):
	text = font.render(texte,1,color)
	fenetre.blit(text, (posX, posY))


#initialisation of pygame
pygame.init()


# ____   ___  ____ _____   ____  _____ ____  ___ _____ ____
#|  _ \ / _ \|  _ \_   _| / ___|| ____|  _ \|_ _| ____/ ___|
#| |_) | | | | |_) || |   \___ \|  _| | |_) || ||  _| \___ \
#|  __/| |_| |  _ < | |    ___) | |___|  _ < | || |___ ___) |
#|_|    \___/|_| \_\|_|___|____/|_____|_| \_\___|_____|____/

ports_series = serial.tools.list_ports.comports()
connected = []
for element in ports_series:
    connected.append(element.device)
#debug
#print("Connected COM ports: " + str(connected))

if len(connected) > 0:						# on test si plusieurs ports ont été trouvée, si oui on utilise le 1er
	ser = serial.Serial(connected[0], 9600)
	ser.flushInput()						# éfface les residus de données sur le port avant qu'on ne commence 
else:
	print("pas de port serie")
	pygame.quit()
	exit()



# _____ _____ _   _ _____ _____ ____  _____
#|  ___| ____| \ | | ____|_   _|  _ \| ____|
#| |_  |  _| |  \| |  _|   | | | |_) |  _|
#|  _| | |___| |\  | |___  | | |  _ <| |___
#|_|   |_____|_| \_|_____| |_| |_| \_\_____|


if(len(argv) >= 3):
	largeur = int(argv[1])
	hauteur = int(argv[2])
else:
	largeur = 640
	hauteur = 480


fenetre = pygame.display.set_mode((largeur,hauteur), RESIZABLE)


#police d'écriture
font = pygame.font.Font(None, int(hauteur/20))


#définition de la couleur de fond
fenetre.fill(fond)


#affichage des bloc de texte
drawText("Heure"      , 10       , 10)
drawText("Température", largeur/5, hauteur/10*2+10)
drawText("Humidité"   , largeur/5, hauteur/10*4+10)
drawText("Lumière"    , largeur/5, hauteur/10*6+10)


#affichage des block blanc
pygame.draw.rect(fenetre,WHITE , pygame.Rect(largeur/4,hauteur/10*3 , largeur/2 , hauteur/10))
pygame.draw.rect(fenetre,WHITE , pygame.Rect(largeur/4,hauteur/10*5 , largeur/2 , hauteur/10))
pygame.draw.rect(fenetre,WHITE , pygame.Rect(largeur/4,hauteur/10*7 , largeur/2 , hauteur/10))


#                 _
# _ __ ___   __ _(_)_ __
#| '_ ` _ \ / _` | | '_ \
#| | | | | | (_| | | | | |
#|_| |_| |_|\__,_|_|_| |_|


continuer = True


while continuer:


	#affichage de l'heure
	pygame.draw.rect(fenetre,fond, pygame.Rect(100,10,250,50))  #effacage de l'ancienne heure
	heure = datetime.datetime.now().isoformat(" ")				#récupération de l'heure
	heure = str(heure)[11:][:8]									#coupage de la chaine de caractère
	drawText(heure,100,10)

	#affichage des variables lue sur les capteurs
	data = str(ser.readline()) #récupération des onnées du port série du rapberry
	data = data[2:][:-5]  #on retire les caractère inutiles 
	print(data)
	data_matrix = data.split(',') #chaque donnée avant la(,) est mise dans une case du tableau
	temp= data_matrix[0] #récupération da la 1ère valeur du tableau
	pres = data_matrix[1] #- || - 2ème valeur
	lum = data_matrix[2]  #- || - 3ème valeur
        
	drawText(str(temp) , largeur/4*1.5 , hauteur/10*3+10 , BLUE)
	drawText(str(pres) , largeur/4*1.5 , hauteur/10*5+10 , BLUE)
	drawText(str(lum ) , largeur/4*1.5 , hauteur/10*7+10 , BLUE)
	
	#on test si on demande a fermer la fenetre
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			continuer = False
	
	#raffraichissement de l'interface
	pygame.display.flip()

ser.close() #arrêt de lecture
pygame.quit()#Ici!

