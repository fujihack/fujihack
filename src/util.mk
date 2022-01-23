# "Parse" C header, converting C macro to Make macro
# See https://gist.github.com/petabyt/898d3437decf65fc04fc50bd0e125362
define importMacro
    $(shell echo "#include <stdio.h>\n \
        int main() {printf(\"$(2)=$(3)\", $(2));return 0;}" > temp.c)
    $(shell $(CC) -include $(1) temp.c -o temp.o)
	$(eval $(shell ./temp.o))
    $(shell $(RM) temp.c temp.o)
endef
