# Tribonacci Series in python
# nth tribonacci number

def nthTribonacci(n):
    if(n==0 or n==1):
        return 0
    if(n==2):
        return 1
    
    return nthTribonacci(n-1)+nthTribonacci(n-2)+nthTribonacci(n-3)

n = 1000
nthTribonacciNumber = nthTribonacci(n)
print(f'The {n}th Tribonacci Number is:',nthTribonacciNumber)