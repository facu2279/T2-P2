
# --------------------------------------------------------------------
#  Makefile de tarea 2.

#  Laboratorio de Programación 2.
#  InCo-FIng-UDELAR

# Define un conjunto de reglas.
# Cada regla tiene un objetivo, dependencias y comandos.
#objetivo: dependencia1 dependencia2...
#	comando1
#	comando2
#	comando3
# (antes de cada comando hay un tabulador, no espacios en blanco).
# Se invoca con
#make objetivo
# para que se ejecuten los comandos.
#
# Si `objetivo' es un archivo los comandos se ejecutan solo si no está
# actualizado (esto es, si su fecha de actualización es anterior a la de alguna
# de sus dependencias.
# Previamente se aplica la regla de cada dependencia.


# --------------------------------------------------------------------

# Objetivo predeterminado (no se necesita especificarlo al invocar `make').
all: principal

# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing entrega

MODULOS = utils info cadena usoTads

# directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj

TESTDIR = test

# extensión de los archivos
EXT = cpp
# compilador
CC = g++ # gcc -x c 
LD = g++ # gcc
# opciones de compilación
CCFLAGS = -Wall -Werror -I$(HDIR) -g  -DNDEBUG
# -DNDEBUG
# se agrega esta opción para que las llamadas a assert no hagan nada.



# cadena de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.$(EXT))
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal


# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).$(EXT)
	@printf 'Compilando $(<) \n'; \
	$(CC) $(CCFLAGS) -c $< -o $@




$(ODIR)/%.o: $(CPPDIR)/%.$(EXT)  $(HDIR)/%.h
	@printf 'Compilando $(<) \n'; \
	$(eval resr = $(shell grep -n -P '_rep_(?!$(basename $(notdir $<)))' $<)) \
	$(eval resh = $(subst #,\#,$(shell grep -n -P 'include(?!.*[.]h)' $< ))) \
	$(eval resc = $(shell grep -n 'nodoCadena' $< )) \
	if [ -z "$(resr)" ] && [ -z "$(resh)" ] && { [ -z "$(resc)" ] || [ -n "$(findstring cadena, $<)" ] ; }; \
	then $(CC) $(CCFLAGS) -c $< -o $@ ; \
	else \
		if [ -n "$(resh)" ]; then printf '  "$(resh)": Include de archivos que no son .h \n' ; fi ; \
		if [ -n "$(resr)" ]; then printf '  "$(resr)": Uso de representación de otros tipos\n' ; fi ; \
		if [ -n "$(resc)" ]; then printf '  "$(resc)": Uso de nodoCadena\n' ; fi ; \
		printf '    NO SE COMPILO $(<)\n' ; \
		rm -f $@; \
	fi


# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE):$(ODIR)/$(PRINCIPAL).o $(OS)
	@printf 'Compilando y enlazando $(@) \n'; \
	$(LD) $(CCFLAGS) $^ -o $@


# Genera el entregable.
ENTREGA=Entrega2.tar.gz
CPPS_ENTREGA = cadena.cpp usoTads.cpp
entrega:
	@rm -f $(ENTREGA)
	tar zcvf $(ENTREGA) -C src $(CPPS_ENTREGA)
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ENTREGA)


# borra binarios
clean_bin:
	@rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS)

# borra resultados de ejecución y comparación
clean_test:
	@rm -f $(TESTDIR)/*.sal $(TESTDIR)/*.diff

# borra binarios, resultados de ejecución y comparación, y copias de respaldo
clean:clean_test clean_bin
	@rm -f *~ $(HDIR)/*~ $(CPPDIR)/*~ $(TESTDIR)/*~



