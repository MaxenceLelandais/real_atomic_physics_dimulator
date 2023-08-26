import cv2
import numpy as np
import math
import time

# Créer une image noire
width, height = 800, 600
image = np.zeros((height, width, 3), dtype=np.uint8)


ratio = width/height
angle = 170*0.0174533
near = 0
far = 1
pasX = 0
pasY = 0
pasZ = 1
angle_x, angle_y, angle_z = 0,0,0


fpsSum= 0
nbrLoop = 0
temps = 0
tempsSum = 0

n = 1
pointsCloud = np.random.rand(n,3)
pointsCloud-=0.5
pointsCloud*=2

ww = width/2
hh = height/2

while True:
    
    if tempsSum>=10 or nbrLoop>100:
        n*=10
        
        pointsCloud = np.random.rand(n,3)
        pointsCloud-=0.5
        pointsCloud*=2
        
        print("nbr particules : ", n, " ,fps moyen : ", 1/(tempsSum/nbrLoop))
        tempsSum= 0
        nbrLoop = 0
    

    # Effacer l'image
    image.fill(0)
    if angle<0:
        angle = 2*3.1415
    if angle>3.1415:
        angle = 0.1
    
    a = 1/(ratio*math.tan(angle/2))
    b = 1/(math.tan(angle/2))
    d = (-near*far)/(far-near)
    
    c_x = np.cos(angle_x)
    s_x = np.sin(angle_x)
    c_y = np.cos(angle_y)
    s_y = np.sin(angle_y)
    c_z = np.cos(angle_z)
    s_z = np.sin(angle_z)
    
    
    l1 = c_y * c_z * a * ww
    l2 = -(c_x * s_z + s_x * s_y * c_z) * a * ww
    l3 = (s_x * s_z - c_x * s_y * c_z) * a * ww
    l4 = c_y * s_z * b * hh
    l5 = (c_x * c_z - s_x * s_y * s_z) * b * hh
    l6 = -(s_x * c_z + c_x * s_y * s_z) * b * hh
    l7 = -s_y
    l8 = s_x * c_y
    l9 = c_x * c_y
    chrono = time.time()
    
    for point in pointsCloud:
        z = l7 * point[0] + l8 * point[1] + l9 * point[2] + pasZ

        if z>0:        
            X = (l1 * point[0] + l2 * point[1] + l3 * point[2] + pasX)/z+ww
            
            if 0<=X:
                if X<width:
                    Y = (l4 * point[0] + l5 * point[1] + l6 * point[2] + pasY)/z+hh
                    
                    if 0<=Y:
                        if Y<height:
                            image[int(Y)][int(X)] = 255
                            
                    
    tempsSum += time.time()-chrono+0.00000001
    print(tempsSum, end="\r")
    
    nbrLoop+=1
    # Afficher l'image
    cv2.imshow('3D Rendering', image)

    # Gérer les événements clavier
    key = cv2.waitKey(1)
    if key == ord('z'):
        pasY +=0.1
    if key == ord('s'):
        pasY-=0.1
    if key == ord('q'):
        pasX+=0.1
    if key == ord('d'):
        pasX-=0.1
        
    if key == ord('+'):
        pasZ+=0.1
    if key == ord('-'):
        pasZ-=0.1
    if key == ord('²'):
        break
    
    if key == ord('a'):
        angle_x +=0.1
    if key == ord('e'):
        angle_x-=0.1
    if key == ord('w'):
        angle_y+=0.1
    if key == ord('x'):
        angle_y-=0.1
    if key == ord('c'):
        angle_z +=0.1
    if key == ord('v'):
        angle_z-=0.1


cv2.destroyAllWindows()
