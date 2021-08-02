/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(x & ~y) & ~(~x & y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // TMIN is 1000...0000, so we just need 0000...0001, and left shift this number 31 bits
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int tmp = x + 1; // if x is TMAX, so tmp will be TMIN (1000...0000)
  x = tmp + x; // if tmp is TMIN, then x will be -1 (1111...1111)
  x = ~x; // if x is -1, then x will be 0 (0000...0000)
  /* if we just return !x, we will get error, because we forget one condition
   * if x is 0xFFFFFFFF, tmp will be 0 (because truncate), and step2: x will be 1111...1111
   * and then in step3, x = ~x, x will be 0 too, but 0xFFFFFFFF is not TMAX, so it will get an error
   */
  // so we need to avoid this special situation
  tmp = !tmp; // here if x is 0xFFFFFFFF, and tmp is 0, so tmp will be 0x01
  x = x + tmp; // so that here if tmp is 1, represent the situation that x is 0xFFFFFFFF, x will be 0 + 0x01 here
  // the two lines above can avoid the situation that x is 0xFFFFFFFF
  return !x; 
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // first we need to contruct a number which is 0xAAAAAAAA
  int odd = 0xAA;
  odd = (odd << 24) + (odd << 16) + (odd << 8) + odd;
  // next if all odd-numbered bits in x are set to 1, so odd & x will be odd, otherwise, it will not equal to odd
  // then we just need to compare whether odd & x is equal to odd, we can use xor here
  return !((odd & x) ^ odd);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* x - 0x30 >= 0 && 0x39 - x >= 0 */
  int TMIN = 1 << 31;
  // here -x = ~x + 1, so we can represent the expression above, and use &TMIN to test whether negative or not
  // if both of them are possitive, then return 1, else return 0
  return !(((x + ~0x30 + 1) & TMIN) | ((0x39 + ~x + 1) & TMIN));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int a = ~(!x) + 1; // if x is 0, a is 1111...1111; else if x is not 0, a is 0
  int b = ~a;
  return (a & z) + (b & y);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* x <= y --> y - x >= 0 --> y + ~x + 1 >= 0 --> ((y + ~x + 1) >> 31) & 1 == 0
   * and if x <= 0 && y >= 0, always return 1, so we need judge the sign bit of x and y
   * because we will have a special condition, that x is 0x80000000 and y is 0x7FFFFFFF
   * if we just use comment line1, we will get an error, because if x is 0x80000000
   * and if x is TMIN,  ~TMIN + 1 == TMIN, so thats why we need line2 to avoid this error
   * and we also need to think about contrary contidion that x is 0x7FFFFFFF and y is 0x80000000
   * so x is TMAX, and y is TMIN, y - x will overflow, here y - x == 1, but actually x is bigger than y
   * so it will happen another error, so we need to take another measure to solve it
   * so we add a statement "!(signX ^ signY)" to ensure that x and y have the same sign bit
   * so we can avoid the situation that y <= 0 && x >= 0, so we can avoid above error
   */
  int signX = (x >> 31) & 1;
  int signY = (y >> 31) & 1;
  int signZ = ((y + ~x + 1) >> 31) & 1;
  return (signX & ~signY) | (!(signX ^ signY) & !signZ);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /* 
   * we just need think about the special number 0, represent in bit form is 0000...0000
   * so if a positive number, we use '-', it will be a negative number, but -0 will not change
   * so using the above characteristics
   */
  int negx = ~x + 1;
  // and here we can't use the way that : ~((x | negx) >> 31 & 1), is false
  return ~(x | negx) >> 31 & 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /*
   * x's two's complement expression is : b_31,b_30,...,b_1,b_0 
   * so if we just need n bits to represent it, it will be: b_n-1,b_n-2,...,b_1,b_0
   * so we will find that b_y ^ b_y+1 = 0 (for y >= n), and b_n ^ b_n-1 = 1
   * And then we need classified discussion, one is x is a positive number, another is x is negative
   * 用中文表达
   * 首先我们要知道不管一个数是正的还是负的，如果这个数的二进制表示高位有连续的一串0或者1，将这连续的一串数字消去
   * 得到的新的数字和原来的二进制表示的数字值是相同的，正数不必多说，因为都是0，所以消去前导连续的0当然没有影响
   * 对于负数而言，通过公式推导和对负数计算特性的理解，也可以得出去除前导连续1也不会改变值
   * 1.如果x是正数，那么我们只需要从高位到低位找到第一个1出现的位置，但是因为x是正数，所以我们还需要在这个1的前面添加一位符号位0
   * 2.如果x是负数，那么我们需要从高位到低位找到第一个0出现的位置，同样的要在0前面加上一个符号位1
   *  因为111111010和1010的值是一样的，由负数的特性可以知道负数二进制表示中前面连续的1都可以消去，结果得到的值不改变(保证留一个1做符号位)
   * 所以由上述英文描述的，可得如果我们这样操作：x ^= (x << 1)，那么对正数我们只需要找到新的x中的第一个1，对负数我们也只需要找到新的x中的第一个1
   * 所以如何找到一个二进制数字中的第一个1呢？
   * 我们可以通过二分来查找，选一个1111...1111的序列m，(m << 16) & x，就可以得出x的高16位是否有1，如果有则查找前面的16位
   * 没有则查找后面的16位，直到待查找序列只有一位结束
   */
  int n = 0, m = ~0;
  x ^= (x << 1);
  n += (!!((m << (n + 16)) & x)) << 4;
  n += (!!((m << (n + 8)) & x)) << 3;
  n += (!!((m << (n + 4)) & x)) << 2;
  n += (!!((m << (n + 2)) & x)) << 1;
  n += (!!((m << (n + 1)) & x)) << 0;
  return n + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exp = (uf >> 23) & 0xFF;
  // Special(NaN)
  if (exp == 0xFF) 
    return uf;
  // Denormalized
  if (exp == 0)
    return ((uf & 0x007FFFFF) << 1) | (uf & (1 << 31)); // take the frac bits left shift and don't forget add the sign bit
  // Normalized
  // here we just need add 1 on the exp bits
  return uf + (1 << 23);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int bais = 127;
  int TMIN = 1 << 31;
  int exp = (uf >> 23) & 0xFF;
  int E = exp - bais;
  if (E < 0) // if origianl exp == 0, must be 0
    return 0;
  if (E > 31)
    return TMIN;
  int frac = (uf & 0x007FFFFF) | 0x00800000; // add the 1 we hide
  /*
   * 我们现在获得了1.frac这样一个二进制小数的表示
   * 这时候要1.frac * 2^E，就代表将小数点右移E位，那么frac总共23位，如果E小于23
   * 那么右移小数点的操作等同于将1xxxx(xxxx为frac的二进制表示)右移23-E位，等同于截断小数点右边的位
   * 如果E大于23，那么就等同于将1xxxx左移E-23位
   */ 
  int f = (E > 23) ? (frac << (E - 23)) : (frac >> (23 - E));
  return uf & TMIN ? -f : f;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    // x is E
    int bais = 127;
    int exp = x + bais;
    if (exp <= 0)
      return 0;
    if (exp >= 0xFF)
      return 0x7F800000; // 0x7F800000 is 0|11111111|00000000000000000000000(means +INF in float)
    return exp << 23; // because we need a float representation
}
