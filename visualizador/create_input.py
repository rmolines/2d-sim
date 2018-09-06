import random

XB = 7
YB = 7
FW = 10000
FH = 10000
RADIUS = 130
balls = []



f = open("input", "w+")

f.write("%d %d %d\n" % (FW, FH, XB*YB))
f.write("1 1 1\n")


counter = 0
for i in range(XB):
    for j in range(YB):
        id_ = counter
        x = i*(FW/XB)+RADIUS+20
        y = j*(FH/YB)+RADIUS
        radius = RADIUS
        vx = float(random.randint(-10,10))/10.0
        vy = float(random.randint(-10,10))/10.0
        mass = random.randint(1, 100)/10
        f.write("%f %f %f %f %f %f %f\n" % (id_, radius, mass, x, y, vx, vy))
        counter += 1

