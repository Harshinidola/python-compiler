def is_prime(n):
  if n <= 1:
    return False
  elif n <= 3:
    return True
  elif n % 2 == 0 or n % 3 == 0:
    return False
  i = 5
  while i * i <= n:
    if n % i == 0 or n % (i + 2) == 0:
      return False
    i += 6
  return True

def generate_primes(limit):
  primes = [2, 3]
  num = 5
  while num <= limit:
    if is_prime(num):
      primes.append(num)
    num += 2
  return primes

def main():
  limit = int(input("Enter the limit: "))
  prime_list = generate_primes(limit)
  print("Prime numbers up to", limit, "are:")
  print(prime_list)

if __name__ == "__main__":
  main()

