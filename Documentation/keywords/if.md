# if

# Syntax:

```
if(NameOfInt/# ?= NameOfInt/#) {
    ;Other keywords to run
}
``` 

# ? Options:

`=` is used to check if the value on the left is equal to the right\
`<` is used to check if the value on the left is lesser than or equal to the right\
`>` is used to check if the value on the left is greater than or equal to the right\
`!` is used to check if the value on the left is not equal to the right\

# Description:

The `if()` conditional keyword is used to change if a set of keywords are executed or not based off of the result of the condition.

# Example: 

```
if(0 == 0) {
    printn("0 is equal to 0")
}
if(-10 <= 0) {
    printn("-10 is lesser than or equal to 0")
}
if(10 >= 0) {
    printn("10 is greater than or equal to 0")
}
if(1 == 0) {
    printn("1 is equal to 0")
}
if(1 != 0) {
    printn("1 is not equal to 0")
}
```