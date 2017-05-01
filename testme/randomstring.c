Zachary Prive Shereck

Quiz 2 Submission

I first looked at what exactly the testme function was checking for. Noticing that the range of characters checked against c
was limited, I only randomly generated characters within an ASCII range that included those characters. I wanted to reduce the runtime of
testme while still randomly generating the characters.

For inputString, generating a random sized string would make the runtime incredibly long and there would be a very low possibility of
actually getting "reset", considering that the string would have to randomly generate a length of 6 AND randomly be set to "reset".
To save my computer and my time, I shortened the possible size to 6 with the last value being a null terminator, since that was the
last argument in the check against "s".

I think the output is a little sloppy, since it prints everything out on every iteration, but I don't really see a better way of giving
the user information without missing some cases. I also added more information to the error message and a new line for better readability.
