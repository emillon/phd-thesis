def f(b):
    x = None
    r = None
    if b:
        x = 1
    else:
        x = lambda y: y + 1
    b = not b
    if b:
        r = x (1)
    else:
        r = x + 1
    return r
