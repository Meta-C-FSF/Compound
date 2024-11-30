# PREFIX

Compound supports that, under any `variadic context`, the macro `prefix` could  
be used for identifying and filtering prefixes before identical symbol, such as  
`d` for `integer`, `u` for `unsigned integer` and `s` for `string`.  

As for Compound-specific support, `$` is used to distinguish from traditional  
prefixes used in C.  Normally, when using `$` as prefix, the possible followings  
has to be quoted by braces.  

> Note  
> The `$` is not compatible with handling traditional symbols, e.g. `d`, `lu` etc.

<!-- Here's a partial mapping.  
```
 Prefix      Meaning
 c           char
 d           signed integer
 ld          long signed integer
 lld         long long signed integer
 
``` -->

Basically, those objects will be `literalised` before writting to given buffer.

Please note that, the item within `{}` is basically Compound objects, or,  
"struct objects" like `Array` from `<Compound/array.h>` and `Class` from  
`<Compound/class.h>`.  

The `$` prefix can also be used for identifying actual heap classes, created  
with `Class_Create` function by appending `#` after `$` and before `{`.  
Something like `$#{Foo}` `$#{Bar}`.  

One thing about heap classes, is that you don't have to write the instance in  
parameters, since it doesn't exist before runtime.

Something like this.
```C
Array arr = EMPTY;
format("%d %ld ${Array} $#{Array}", 1, 100, arr);
```

Also, just like Compound objects, the specified class will be `literalised`  
before writting into buffer.  But as a class, user can `override` their methods,  
which allows to "reformat" the literalisation.

> Note  
> To type `$` individually, write `$$` to indicate the mean without translation.  
