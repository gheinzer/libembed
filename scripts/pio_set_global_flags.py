Import("projenv", "env")
projenv.ProcessFlags("-std=gnu++17")

defines = list(projenv["CPPDEFINES"])
defines.append(("PIOPLATFORM", projenv["PIOPLATFORM"]))
defines.append(("PIOENV", projenv["PIOENV"]))
defines.append(("PIOFRAMEWORK", projenv["PIOFRAMEWORK"]))

projenv.Append(
    CPPDEFINES=defines
)