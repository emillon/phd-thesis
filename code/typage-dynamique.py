>>> a = 3
>>> b = 2
>>> c = 4.5
>>> type(a)
<type 'int'>
>>> type(b)
<type 'int'>
>>> a+b
5
>>> type(a+b)
<type 'int'>
>>> a+c
7.5
>>> type(a+c)
<type 'float'>
>>> def d(x):
...     return 2*x
... 
>>> type(d)
<type 'function'>
>>> d(2)
4
>>> type(d(2))
<type 'int'>
>>> a+d
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: unsupported operand type(s) for +: 'int' and 'function'
