def calculate_area(radius):
  return 3.14 * radius * radius

def calculate_circumference(radius):
  return 2 * 3.14 * radius

def main():
  radius = float(input("Enter the radius of the circle: "))
  area = calculate_area(radius)
  circumference = calculate_circumference(radius)
  print("The area of the circle with radius", radius, "is:", area)
  print("The circumference of the circle with radius", radius, "is:", circumference)

if __name__ == "__main__":
  main()

