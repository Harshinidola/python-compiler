def calculate_power(base, exponent):
  result = 1
  for _ in range(exponent):
    result *= base
  return result

def main():
  base = float(input("Enter the base number: "))
  exponent = int(input("Enter the exponent: "))
  result = calculate_power(base, exponent)
  print("The result of", base, "raised to the power of", exponent, "is:", result)

if __name__ == "__main__":
  main()

