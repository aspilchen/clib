### Dynamic Arrays

## dynarr
A generic dynamic array that still needs some work. Would like to make it thread safe with atomics.
Uses a void pointer and some information provided by the user to calculate heap memory details.
Uses memcpy to copy data to and from the array.

## dynarrExperiment
This is just me having some fun trying to use compiler tricks to create a generic, dynamic array
with an easy to use interface. The user has to follow instructions for gaurding against multiple
definitions of the same object. But overall it seems to work nicely.

## Extra notes
I will work on making a better page and documentation over time.