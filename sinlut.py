import math


def fxFloatUp(x):
    return x / (1 << 16)


def fxFloatDown(x):
    return int(x * (1 << 16))


ENTRIES_LEN = 512
sin_entries = []
cos_entries = []

for i in range(ENTRIES_LEN):
    a = (math.pi * 2 / ENTRIES_LEN) * i
    sin_entries.append(fxFloatDown(math.sin(a)))
    cos_entries.append(fxFloatDown(math.cos(a)))

with open("_sinlut.h", "w+") as file:
    file.write(f"#define SINLUT_ENTRIES {ENTRIES_LEN}\n")
    file.write("int32_t sinlut[SINLUT_ENTRIES] = {")
    for i in sin_entries:
        file.write(str(i) + ",")
    file.write("};\n")
    file.write("int32_t coslut[SINLUT_ENTRIES] = {")
    for i in cos_entries:
        file.write(str(i) + ",")
    file.write("};\n")
