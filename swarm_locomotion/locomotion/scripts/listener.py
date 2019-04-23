#!/usr/bin/env python

import rospy

from std_msgs.msg import Float32

import time
import math
from threading import Thread
import numpy as np





radius=3.4
radconstant = (2*3.14*radius)/6000
d=18.



lengthconstant=0.01


currentrpm_A=0
currentrpm_B=0
exitflag=0

timestamp=0.05
realtheta=0

setrpm_A=0
setrpm_B=0

x=0
y=0

startx=0
starty=0


def currentpos(args):
    global x
    global y
    global exitflag
    global realtheta
    global currentrpm_A
    global currentrpm_B
    global setrpm_A
    global setrpm_B
    global startx
    global starty
    x=startx
    y=starty
    a=np.array([startx,starty])
    xaxis=np.array([1, 0])
    realtheta = math.acos(a.dot(xaxis) / ((np.linalg.norm(a)) * (np.linalg.norm(xaxis))))

    #print("Hello")
    counter =0
    while 1:
        #print(x,y)
        #currentrpm_A
        #currentrpm_B
        print(currentrpm_A,currentrpm_B)
        #print(math.degrees(realtheta))
        if currentrpm_A==0 and currentrpm_B!=0:
            realtheta=realtheta-((currentrpm_B)*2*3.14*(radius/100)*timestamp/60)/(d/100)


        else:
            if currentrpm_A!=0 and currentrpm_B==0:
                realtheta = realtheta +((currentrpm_A-currentrpm_B) * 2 * 3.14 * (radius / 100) * timestamp / 60) / (d / 100)
            else:
                x=x+math.cos(realtheta)*currentrpm_A*radconstant*100*timestamp

                y=y+math.sin(realtheta)*currentrpm_A*radconstant*100*timestamp

        if realtheta > 3.14:
            realtheta = realtheta - 2 * 3.14
        if realtheta < -3.14:
            realtheta = 2 * 3.14 + realtheta
        if exitflag==1:
            setrpm_A=0
            setrpm_B=0
            break
        time.sleep(timestamp)


def relativepos(x0, y0, x1, y1, x2, y2):
    u=y2-((y1-y0)/(x1-x0))*x2

    if u > 0:
        return 1
    else:
        return 0





def turn(x0,y0,x1,y1,x2,y2):
    a=np.array([x1-x0,y1-y0])
    b=np.array([x2-x1,y2-y1])



    t=2



    xaxis=[1,0]
    theta1 = math.acos(a.dot(xaxis) / ((np.linalg.norm(a)) * (np.linalg.norm(xaxis))))
    theta2 = math.acos(b.dot(xaxis) / ((np.linalg.norm(b)) * (np.linalg.norm(xaxis))))
    if a[1]<0:
        theta1=-theta1
    if b[1]<0:
        theta2=-theta2

    theta=theta2-theta1
    if(theta>3.14):
        theta=-(2*3.14-theta)
    rpm=(theta*d/100)*60/(t*(2*3.14*radius/100))

    rpm=abs(rpm)
    print("theta=", math.degrees(theta))

    if theta<0:
        setrpm(0,rpm,t)
        goto(x1,y1,x2,y2)

    if theta>0:
        setrpm(rpm,0,t)
        goto(x1,y1,x2,y2)

    if theta==0:
        goto(x1,y1,x2,y2)




def goto(x1,y1,x2,y2):

    leftrpm=50

    rightrpm=50

    vel=leftrpm*radconstant
    print(np.linalg.norm([x2-x1,y2-y1]))
    t=np.linalg.norm([x2-x1,y2-y1])/(vel*100)

    setrpm(leftrpm,rightrpm,t)





def setrpm(leftrpm,rightrpm,t):

    global setrpm_A
    global setrpm_B
    print("right rpm=",(rightrpm),"left rpm=",leftrpm, "time=",t)
    setrpm_A=leftrpm
    setrpm_B=rightrpm
    time.sleep(t)


def readdata():
    f = open("./example.txt","r")

    myList =[]

    for line in f:
        myList.append(line)

    finallist=list(reversed(myList))


    qa=[]

    for x in finallist:
        x=x[1:]
        qa=qa+[x]

    re=[]
    for x in qa:
        x=str(x).replace("-",",")
        re=re+[str(str(x).replace("-",",")).replace("\n","")]

    ans=[]
    for x in re:
        i=x.find(',')
        ans=ans+[(x[:i],x[i+1:])]

    return ans


def init(args):
    global startx,starty,x,y,exitflag
    #points=readdata()

    points=[(45,45),(0,90),(45,135),(0,150),(45,45)]

    #points=[(2,90),(100,100),(120,90)]

    [startx,starty]=points[0]
    [startx,starty]=[int(startx),int(starty)]

    thread = Thread(target = currentpos, args = (10,))
    thread.start()


    #print("hello")
    #turn(90,90,120,120,120,90)


    print(points)
    [j, k] = [0, 0]

    for i in range(len(points)):

        if i == 0:
            [j, k] = [0, 0]
        else:
            [j, k] = points[i - 1]
            [j, l] = [int(j), int(k)]

        print("##")

        print(x, y)

        j = int(j)

        k = int(k)

        [l, m] = points[i]

        l = int(l)

        m = int(m)

        if i != len(points) - 1:
            [a, b] = points[i + 1]
            a = int(a)
            b = int(b)
            turn(j, k, l, m, a, b)
            #turn(l, m, x ,y, a, b)

    print("hello")

    exitflag = 1

    #turn(90,90,120,120,90,120)

    print(x, y)
    thread.join()





def callback1(data):
    global currentrpm_A
    currentrpm_A = data.data
    print(currentrpm_A)
def callback2(data):
    global currentrpm_B
    currentrpm_B = data.data

#def func():
#    global set_rpmA
#    global set_rpmB
#    set_rpmA = 100
#    set_rpmB = 100

def listener():
    global  setrpm_A,setrpm_B
    rospy.init_node('locomotion', anonymous=True)

    rospy.Subscriber("bot1/current_rpmA", Float32, callback1)
    rospy.Subscriber("bot1/current_rpmB", Float32, callback2)
    pub1 = rospy.Publisher('bot1/set_rpmA', Float32, queue_size=10)
    pub2 = rospy.Publisher('bot1/set_rpmB', Float32, queue_size=10)
    rate = rospy.Rate(20)

    while not rospy.is_shutdown():	
        pub1.publish(setrpm_A)
        pub2.publish(setrpm_B)
        rate.sleep()

    rospy.spin()


if __name__ == '__main__':

    thread = Thread(target = init, args = (10,))
    thread.start()
    listener()
    thread.join()
	
