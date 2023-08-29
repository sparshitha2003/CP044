from tkinter import *
from tkinter import colorchooser
# import PIL.ImageGrab as imagegrab
# import PIL
# from PIL import ImageGrab as imagegrab
#this helps to screennshot
# from tkinter import filedialog
root=Tk() 
# 1. this creates a root windoow
root.title("paint tool")
# 3.if we want to give the title to the main window
root.geometry("1000x600")
#4.if we want to set the width and height of the main window
frame1=Frame(root,height=100,width=1000,)
#5.we initialize the frame in the main widow root,
frame1.grid(row=0,column=0,sticky=NW)
#6.we place the frame1 in the 0 th row and 0th coloumn
#toolsframe
toolsframe=Frame(frame1,height=100,width=100,relief=SUNKEN,borderwidth=3)
toolsframe.grid(row=0,column=0,)
def usepencil():
     stroke_color.set("black")
     canvas["cursor"]="arrow"
pencilbutton=Button(toolsframe,text="pencil",width=10,command=usepencil)

pencilbutton.grid(row=0,column=0)

def useeraser():
     stroke_color.set("white")
     canvas["cursor"]=DOTBOX
eraserbutton=Button(toolsframe,text="eraser",width=10,command=useeraser)
eraserbutton.grid(row=1,column=0)
toolslabel=Label(toolsframe,text="tools",width=10,)
toolslabel.grid(row=2,column=0)
#sizeframe
sizeframe=Frame(frame1,height=100,width=100,relief=SUNKEN,borderwidth=3)
sizeframe.grid(row=0,column=1)
defaultbutton=Button(sizeframe,text="default",width=10,command=usepencil)
defaultbutton.grid(row=0,column=0)
stroke_size=IntVar()
stroke_size.set(1)
options=[1,2,3,4,5,6,8,9,10]
sizelist=OptionMenu(sizeframe,stroke_size,*options)
sizelist.grid(row=1,column=0)
sizelabel=Label(sizeframe,text="size",width=10,)
sizelabel.grid(row=2,column=0)
#colorboxframe
colorboxframe=Frame(frame1,height=100,width=100,relief=SUNKEN,borderwidth=3)
colorboxframe.grid(row=0,column=2)
#initialize variables
previouscolor1=StringVar()
previouscolor1.set("white")
previouscolor2=StringVar()
previouscolor2.set("white")

def selectcolor():

     selectedcolor=colorchooser.askcolor(title="selectcolor")
     print(selectedcolor[1])
     if selectedcolor[1]==None:
          stroke_color.set("black")
     else:     
       stroke_color.set(selectedcolor[1])
       previouscolor2.set(previouscolor1.get())
       previouscolor1.set(selectedcolor[1])
       previous1button["bg"]=previouscolor1.get()
       previous2button["bg"]=previouscolor2.get()


colorboxbutton=Button(colorboxframe,text="selectcolor",width=10,command=selectcolor)
colorboxbutton.grid(row=0,column=0)
previous1button=Button(colorboxframe,text="previous1",width=10,)
previous1button.grid(row=1,column=0)
previous2button=Button(colorboxframe,text="previous2",width=10,)
previous2button.grid(row=2,column=0)

#colorframe
colorframe=Frame(frame1,height=100,width=100,relief=SUNKEN,borderwidth=3)
colorframe.grid(row=0,column=3)
#red button
redbutton=Button(colorframe,text="red",width=10,bg="red",command=lambda:stroke_color.set("red"))
redbutton.grid(row=0,column=0)
#green button
greenbutton=Button(colorframe,text="green",width=10,bg="green",command=lambda:stroke_color.set("green"))
greenbutton.grid(row=1,column=0)
#blue button
bluebutton=Button(colorframe,text="blue",width=10,bg="blue",command=lambda:stroke_color.set("blue"))
bluebutton.grid(row=2,column=0)
#yellowbutton
yellowbutton=Button(colorframe,text="yellow",width=10,bg="yellow",command=lambda:stroke_color.set("yellow"))
yellowbutton.grid(row=0,column=1)
#orange button
orangebutton=Button(colorframe,text="orange",width=10,bg="orange",command=lambda:stroke_color.set("orange"))
orangebutton.grid(row=1,column=1)
#pink button
pinkbutton=Button(colorframe,text="pink",width=10,bg="pink",command=lambda:stroke_color.set("pink"))
pinkbutton.grid(row=2,column=1)
#shape frame
shapeframe=Frame(frame1,height=100,width=100,relief=SUNKEN,borderwidth=3)
shapeframe.grid(row=0,column=4)
# Widgetshapes=Widget(shapeframe,width=10)
# Widgetshapes.grid(row=1,column=4)
shapelabel=Label(shapeframe,text="shapes",width=10,)
shapelabel.grid(row=2,column=0)
#saveimageframe
# saveimageframe=Frame(frame1,height=100,width=100,relief=SUNKEN,borderwidth=3)
# saveimageframe.grid(row=0,column=4)
# def saveimage():
#      # img=imagegrab.grab(bbox=(0,0,500,500))
#      # img.show()
#      pass

# savebutton=Button(saveimageframe,text="SAVE",width=10,command=saveimage())
# savebutton.grid(row=2,column=1)

#-------------------frame2--------------------------------------------
frame2=Frame(root,height=500,width=1000,bg="yellow")
frame2.grid(row=1,column=0)
canvas=Canvas(frame2,height=500,width=1000,bg="white")
canvas.grid(row=0,column=0)
#takes x and y axiis to draw the line
#------
#7variables for pencil
prevpoint=[0,0]
currentpoint=[0,0]
stroke_color=StringVar()
stroke_color.set("green")
#to set the default color
def paint(event):
     global prevpoint,currentpoint
     x=event.x
     y=event.y
     currentpoint=[x,y]
    #  canvas.create_oval(x,y,x+20,y+20,fill="black")

     if prevpoint !=[0,0]:
          canvas.create_polygon(prevpoint[0],prevpoint[1],currentpoint[0],currentpoint[1],fill=stroke_color.get(),outline=stroke_color.get(),width=stroke_size.get())
     prevpoint=currentpoint   
     if event.type == "5":
          prevpoint=[0,0]
  
canvas.bind("<B1-Motion>",paint)

# 8. the bind helps to bind the event(clicking button 1) with the function
#but it gives dotted line when we move fast,so i should join the dots using the create line
canvas.bind("<ButtonRelease-1>",paint)
root.resizable(False,False)
#5.this means i dont to resize the heght and width
root.mainloop()
# 2. now the main root stays in the screen and we can interact with the window
