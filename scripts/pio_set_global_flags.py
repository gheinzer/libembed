Import("projenv", "env")
projenv.ProcessFlags("-std=c++17 -fexceptions")

defines = list(projenv["CPPDEFINES"])
defines.append(("LIBEMBED_PLATFORM", projenv["PIOPLATFORM"]))
boardName = str(projenv["BOARD"]).strip()
defines.append(("LIBEMBED_BOARD", boardName))
defines.append(f"LIBEMBED_BOARD_{boardName.upper()}")
defines.append(("LIBEMBED_FRAMEWORK", projenv["PIOFRAMEWORK"]))

projenv.Append(
    CPPDEFINES=defines
)