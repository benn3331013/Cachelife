CC=gcc
CXX=g++

CFLAGS=-Wall -O3
CPPFLAGS=-I./include -L./lib #$(addprefix -I, ./include)
#     On some CPUs, in particular the x86s, the static libgmp.a should be used for maximum speed, since the PIC code in the shared libgmp.so will have a small overhead on each function call and global data address. For many programs this will be insignificant, but for long calculations there’s a gain to be had.


LDLIBS=-lgmp
LDFLAGS=`sdl2-config --cflags --libs`


CACHELIFE_O_FILES=$(addsuffix .o, $(addprefix ./build/, InitCachelife \
CreateZeros VerifyCache \
InsertLivingCell CachelifeSet_file CachelifeSet_array ArrayFromNode \
Join Surround Crop \
Next_4x4 Next \
Export_file ))

$(shell mkdir -p build/display)
DISPLAY_O_FILES=$(addsuffix .o, $(addprefix ./build/display/, InitCachelifeDisplay \
SDLWindowThread \
RenderArray RenderNodes))
#PrintArray PrintNode


#	Object files
build/%.o: src/%.c include/cachelife.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
build/cachelife_with_display.o: src/cachelife.c include/cachelife.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -DCACHELIFE_DISPLAY -c $< -o build/cachelife.o
build/cachelife_slow.o: src/cachelife.c include/cachelife.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -DCACHELIFE_DISPLAY -DCACHELIFE_SLOW -c $< -o build/cachelife.o
build/cachelife_no_display.o: src/cachelife.c include/cachelife.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o build/cachelife.o

build/Cachelife.o: $(CACHELIFE_O_FILES)
	ld -r $(CACHELIFE_O_FILES) -o $@
#	$(RM) $(CACHELIFE_O_FILES)

build/display/%.o: src/display/%.c include/cachelife_display.h include/cachelife.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
build/Cachelife_display.o: $(DISPLAY_O_FILES)
	ld -r $(DISPLAY_O_FILES) -o $@




# Cachelife without display : maximum speed! 
Cachelife: main.c build/cachelife_no_display.o build/Cachelife.o src/cachelife.c
	$(CC) $(CFLAGS) $(CPPFLAGS) build/Cachelife.o build/cachelife.o $< -o Cachelife $(LDLIBS)

# Cachelife with display
Cachelife_display: main.c build/cachelife_with_display.o build/Cachelife.o build/Cachelife_display.o src/cachelife.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DCACHELIFE_DISPLAY build/Cachelife.o build/Cachelife_display.o build/cachelife.o $< -o Cachelife $(LDLIBS) -lSDL2 $(LDFLAGS)

# Cachelife with slow display
Cachelife_slow: main.c build/cachelife_slow.o build/Cachelife.o build/Cachelife_display.o src/cachelife.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DCACHELIFE_DISPLAY -DCACHELIFE_SLOW \
	build/Cachelife.o build/Cachelife_display.o build/cachelife.o $< -o Cachelife \
	$(LDLIBS) -lSDL2 $(LDFLAGS)




.PHONY: clean
clean:
	rm -f build/*.o Cachelife