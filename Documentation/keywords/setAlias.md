# setAlias

# Syntax:

```
setAlias(FUNCTION, FUNCTION_NAME, DESIRED_ALIAS)
```

# Description

The `setAlias()` function is used to allow one to use different names for functions.
This is useful for making it more readable for certain languages or making the file shorter.

# Example:

```
;Sets the alias of the function "printn" to "prt"
setAlias(FUNCTION, printn, prt)

;Use the alias to use printn
prt("setAlias Example!")
printn("Example!")
```