# Assumes gcd(a, b) = 1, with a as the mod and b as the target

# Test values
# a = 31
# b = 7

a = pow(2, 64)
b = 212103456793011

m = a # for mod purposes


q = (int) (a / b)
r = a % b
s1 = 1
s2 = 0
s3 = s1 - (q * s2)
t1 = 0
t2 = 1
t3 = t1 - (q * t2)

while r != 0:
    a = b
    b = r
    q = (int) (a / b)
    r = a % b
    s1 = s2
    s2 = s3
    s3 = s1 - (q * s2)
    t1 = t2
    t2 = t3
    t3 = t1 - (q * t2)

print(t2 if t2 > 0 else t2 - m)
