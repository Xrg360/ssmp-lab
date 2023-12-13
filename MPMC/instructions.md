# Process to execute Assembly code on 8086

## Starting DOSBox

Search windows for DOSBox and launch it.

![image](https://github.com/Xrg360/ssmp-lab/assets/55801439/3a7d5cad-54db-4fa6-82f6-9a96de327a8b)

DOSBox starts with this screen

![image](https://github.com/Xrg360/ssmp-lab/assets/55801439/3697ef89-1657-466b-a6f2-759d45178cf5)


Type the commands 
```
mount c c:\8086
```
> replace the `c:\8086` with the location of your 8086 binary files

Use 
```
c:
``` 
> to move to the directory

![image](https://github.com/Xrg360/ssmp-lab/assets/55801439/572bbb97-7541-47e5-9d3c-81f18b4fd9d0)


## Start Creating, Assembling, Linking and Debugging assembly program files

### EDIT
To create files and edit them we make use of the `EDIT` command
```
EDIT <filename>
```

Since we are working with assembly program we name the file with a `.asm` extension

```
EDIT <filename>.asm
```
eg. Editing ADD.asm

![image](https://github.com/Xrg360/ssmp-lab/assets/55801439/79aa68ae-60ea-48b2-b2db-d095ec2d777b)

### ASSEMBLE
To assemble the files we make use of the `MASM` command
```
MASM <filename>.asm
```
eg. Assembling ADD.asm
This will produce a object file with the extension `.obj`

![image](https://github.com/Xrg360/ssmp-lab/assets/55801439/a84f0658-cf8d-4601-b385-9448de51fef3)

> Just press enter for the inputs asked by `MASM`
> Ojbect files cannot be executed directly, they have to be linked with the necessary libraires

### LINKING
To link Object files we make use of the `LINK` command
```
LINK <filename>
```
This will produce an executable file with the extension `.exe`

> Just press enter for the inputs asked by `LINK`
> Just providing the filename would be enough, though it is recommended to use the full file name with extension

eg. Linking ADD.obj

![image](https://github.com/Xrg360/ssmp-lab/assets/55801439/c144fc33-04ee-409c-a62b-eb19ea92cef6)


### DEBUGGING

We proceed with debugging using the `DEBUG` command
```
DEBUG <filename>.exe
```

This will start the debug process and asks the user for commands to start debugging

eg. Debugging ADD.exe

![image](https://github.com/Xrg360/ssmp-lab/assets/55801439/07381b25-3ff5-433b-946e-0d281b87fa15)

The commands are as follows:
|Command|Use|
|-|-|
|T|Executes one instruction and then displays the contents of all registers, the status of all flags, and the decoded form of the instruction that Debug will execute next|
|E|Enters data into memory starting at a specified address|
|G|Runs the executable file that is in memory, (This will run untill it sees an interrupt)|
|Q|Quit the debug menu|




