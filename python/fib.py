"""

def fib2(n, a1=0, a2=1):
    if n == 0:
        return a1, 1  # 最初のコールもカウントするために1を返す
    elif n == 1:
        return a2, 1  # 最初のコールもカウントするために1を返す
    else:
        fib_value, call_count = fib2(n-1, a2, a1+a2)
        return fib_value, call_count + 1

def main():
    for i in range(0, 11):
        result, count = fib2(i)
        print('n=%d : %d call:%d' % (i, result, count))

main()

"""


def fib2(n, a1=0,a2=1):
    if n<1:
        return a1,1
    v, k=fib2(n-1,a2,a1+a2)
    return v,k+1

def main():
    for i in range(0,11):
        result,count=fib2(i)
        print('n=%d : %d call:%d'%(i,result,count))

main()

