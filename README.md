# YOU NEED COMPOUND

Generally, Compound is a library for general-purposes programming which you will find essential for higher level of abstraction based on c.

It is worth noticing that, this library is completely aimed for creating another language. That means, every feature update is supposedly to serve the language.

---
## Building
```shell
cmake . && make
```

> *PLEASE NOTICE*  
> *Compound is originally designed for GNU/Linux and other Unix-like operating systems.*  
> *Support for MS Windows will be possible in the future.*

### Platform specifications
```C
/* Copied on Fri 10 May 16:24:09 CST 2024 */

# if defined __x86_64__ || defined __x86_64  // For 64-bits operating systems.
#  define __COMPOUND_64__
#  define __COMPOUND_PRODUCT__  compound64
# elif defined __i386__ || __i486__ || __i586__ || __i686__ || _X86_ || __X86__  // For 32-bits operating systems.
#  define __COMPOUND_32__
#  define __COMPOUND_PRODUCT__  compound32
# else
#  error Platform not supported.  Please issue this on github.com/Wilhelm-Lee/Compound  --William
# endif
```
Compound, now, roughly divides platform compatibilities into 2 major parts, the 64-bits and the 32-bits.  
This idea is ready for refinements, you can put up such suggestions and they're welcomed.  

## Installation
```shell
./preinstall  # (Require root privilege)
./postinstall  # (Require root privilege)
```

> *I TELL YOU WHAT*  
> *It is for the convenience of project building automation that the installation procedure being devided into two different parts.*  
> *In general, the "preinstall" copies the header files into system "include" directory,*  
> *while the "postinstall" copies the compiled library into system library directory.*


And if you cannot execute the scripts, try to add permission for execution:
```shell
chmod +x ./the_file_lacks_of_permission_to_execute_and_to_be_honest_i_dont_know_why_do_i_have_to_put_the_name_so_long_that_none_of_you_would_like_to_read_it_through_but_since_you_have_gotten_this_far_congrats_you_are_my_big_star_now_oh_by_the_way_do_you_know_that_the_cat_of_mine_can_actually_talk_cause_last_sunday_when_i_head_to_kitchen_for_some_drinks_and_i_heard_something_mumbling_behind_the_door_and_i_went_up_to_check_what_it_was_and_it_turns_out_that_it_was_my_cat_speaking_and_what_it_said_was_meow
```

## Troubleshoot
For now, we wish more of you to put up issues so that the problems can be spotted.

> *NOT SO FAST*  
> *If you got a problem, try to look up for similar or same issues that had been put up already,*  
> *'cause you don't want to have your reply simply written something like "ah yeah yeah, we've been through that sometime earlier".*
