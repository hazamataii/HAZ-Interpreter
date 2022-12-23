# playFile

# Syntax:

```
playFile("PathToFile")
playFile(<PathToFile>)
```

# Description:

The `playFile()` function is used to load and execute another `.hazl` file. Quotation marks are to be used if the specified file path is relative to the main/first running file. `<>` are to be used if the specified file path is relative to the interpreter's executable.

# Example:

```
;Opens and reads the local(to the first (from arguments) running file) .hazl file
playFile("日本語.hazl")
;Opens and reads the local(to the interpreter's location) .hazl file
playFile(<日本語.hazl>)
```