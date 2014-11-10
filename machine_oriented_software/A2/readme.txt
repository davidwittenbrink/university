A2a Sorted linked list implementation 
by Amel Hamidovic and David Wittenbrink

Our sorted linked list implementation works in the following way:
When calling `sorted_list_create` a new 'header' element is created
and a pointer to it returned.

When adding an integer to the list through `sorted_list_add`,
we start to go through our list, looping from one element to the other
using the next attribute of a list element. We find the first element
that stores an integer bigger than ours and add our element before it.
In case we reach the end of our list, we add the new element after it.
In case of the list containing nothing but the header element, we add
the new element after the header and change the pointer pointing to
the first element of the list.

When `sorted_list_remove` is called, we loop through our list from the
first element while keeping track of the number of times we switched
to the next element. Once this number is as high as the index parameter,
we remove the element and modify the previous attribute of the next element
and the next attribute of the previous element. If we delete an element at
index 0, we also change the pointer pointing to the first element of the
list. If the index is out of range of our list, we do nothing and return.

`sorted_list_destroy` starts by destroying the header element, then goes
through each element and frees it's memory.


A2b

The implementation of this assignment is fairly straight forward.
The `for_all` function takes as parameters a pointer to an array,
the length of the list and a pointer to a function that takes an
int as a parameter and returns an integer.
`for_all` then goes through each element of the array, calls
the function given by the parameter, and overwrites the element
with the returned value.

`is_any` also takes an array, it's length and a function taking
and returning an integer. The function then loops through the
array, checks if the given function (through the pointer) returns
1. If it does, `is_any` returns 1. If the whole loop is cycled
through and the given function never returned 1, we return 0.