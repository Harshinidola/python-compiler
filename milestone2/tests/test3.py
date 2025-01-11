def calculate_power(base:int, exponent:int)->int:
  result:int = 1
  for _ in range(exponent):
    result *= base
  return result

def main():
  base:int = 2
  exponent:int =4
  result:int = calculate_power(base, exponent)
  print("The result of", base, "raised to the power of", exponent, "is:", result)

if __name__ == "__main__":
  main()

