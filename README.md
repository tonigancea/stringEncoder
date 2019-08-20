# stringEncoder

## Introduction
This was my first major C project I worked on. Also the first major programing homework in college. The main purpose was to learn how to work with pointers and to get used with the C syntax.

## Behavior
This program encodes an input received from `stdin`. 

This input has one *term* on each line. The input ends with `"END"` string. This is how the program knows where does the input end. There are three types of *terms*:
* words
* characters
* numbers

Each term has its own encoding rule, as following:
* Encoding rule for **words**: Let there be `l`, the length of the word and let there be `d`, the biggest divisor of `l`, with `d ≠ l`. (example: if `l = 21` then `d = 7` or if `l = 28` then `d = 14`) The first `d` characters will be moved at the end of the word. If the word hasn't any figure (0, 1, 2...) inside it, the rest of the characters from the initial word (`l-d`) will remain unchanged. On the other case, if the word has at least a figure inside it, the rest of the characters will be reversed.

* Encoding rule for **characters**: Let there be `x`, the character we have to encode, `p` the most popular character we parsed so far (including the words and the numbers) and `u` the least popular character we parsed so far. The final encoding for `x` is the concatenation of `p`, `x` and `u`, in this order. If we haven't parsed anything so far, `p` and `u` are *the empty string*.

* Encoding rule for **numbers**: If the number is `>0`, the number will be cyclically rotated until the maximum is found. If the number is `<0`, the absolute value will be extracted and the number will be cyclically rotated until the minimum is found. 

Each term is encoded using its own rule and the output is added to the final string. But this string will be encoded once more. We will call it `tempString`.

Let there be `n`, the number of encoded terms. `tempString` will be splited in `n` equal components. If `tempString` doesn't split into equal components, the remaining characters will be part of the last component.

Then, the complexity for each component will be computed. All the components will be reallocated in descending order by complexity. The complexity of a component is the *mean* of the ASCII code of each character from that component.

Having this array of components, the final string will be the concatenation of the components from the following indexes: `0`, `n-1`, `1`, `n-2`, etc. Let's call this string `finalString`.

## Final output:
`number_of_word_terms` `number_of_character_terms` `number_of_number_terms`

`tempString`

`finalString`
