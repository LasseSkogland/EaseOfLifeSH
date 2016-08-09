all: link
	
link: compile
	@echo Linking files
	@link obj\keylog.obj /nologo /out:bin\kle.exe /FIXED /FILEALIGN:512 /ENTRY:main /IGNORE:4254
	
compile:
	@echo Compiling Files
	@cl /nologo /c keylog.c /GS- /O1 /Os /Foobj\keylog.obj