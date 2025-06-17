Phone Call Simulation with Statistics and GUI

This project simulates incoming phone calls and analyzes call-related statistics.

Viktoria Toman and Jakub Gorczyca collaboratively implemented the generation of incoming calls using the Poisson distribution, as well as the simulation of call durations based on both normal and Poisson distributions. Their work includes queue handling via linked lists, ensuring configurable parameters, and calculating key statistics such as average call time, number of calls, and average wait time.

I developed a graphical user interface (GUI) that allows the user to load input data from a file or a text field, then displays a summary of the simulation results.
A sample input file is included in the project to help you get started quickly.


If you are having issues with GTK, you can follow these steps:
1. Download and install MSYS2 • Visit https://www.msys2.org 

2. Update MSYS2 packages Open the MSYS2 directory and launch mingw bash, then run:

`pacman -Syu`
`pacman -Su`
3. Install GTK3 compilation packages In the Bash terminal, enter the following (adjust the command if you're using a system with a different architecture):


`pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk3 mingw-w64-x86_64-pkg-config`
This installs the GCC compiler, GTK3 libraries, and pkg-config utility.

4. Compile the program. Move your project files to ./home/User, then compile by running:

<pre>
  gcc main.c stats.c call.c -o app.exe `pkg-config --cflags --libs gtk+-3.0`
</pre>

5. Run the program After compiling, execute the program with:

`./app.exe`

