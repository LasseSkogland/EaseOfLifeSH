all: link

run: all
	@start bin\kle.exe
	
link: compile
	@echo Linking files
	@link obj\keylog.obj /nologo /out:bin\kle.exe
	
compile:
	@echo Compiling Files
	@cl /nologo /c keylog.c /Ox /Foobj\keylog.obj