import random
import os
import argparse
import sys

XB = 2
YB = 1
FW = 10000
FH = 10000
RADIUS = 130
balls = []
field = [[False]*FH]*FW



def rand_balls():
    XB = int(input())

    f = open("input", "w+")

    f.write("%d %d %d\n" % (FW, FH, XB*YB))

    x_pos = []
    y_pos = []

    mu = random.randint(200, 500)
    f.write("%f 1 1\n" % (50))

    for i in range(XB):
        radius = random.randint(100, 500)
        placed = False
        while (not placed):
            collides = False
            x = random.randint(radius, FW-radius)
            y = random.randint(radius, FW-radius)
            for i in range(x-radius, x+radius):
                for j in range(y-radius, y+radius):
                    if (field[i][j]):
                        collides = True
            
            if(not collides):
                for i in range(x-radius, x+radius):
                    for j in range(y-radius, y+radius):
                        field[i][j] = True
                placed = True 
                
        vx = float(random.randint(-5000,5000))
        vy = float(random.randint(-5000,5000))
        mass = random.randint(1, 100)/10
        f.write("%f %f %f %f %f %f %f\n" % (i, radius, mass, x, y, vx, vy))

def go_for_numbers():
    XB = int((sys.argv)[2])

    f = open("input", "w+")

    f.write("%d %d %d\n" % (FW, FH, XB*XB))


    mu = random.randint(200, 500)
    f.write("%f 1 1\n" % (50))

    counter = 0;
    for i in range(XB):
        for j in range(XB):
            radius = (FW/XB)*0.2;
            x = i*(FW/XB)+radius;
            y = j*(FH/XB)+radius;
            vx = float(random.randint(-4000,4000))
            vy = float(random.randint(-4000,4000))
            mass = random.randint(1, 100)/10
            f.write("%f %f %f %f %f %f %f\n" % (counter, radius, mass, x, y, vx, vy))
            counter+=1


def test_balls():
    f = open("input", "w+")
    radius = 200
    f.write("%d %d %d\n" % (FW, FH, XB*YB))

    f.write("%f 1 1\n" % (0))
    x = FW/3;
    y = FH/2;
    vx = 1000;
    vy = 0;
    mass = 1;

    f.write("%f %f %f %f %f %f %f\n" % (0, radius, mass, x, y, vx, vy))

    x = FW/3*2;
    y = FH/2;
    vx = -1000;
    vy = 0;
    mass = 1;

    f.write("%f %f %f %f %f %f %f\n" % (1, radius, mass, x, y, vx, vy))


def main():
    if ((sys.argv)[1] == "-test"):
        test_balls()
    elif ((sys.argv)[1] == "-n"):
        go_for_numbers()
    else:
        rand_balls()

if __name__ == "__main__":
    main()
    print("Concluido")

# os.system("make")
# os.system("./visualizador < 2")