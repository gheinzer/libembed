Import("projenv", "env")
projenv.ProcessFlags("-std=c++17")

defines = list(projenv["CPPDEFINES"])
defines.append(("LIBEMBED_PLATFORM", projenv["PIOPLATFORM"]))
defines.append(("LIBEMBED_BOARD", str(projenv["BOARD"]).strip()))
defines.append(("LIBEMBED_FRAMEWORK", projenv["PIOFRAMEWORK"]))

projenv.Append(
    CPPDEFINES=defines
)