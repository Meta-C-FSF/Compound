# COMPOUND

Compound makes C more secure, and handy.  

Compound is also recently getting developed with its Object-Oriented Programming
functionalities.  

By the time, we've finished several things that worth mentioning.  

Such as:  
  - `Catlog`  
     A logging system with ease to use.  

  - `MemoryStack`  
     Of which you can use it to release heap addresses automatically.  

  - `Status`  
     Functions which returns `Status` can be gracefully handled and examined for
     potential errors.  

Comming up, we have OOP support, as mentioned before:  
  - `Class`  
     You may create `Class` in C.  

About the `Class`, when you are creating one, you may write like this:  
```C
int main(void)
{
  class(PUBLIC, DYNAMIC, "BooleanSwitcher", {
    field(PRIVATE, DYNAMIC, TBool, "state");

    constructor(PUBLIC, {
      THIS->state = false;
    }, NULL, 0);

    constructor(PUBLIC, {
      THIS->state = state;
    }, "b", "state");

    method(PUBLIC, DYNAMIC, TVoid, "Toggle", {
      THIS->state = !(THIS->state);
    }, NULL, 0);

    method(PUBLIC, DYNAMIC, TBool, "GetState", {
      return THIS->state;
    }, NULL, 0);

    method(PUBLIC, DYNAMIC, TVoid, "SetState", {
      THIS->state = state;
    }, "b", "state");
  })

  return 0;
}
```
Yes, you may need to use macros to express quickly and gracefully.  

And with further development, implementing polymorphisms is possible.  

But for now, we're concentrating on solving the "Type Reflecting" system.
And if you happen to have such experiences, we sincerely welcome you to give us
a hand.  

## Building & Installing (GNU/Linux)
```shell
# You will have to install headers before building the project.
./preinstall   # May need root privilege.

cmake && make

# Then, you will also need to install freshly built library into your system.
./postinstall  # May need root privilege.
```

> We need installation instructions for MacOS and MS/Windows.

## Platform specifications  

Compound uses [LLVM/Clang](https://github.com/llvm/llvm-project) to compile, and
uses [CMake](https://github.com/Kitware/CMake) to build.  

As for MS/Windows building, we current need someone who's familiar with Windows
building system to write the responding `CMakeLists`.

In conclusion, Compound is now only tested on GNU/Linux, which runs just well.
As for MacOS, technically able to run as fine as well, with a little adjustment
on installation in addition, of course.

