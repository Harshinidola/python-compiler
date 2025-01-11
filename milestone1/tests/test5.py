def fibonacci_sequence(n):
    fibonacci = [0, 1]
    while len(fibonacci) < n:
        next_fib = fibonacci[-1] + fibonacci[-2]
        fibonacci.append(next_fib)
    return fibonacci

def print_fibonacci_sequence(sequence):
    print("Fibonacci Sequence:")
    for num in sequence:
        print(num, end=" ")

def main():
    n = int(input("Enter the number of Fibonacci sequence elements to generate: "))
    sequence = fibonacci_sequence(n)
    print_fibonacci_sequence(sequence)

if __name__ == "__main__":
    main()

