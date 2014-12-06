// Fibonacci program.
n := 8;       // n-esim Fibonacci's number.
pred1 := 1;
pred2 := 1;
i := 2;
fib := 1;

if n > 2 then
  while i < n do
    fib := pred1 + pred2;
    pred2 := pred1;
    pred1 := fib;
    i := i + 1;
  end;
else
  skip;
end;

print fib;
