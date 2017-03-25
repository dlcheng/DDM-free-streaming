
#--------------------------------------- Select target computer
#SYSTYPE="Workstation"
SYSTYPE="dlcheng"
#SYSTYPE="ITSC"

#--------------------------------------- Adjust settings for target computer
ifeq ($(SYSTYPE),"Workstation")
CC       =   gcc   
OPTIMIZE =   -O3 -Wall 
GSL_INCL =  -I/home/dlcheng/Install/gsl/include
GSL_LIBS =  -L/home/dlcheng/Install/gsl/lib
endif

ifeq ($(SYSTYPE),"dlcheng")
CC       =   gcc   
OPTIMIZE =   -O3 -Wall 
GSL_INCL =  -I/home/dlcheng/Install/gsl-1.16/include
GSL_LIBS =  -L/home/dlcheng/Install/gsl-1.16/lib
endif

ifeq ($(SYSTYPE),"ITSC")
CC       =   gcc   
OPTIMIZE =   -O3 -Wall
GSL_LIBS=   -L/users/s0902248/Lib/gsl-1.9/lib  -Wl,"-R /users/s0902248/Lib/gsl-1.9/lib"
GSL_INCL =  -I/users/s0902248/Lib/gsl-1.9/include
endif



OPTIONS =  $(OPTIMIZE) $(OPT) 

EXEC   = FSC

OBJS   = main.o

INCL   = Makefile


CFLAGS = $(OPTIONS) $(GSL_INCL) 


LIBS   = $(GSL_LIBS) -lgsl -lgslcblas -lm 

$(EXEC): $(OBJS) 
	$(CC) $(OBJS) $(LIBS)   -o  $(EXEC)  

$(OBJS): $(INCL) 


clean:
	rm -f $(OBJS) $(EXEC) *.gch

