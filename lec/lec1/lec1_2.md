# Introduction to C: memroy and the compiler / Subtleties of C

## **pointer**

### How do you get at this information about memory?

- Through pointer;

- & and * operators

```cpp
int a = 5;
int *ptra = &a;
```

read declarations from right to left( *ptra is declared to be of type int )

apply & to any addressable value ("lvalue")

```cpp
return &5;
// error: lvalue required as unary '&' operand
```

## **speed**

1. C is focused on speed -> always checking arr bounds/memory access would slow you down;

2. simple typo below, can cause corruption;

```cpp
for (int i = 0; i <= N; i++) {}
```

3. memory corruption can cause totally unexpected, hard to debug behavior at worst; at best: segmentation fault(core dumped);

## **memory**

> “I promise to always free each chunk of memory that I allocate.” Don’t be the cause of memory leaks! It’s a bad practice.

## **array indexing**

C doesn't know what an array is.

T array[] and T *array are both pointers to a contiguous chunks of memory.

```cpp
int array[10];
// Initialize
for( int i = 0; i < 10; ++i ) {
  array[i] = i;
}
// Does the exact same thing as above
for( int i = 0; i < 10; ++i ) {
  *( array + i ) = i;
}
```

## **float point**

$$
x = (-1)^\text{sign} \cdot (1 . m_{22} m_{21} m_{20} \ldots m_0) \cdot 2^{e - \text{bias}}
$$

where bias is, in our case, 127;

![32bit fl](../../src/Screen%20Shot%202020-05-02%20at%2011.35.41%20am.png)

- sign = 0, m21 = 1, e = 124;

- pow = e - bias = -3; 2^(-3) = 0.125;

- franction = 2^(-m21m22) = 2^(-2) = 0.25;

![64bit double](../../src/Screen%20Shot%202020-05-02%20at%2011.35.48%20am.png)