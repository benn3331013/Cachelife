# Cachelife

This is a fairly simple and straightforward implementation of [Bill Gosper's Hashlife Algorithm](https://en.wikipedia.org/wiki/Hashlife), in C.

The majority of the code was written in 2021, but it has been refactored, and updated a bit.

This is not an "easy-to-use" project, it's merely a demonstration of the power of the hashlife algorithm, and as such the display is pretty bad.

However, if you just need to load a configuration and get the result a **LOT OF ITERATIONS** (voluntarily imprecise here) later, you COULD use Cachelife.

You might notice that, from *hashlife* to *Cachelife*, the "hash" has disappeared. Because Cachelife doesn't use hashing. You might wonder why.

## Installation
### Dependencies
The algorithm in itself is completely independant of any dependency, but the project as a whole relies on 2 libraries : 
 * **GMP**, for the manipulation of big ints, for the counter of iterations. You could remove this dependency but you would then be limited to 18446744073709551615==2^64 (or 340282366920938463463374607431768211456 == 2^128 ) iterations.<br>
 Since the performance difference wouldn't be that big, we chose to use GMP by default.
 * **SDL2**, for the GUI. This is used to display the game ( see [Display](##Display)). <br>
 You can compile the project with or without this library (see [Compiling](##Compiling)).

### Container
The easiest way to use those dependencies is to use the Docker container. They're imported as packages.

### Installing locally
If, for whatever reason, you prefer not to use the Docker container.
The install.sh script is provided to ease their (local) installation. You can use it by simply executing : 
```
./install.sh
```
The installation, in that case, is made from the GitHub repository of SDL2, and the 6.2.1 version of GMP, which is provided with the project.<br>
If you do NOT install these locally, and prefer to use your global versions, you should NOT have to make adjustments to the Makefile.



## Compiling
A makefile is provided, with different options : 
 * With display : ```make Cachelife```  
 * With slow display : ```make Cachelife_slow``` 
 * Without display : ```make Cachelife_no_display```

Versions with display are obviously slower than the ones without. 

## Running
If you choose to run with the docker container : 
```
sudo docker build -t cachelife .
sudo docker run --name cachelife-container -it cachelife
```
Then, you can simply run one of the following : 
```
make Cachelife
make Cachelife_slow
make Cachelife_no_display
```

To execute, you can simply type : 
```
./Cachelife -l <number of iterations> -f <file containing the initial position>
```
(you can get a list of available commands with --help or -h).


## Display
<u>PLEASE BE VERY CAREFUL WHEN USING DISPLAY FOR A HIGH NUMBER OF ITERATION AND A LOT OF LIVING CELLS.</u><br>
The display for this project is very basic.
It does NOT display every iteration, since that would make the hashlife algorithm useless.<br>
The display is non-moving, it always show the same part of the space. 
If you have a moving figure leaving the screen, the display will NOT follow.<br>
It only shows a low amount of cells : if you only have a static figure, it will display a square of cells, containing your figure. The unshown rest of the space is empty.


## References
https://en.wikipedia.org/wiki/Hashlife
https://www.drdobbs.com/jvm/an-algorithm-for-compressing-space-and-t/184406478