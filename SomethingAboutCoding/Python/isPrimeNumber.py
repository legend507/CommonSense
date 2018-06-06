def IsPrime(n):
  for divisor in range(2, n / 2):
    if n % divisor == 0:
      return False

  return True