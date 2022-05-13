![image](https://img.icons8.com/stickers/100/000000/graduation-cap.png)

# clifter-os
this the main repository of clifterOS. this project is currently in high development, and i predominately written in C of course ome parts such as hardware communication, scripting, building, etc ...


## directory structure

- **arch**: architecture dependant codes
  - **boot**: GRUB bootloader information
    - **multiboot**: GRUB multiboot information
- **include**: all include files
- **libc**: c library constructed and used by clifter os, non architecture and non-platform dependant code
- **bin**: Non administraator terminal commands
- **platform**: platform dependat code
  - **pc**: PC platform

## architecture

for now clifter os running with x86(32bit) architecture

## installation

**building from source**

first make sure you have a ubuntu terminal (if you are on windos, ue the new linux subsystem feature). then donwload the depedencie using ``bash setup.sh``. then compile the ClifterOs using make. now that you have qemu after executede ``setup.sh``, you can go ahead and run on qemu using ``make qmue_compile`` for running the binary or ``make qemu_iso`` to run the actuaal image file (ISO).

## installing from source ubuntu

Clone repository **ClifterOS** from git
```
git clone https://github.com/slowy07/clifter-os
```

After sucessfully cloning the project You can have additonal configurations to run at a specific Architecture / Platform / Compiler / etc...

Look at Documentation/Options for more on this.

If you choose not to have additonal options it will configure with the defaults set by Makefile ``?=`` . Now run make

```
make
```

and this will give you a sucessfull imge file (ISO) for clifterOS,if you have qemu for testing you can run

```
make qemu_compile
```

for running the binry version or the actual ISO using

```
make qemu_iso
```