import os.path

filename = "obj/bootloader"
filesize = os.path.getsize(filename)

if filesize >= 510:
    print("1st stage bootloader can't be more then 512 bytes")
    exit()

with open(filename, "ab") as f:
    f.write(bytes(510 - filesize))
    f.write(bytes(1).fromhex("55"))
    f.write(bytes(1).fromhex("AA"))
