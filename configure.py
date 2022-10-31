import os, platform, subprocess

try:
    import ptpy
except e:
    print("couldn't import ptpy")

def checkCommand(shell):
    return subprocess.check_call(["which", shell])

def checkAll():    
    print("Checking for host GCC")
    if checkCommand("gcc"):
        print("gcc not found")
        exit(1)
    else:
        print("gcc checked")

    print("Checking for make")
    if checkCommand("make"):
        print("make not found")
        exit(1)
    else:
        print("make checked")

    print("Checking for ARM GCC")
    if checkCommand("arm-none-eabi-gcc"):
        print("Could not find arm-none-eabi-gcc")
        exit(1)
    else:
        print("arm cc checked")

checkAll()
