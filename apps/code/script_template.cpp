#include "script_template.h"

namespace Code {

<<<<<<< HEAD
constexpr ScriptTemplate emptyScriptTemplate(".py", "\x01");
=======
constexpr ScriptTemplate emptyScriptTemplate(".py", "\x01" R"(
)");
>>>>>>> 03b42069898cdbfb44f622c0b41164a55407cc90

/*
constexpr ScriptTemplate squaresScriptTemplate("squares.py", "\x01" R"(from math import *
from turtle import *
def squares(angle=0.5):
  reset()
  L=330
  speed(10)
  penup()
  goto(-L/2,-L/2)
  pendown()
  for i in range(660):
    forward(L)
    left(90+angle)
    L=L-L*sin(angle*pi/180)
  hideturtle())");

constexpr ScriptTemplate mandelbrotScriptTemplate("mandelbrot.py", "\x01" R"(# This script draws a Mandelbrot fractal set
# N_iteration: degree of precision
import kandinsky
def mandelbrot(N_iteration):
  for x in range(320):
    for y in range(222):
# Compute the mandelbrot sequence for the point c = (c_r, c_i) with start value z = (z_r, z_i)
      z = complex(0,0)
# Rescale to fit the drawing screen 320x222
      c = complex(3.5*x/319-2.5, -2.5*y/221+1.25)
      i = 0
      while (i < N_iteration) and abs(z) < 2:
        i = i + 1
        z = z*z+c
# Choose the color of the dot from the Mandelbrot sequence
      rgb = int(255*i/N_iteration)
      col = kandinsky.color(int(rgb),int(rgb*0.75),int(rgb*0.25))
# Draw a pixel colored in 'col' at position (x,y)
      kandinsky.set_pixel(x,y,col))");

constexpr ScriptTemplate polynomialScriptTemplate("polynomial.py", "\x01" R"(from math import *
# roots(a,b,c) computes the solutions of the equation a*x**2+b*x+c=0
def roots(a,b,c):
  delta = b*b-4*a*c
  if delta == 0:
    return -b/(2*a)
  elif delta > 0:
    x_1 = (-b-sqrt(delta))/(2*a)
    x_2 = (-b+sqrt(delta))/(2*a)
    return x_1, x_2
  else:
    return None)");
*/
<<<<<<< HEAD
=======

constexpr ScriptTemplate td_math_v3ScripTemplate("td_math_v3.py", "\x01" R"(class Vec:
  def __init__(v,x,y,z=None):
    v.x=x
    v.y=y
    if z!=None:
      v.z=z

  def add(v,ot):
    return Vec(v.x+ot.x,v.y+ot.y,v.z+ot.z)

  def mul(v,r):
    return Vec(r*v.x,r*v.y,r*v.z)

  def rot(v,n,cost,sint):
    crossed=v.cross(n)
    dotted=n.dot(v)
    return Vec((1-cost)*dotted*n.x+cost*v.x+sint*crossed.x,(1-cost)*dotted*n.y+cost*v.y+sint*crossed.y,(1-cost)*dotted*n.z+cost*v.z+sint*crossed.z)

  def rot_perp(v,n,cost,sint):
    crossed=v.cross(n)
    return Vec(cost*v.x+sint*crossed.x,cost*v.y+sint*crossed.y,cost*v.z+sint*crossed.z)

  def dot(v,w):
    return v.x*w.x+v.y*w.y+v.z*w.z

  def cross(v,w):
    #return Vec(w.y*v.z-v.y*w.z,v.x*w.z-w.x*v.z,w.x*v.y-v.x*w.y)
    return Vec(v.y*w.z-w.y*v.z,w.x*v.z-v.x*w.z,v.x*w.y-w.x*v.y)

  def chco(v,c,i,j,k):#change_coordinates
    p=Vec(v.x-c.x,v.y-c.y,v.z-c.z)
    return Vec(p.x*i.x+p.y*i.y+p.z*i.z,p.x*j.x+p.y*j.y+p.z*j.z,p.x*k.x+p.y*k.y+p.z*k.z)

  def shift(c,d,s):#<=>c.add(d.mul(s))
    return Vec(c.x+d.x*s,c.y+d.y*s,c.z+d.z*s)

  def delta(u,v):
    return Vec(v.x-u.x,v.y-u.y,v.z-u.z)

def cam_rot(i0,i1,n,c,cost,sint):
  i0=i0.rot_perp(n,cost,sint)
  i1=i1.rot_perp(n,cost,sint) #TODO: optimize with cross product
  c=c.rot(n,cost,sint)
  return i0,i1,c)");

constexpr ScriptTemplate mesh_v3ScriptTemplate("mesh_v3.py", "\x01" R"(from td_math_v3 import *
from kandinsky import get_keys as gk,fill_rect as fr,draw_string as ds,wait_vblank as wb,draw_line as line,fill_triangle as triangle
from math import pi as PI,cos,sin
from time import monotonic as mnt

def tr(A,B,C,c,b=False,c2=(0,0,0)):triangle(A.x,A.y,B.x,B.y,C.x,C.y,c,b,c2)
def dl(A,B,c=(255,0,0)):line(A.x,A.y,B.x,B.y,c)

mesh=[Vec(-1,-1,-1),Vec(1,-1,-1),Vec(1,-1,1),Vec(-1,-1,1),Vec(-1,1,-1),Vec(1,1,-1),Vec(1,1,1),Vec(-1,1,1)]
triangles=[0,1,5,0,5,4,1,2,6,1,6,5,2,3,7,2,7,6,3,0,4,3,4,7,4,5,6,4,6,7,1,0,3,1,3,2]
#edges=[0,1,1,2,2,3,3,0,0,4,1,5,2,6,3,7,4,5,5,6,6,7,7,4]
colors=[(192,0,0),(160,0,0),(192,192,0),(160,160,0),(0,192,0),(0,160,0),(0,192,192),(0,160,160),(0,0,192),(0,0,160),(192,0,192),(160,0,160),(64,64,64)]

#mesh=[Vec(-1,0,-1),Vec(1,0,-1),Vec(0,0,1),Vec(0,1,0)]
#triangles=[0,2,1,0,1,3,2,0,3,1,2,3]
#colors=[(255,0,0),(192,192,0),(0,192,0),(0,0,192)]

#mesh=[Vec(-1,0,-1),Vec(1,0,-1),Vec(1,0,1),Vec(-1,0,1)]
#triangles=[0,1,2,0,2,3]
#edges=[0,1,1,2,2,3,3,0]
#colors=[(192,0,0),(0,192,0)]

#mesh=[Vec(-1,-2,-1),Vec(1,-2,-1),Vec(1,-2,1),Vec(-1,-2,1),Vec(-1.5,0,-1.5),Vec(1.5,0,-1.5),Vec(1.5,0,1.5),Vec(-1.5,0,1.5),Vec(-1,2,-1),Vec(1,2,-1),Vec(1,2,1),Vec(-1,2,1),Vec(-.5,3,-.5),Vec(.5,3,-.5),Vec(.5,3,.5),Vec(-.5,3,.5)]
#triangles=[0,2,1,0,3,2,0,1,5,0,5,4,1,2,6,1,6,5,2,3,7,2,7,6,3,0,4,3,4,7,4,5,9,4,9,8,5,6,10,5,10,9,6,7,11,6,11,10,7,4,8,7,8,11,8,9,13,8,13,12,9,10,14,9,14,13,10,11,15,10,15,14,11,8,12,11,12,15,12,13,14,12,14,15]#,8,9,11,9,10,11]
#colors=[(32,32,32),(64,64,64),(0,255,0),(0,192,0),(0,0,255),(0,0,192),(255,255,0),(192,192,0),(255,0,0),(192,0,0),(0,128,0),(0,96,0),(0,0,128),(0,0,96),(128,128,0),(96,96,0),(128,0,0),(96,0,0),(0,64,0),(0,32,0),(0,0,64),(0,0,32),(64,64,0),(32,32,0),(64,0,0),(32,0,0),(128,128,128),(192,192,192)]

cm=Vec(0,0,0)#center of rot
am=Vec(0,1,0)#axis of rot
mrotspd=2

cam=Vec(0,5,-6)#cam origin
ci,cj,ck=Vec(1,0,0),Vec(0,2**-.5,2**-.5),Vec(0,-2**-.5,2**-.5)#1,0,0,0,.707,.707,0,-.707,.707#cam"s axes, can rotate FREELY
crspd,cmspd=1.5,3
dnearplane=1.5

fov=PI/2#FOV
w,h=320,222
l=.5*cos(fov/2)/sin(fov/2)
toxw,toyw=lambda x:int((x+.5)*w),lambda y:int((.5-y*w/h)*h)

timed={"inp":0,"rot":0,"tlt":0,"prj":0,"lin":0,"tri":0}

framecount=0
doLines=False
domrot=True
tog=False
t0=mnt()
while not "onOff" in gk():
  dispg=[]#1D:flattened 2D(n,3)
  dispi=[]#1D
  dt=mnt()-t0

  #parse inputs
  inp=gk()
  #timerstart=mnt()
  if "shift" in inp:#displace
    k=1 if "right" in inp else -1 if "left" in inp else 0
    if k:
      cam=cam.shift(ci,k*cmspd*dt)
    k=1 if "exp" in inp else -1 if "sin" in inp else 0
    if k:
      cam=cam.shift(ck,k*cmspd*dt)
    k=1 if "up" in inp else -1 if "down" in inp else 0
    if k:
      cam=cam.shift(cj,k*cmspd*dt)
  elif "home" in inp:#zoom
    dfov=0 if not "up" in inp and not "down" in inp else -.05 if "up" in inp else .05
    if dfov:
      fov=max(.05,min(3.1,fov+dfov))
      l=.5*cos(fov/2)/sin(fov/2)
  elif "EE" in inp:
    mrotspd*=1.05 if "up" in inp else .95 if "down" in inp else 1
  else:#rotate
    abct,abst=cos(crspd*dt),sin(crspd*dt)
    k=-1 if "right" in inp else 1 if "left" in inp else 0
    if k:ci,ck,cam=cam_rot(ci,ck,cj,cam,abct,k*abst)
    k=-1 if "up" in inp else 1 if "down" in inp else 0
    if k:cj,ck,cam=cam_rot(cj,ck,ci,cam,abct,k*abst)
    k=-1 if "exp" in inp else 1 if "sin" in inp else 0
    if k:ci,cj,cam=cam_rot(ci,cj,ck,cam,abct,k*abst)
  if "0" in inp:#toggle mesh rotation
    if tog:
      tog=False
      domrot=not domrot
  elif "." in inp:#toggle drawing edges
    if tog:
      tog=False
      doLines=not doLines
  else:tog=True
  del inp
  #timed["inp"]+=mnt()-timerstart

  #rotate mesh
  #timerstart=mnt()
  dt=mnt()-t0
  if domrot:
    #only compute cosine and sine once for rotation
    cost,sint=cos(mrotspd*dt),sin(mrotspd*dt)
    for i,v in enumerate(mesh):
      mesh[i]=v.rot(am,cost,sint)
  t0=mnt()
  #timed["rot"]+=mnt()-timerstart

  #find mesh on screen
  for i in range(len(triangles)//3):
    #timerstart=mnt()
    #coordinates in camera space
    v0=mesh[triangles[3*i]].add(cm).chco(cam,ci,cj,ck)
    v1=mesh[triangles[3*i+1]].add(cm).chco(cam,ci,cj,ck)
    v2=mesh[triangles[3*i+2]].add(cm).chco(cam,ci,cj,ck)
    #timed["tlt"]+=(mnt()-timerstart)/len(triangles)

    #timerstart=mnt()
    #face normal
    normal=v0.delta(v1).cross(v1.delta(v2))

    #draw only if facing camera
    if normal.dot(v0)>=0:
      #sort but keep orientation,v0 lowest z
      if v1.z<v0.z:
        if v2.z<v1.z:
          v0,v1,v2=v2,v0,v1
        else:
          v0,v1,v2=v1,v2,v0
      elif v2.z<v0.z:
          v0,v1,v2=v2,v0,v1

      #clipping for the near plane (thales theorem)
      #4 cases: all on screen->NOPE/2 on screen->clip,2tr/1 on screen->clip,1tr/0 on screen->next
      if v0.z<dnearplane:
        if v1.z<dnearplane:
          if v2.z<dnearplane:#none on screen
            continue
          #v2 on screen
          mi,mj=(v2.z-dnearplane)/(v2.z-v0.z),(v2.z-dnearplane)/(v2.z-v1.z)
          pi=Vec(toxw((v2.x+mi*(v0.x-v2.x))*l/dnearplane),toyw((v2.y+mi*(v0.y-v2.y))*l/dnearplane))
          pj=Vec(toxw((v2.x+mj*(v1.x-v2.x))*l/dnearplane),toyw((v2.y+mj*(v1.y-v2.y))*l/dnearplane))
          p2=Vec(toxw(v2.x*l/v2.z),toyw(v2.y*l/v2.z))

          dispg.extend((pi,pj,p2))
          dispi.append(i)
        elif v2.z<dnearplane:#v1 on screen
          mi,mj=(v1.z-dnearplane)/(v1.z-v2.z),(v1.z-dnearplane)/(v1.z-v0.z)
          pi=Vec(toxw((v1.x+mi*(v2.x-v1.x))*l/dnearplane),toyw((v1.y+mi*(v2.y-v1.y))*l/dnearplane))
          pj=Vec(toxw((v1.x+mj*(v0.x-v1.x))*l/dnearplane),toyw((v1.y+mj*(v0.y-v1.y))*l/dnearplane))
          p1=Vec(toxw(v1.x*l/v1.z),toyw(v1.y*l/v1.z))

          dispg.extend((pi,pj,p1))
          dispi.append(i)
        else:#v1&v2 on screen
          mi,mj=(dnearplane-v0.z)/(v2.z-v0.z),(dnearplane-v0.z)/(v1.z-v0.z)
          pi=Vec(toxw((v0.x+mi*(v2.x-v0.x))*l/dnearplane),toyw((v0.y+mi*(v2.y-v0.y))*l/dnearplane))
          pj=Vec(toxw((v0.x+mj*(v1.x-v0.x))*l/dnearplane),toyw((v0.y+mj*(v1.y-v0.y))*l/dnearplane))
          p1=Vec(toxw(v1.x*l/v1.z),toyw(v1.y*l/v1.z))
          p2=Vec(toxw(v2.x*l/v2.z),toyw(v2.y*l/v2.z))

          dispg.extend((pi,pj,p2,pj,p1,p2))
          dispi.extend((i,i))
      else:#all on screen
        p0=Vec(toxw(v0.x*l/v0.z),toyw(v0.y*l/v0.z))
        p1=Vec(toxw(v1.x*l/v1.z),toyw(v1.y*l/v1.z))
        p2=Vec(toxw(v2.x*l/v2.z),toyw(v2.y*l/v2.z))
        dispg.extend((p0,p1,p2))
        dispi.append(i)
    #timed["prj"]+=(mnt()-timerstart)/len(triangles)

  #clear screen
  wb()
  fr(0,0,320,222,(255,255,255))
  #draw mesh
  for i,p0,p1,p2 in zip(dispi,dispg[::3],dispg[1::3],dispg[2::3]):
    #timerstart=mnt()
    tr(p0,p1,p2,colors[i],doLines)
    #timed["tri"]+=(mnt()-timerstart)/len(dispi)
    #if doLines:
    #  dl(p0,p1,(0,0,0))
    #  dl(p1,p2,(0,0,0))
    #  dl(p2,p0,(0,0,0))

  #framecount+=1
  #wait if necessary
  while mnt()-t0<1/30:0

#total=sum(timed.values())
#for k,v in timed.items():
#  print("{}=".format(k),"{}".format(v/framecount*1000)[:6],"ms ->","{}".format(v/total*100)[:5],"%"))");
>>>>>>> 03b42069898cdbfb44f622c0b41164a55407cc90

const ScriptTemplate * ScriptTemplate::Empty() {
  return &emptyScriptTemplate;
}

/*
const ScriptTemplate * ScriptTemplate::Squares() {
  return &squaresScriptTemplate;
}

const ScriptTemplate * ScriptTemplate::Mandelbrot() {
  return &mandelbrotScriptTemplate;
}

const ScriptTemplate * ScriptTemplate::Polynomial() {
  return &polynomialScriptTemplate;
}
*/
<<<<<<< HEAD
=======

const ScriptTemplate * ScriptTemplate::Td_math_v3() {
  return &td_math_v3ScripTemplate;
}

const ScriptTemplate * ScriptTemplate::Mesh_v3() {
  return &mesh_v3ScriptTemplate;
}
>>>>>>> 03b42069898cdbfb44f622c0b41164a55407cc90

}
