# Import macro from C -> GNU Make
# See https://gist.github.com/petabyt/898d3437decf65fc04fc50bd0e125362
define importMacro
    $(if $(2),
    $(info Importing $(2))
    $(shell printf "
        #include <stdio.h>\n \
        #ifndef $(2)\n \
            #define $(2) 0\n \
        #endif\n \
        int main() { \
		    printf(\"$(2)=$(3)\", $(2)); \
		return 0; \
		} \
		" > MakefileImportMacro.c)
    $(shell $(CC) -include $(1) MakefileImportMacro.c -o MakefileImportMacro.o)
    $(eval $(shell ./MakefileImportMacro.o))
    $(shell $(RM) MakefileImportMacro.c MakefileImportMacro.o)
    ,)
endef
