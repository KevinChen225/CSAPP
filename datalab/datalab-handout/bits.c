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
  int result = ~(~(x&~(x&y))&~(y&~(x&y))); 
  //x XOR y = (x NAND (x NAND y)) NAND (y NAND (x NAND y))
  //共4個 NAND
  //x NAND y = NOT (x AND y)
  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int result = 0x1 << 31; //-2^(31)
  return result;
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
  int result = !((~(x + 1)^x)|!(x+1));
  //假設x為INT_MAX，INT_MAX + 1是INT_MIN所以~(x + 1)是True，因為不能用==所以用XOR的NOT作判斷
  //得到!(~(x + 1)^x)，但如果x是-1(11111111 11111111 11111111 11111111)
  //x + 1會全部為0，這樣結果!0也會回傳1，所以用右邊!(x+1)得到1避免誤判
  return result;
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
  int a = 0xAA; //9xAA = 10101010奇數位為1，32bit = 0xAAAAAAAA
  a = a + (a << 8);
  a = a + (a << 16);  //0xAAAAAAAA
  int result = !((a&x)^a);  //0xAAAAAAAA跟x做AND後再做XOR如果和a一樣就為0，return !0
  return result;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
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
  // 0 = 110000  1 = 110001.. 9 = 111001
  int a = x >> 6; //前26位必須是0
  int cond1 = !a; //要得到1
  int b = x >> 4; //過濾後面六位 11xxxx
  int cond2 = !(b ^ 0b11); //要得到1
  int c = x & 0b1111; //對後四位過濾
  int result = c + (~0b1010 + 1);  //做c - 0xA要< 0但不能用負號所以用2的補數
  int cond3 = result >> 31 & 1;  //如果res是負的arithmetic right shift會補1，反之則補0，再和1做AND
  return cond1 & cond2 & cond3;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  //!0 return y 0 return z
  int a = !!x;  //x非0都轉成1
  int mask = ~a + 1;  //得到全是1或0的mask
  return (mask & y)|(~mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //先比x的sign bit跟y的sign bit
    int signx = (x >> 31) & 1;
    int signy = (y >> 31) & 1;
    int signdiff = signx ^ signy; //如果bit相同為0不同為1
    int diff = x + (~y + 1);  //x - y,~y + 1為-y
    int sd = (diff >> 31) & 1;  //取diff的sign bit,如果為1代表x < y
    int equal = !(x ^ y); //兩數相同的情況 相同為1不同為0
    int cond1 = (signdiff & signx); //x跟y不同號的情況
    //e.g. x = -3,y = 5:
    //signx = 1,signy = 0,signdiff = 1,cond1 = 1
    int cond2 = signdiff ^ 1; //x跟y同號的情況XOR會為1
    int cond3 = sd | equal; //基於同號的前提，x < y 或 x == y，也就是 x <= y
    return cond1 | (cond2 & cond3);
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
  //x非 0，x 和 -x 至少有一個是負數
  //e.g. 0101 = 5 1011 = -5
  int a = ~x + 1; // -x
  int signbit = (a | x) >> 31; // x = 0得0，非0得-1 
  //a OR x的 sign bit為1時右移31個bit補1得到 -> (11111111 11111111 11111111 11111111) = -1
  return signbit + 1;
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
  // 不管正數還是負數先找 highest bit 是 0 或 1s e.g. 12 -> 01100,-5 -> 1011
  int flag = x >> 31;
  // 假設正數(12) 00000000 00000000 00000000 00001100 右移 31 bits 得到 00000000 00000000 00000000 00000000 flag = 0
  //    負數(-5) 11111111 11111111 11111111 11111011 右移 31 bits 得到 11111111 11111111 11111111 11111111 flag = -1
  // 如果負數找最高的 1 那永遠會是 bit 31 ，所以要取反，但正數則不影響
  x = ((~flag) & x) | (flag & (~x));  
  // 表示正數不變，負數取反 e.g. x為正，flag = 0...000 (~flag) & x 一定是x，flag & (~x) 則為0
  // x為負 flag = 1...111 (~flag) & x 為 0 flag & (~x) 則為 ~x

  int bit_16, bit_8, bit_4, bit_2, bit_1, bit_0;

  // 用binary search的方式檢查 highest bit 在哪裡  16 -> 8 -> 4 -> 2 -> 1 -> 0
  //           32 bits
  // [ 高 16 bits ][ 低 16 bits ]
  int a = !!(x >> 16);

  // 切一半 e.g. 00000000 00000100 | 00000000 00000000
  // 變成        00000000 00000000 | 00000000 00000100
  // 高 16 bits 全是 0 -> 0
  // 高 16 bits 有 1  -> 1
  // !!0 = 0，!!非0 = 1

  bit_16 = a << 4;  // 假設 高 16 bit 為 1 那 1 << 4 = 16 ，把 16 這個數字記起來 
  x = x >> bit_16;  // bit_16 只可能是 0 或 16
  // 如果是 0  則 x = x >> 0 不變
  // 如果是 16 則 x = x >> 16 相當於捨棄後面十六位，把高16位搬到低十六位繼續做 search
  // e.g. x = 00000000 00000101 | 10101010 11110000 高 16 bits 有 1
  // x >> 16  00000000 00000000 | 00000000 00000101

  // 接著繼續做
  bit_8 = !!(x >> 8) << 3;
  x = x >> bit_8;

  bit_4 = !!(x >> 4) << 2;
  x = x >> bit_4;

  bit_2 = !!(x >> 2) << 1;
  x = x >> bit_2;

  // 已經是 0 或 1，不用再左移
  bit_1 = !!(x >> 1);
  x = x >> bit_1;

  // 最後剩下的 x 只會是 0 或 1
  bit_0 = x;

  return bit_16 + bit_8 + bit_4 + bit_2 + bit_1 + bit_0 + 1; // 1為 sign bit
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
  // [ sign ][ exponent ][ fraction ]
  //    1         8           23
  // 1 sign bit 8 exponent bit 23 fraction bit，exp = E + 127
  // 取最高位
  unsigned signBit = (uf >> 31) & 1;

  // 取中間 8 bit
  unsigned exp = ((uf >> 23) & 0xFF);

  // 取右邊 23 bit
  unsigned frac = uf & 0x7FFFFF;

  // NaN
  if(exp == 0xFF)
    return uf;
  
  // uf = 0
  if(exp == 0 && frac == 0)
    return uf;

  // denormalize 
  if(exp == 0 && frac != 0){
    frac = frac << 1; // *2
    return (signBit << 31) | frac;
  }
  // 避免把 overflow 錯誤做成 NaN，確保結果是 inf
  if(exp == 0xFE) {
      return (signBit << 31) | (0xFF << 23);
  }
  // normalize
  exp++;
  return (signBit << 31) | (exp << 23) | frac;
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
  // 取最高位
  unsigned signBit = (uf >> 31) & 1;

  // 取中間 8 bit
  unsigned exp = ((uf >> 23) & 0xFF);

  // 取右邊 23 bit
  unsigned frac = uf & 0x7FFFFF;

  // exp 是 unsigned，轉成 int 好點
  int E = (int)exp - 127;
  
  // uf = 0
  if(exp == 0 && frac == 0)
    return 0;
  
  // NaN 或 Inf
  if(exp == 0xFF)
    return 1 << 31; // 0x80000000
  
  // frac 變回去，把隱藏的 1 補回來 
  // e.g. 1.101 實際儲存的地方只有101...
  frac = (frac | (1 << 23));

  // 如果 E < 0 代表這個數字一定 < 1，轉 int 會直接切掉小數
  if(E < 0)
    return 0;
  
  // 代表結果超過 int 能表示的範圍，返回 0x80000000u
  if(E >= 31)
    return 1u << 31;
  // ============================================
    // 情況 1：E < 23
    // ============================================
    //
    // 例如 E = 2：
    //
    // float：
    //
    //     1.101 × 2^2
    //
    // 小數點右移 2 格：
    //
    //     110.1
    //
    // 轉 int：
    //
    //     110₂ = 6
    //
    //
    // 但是 frac 在程式裡其實長這樣：
    //
    //     110100000000000000000000
    //        ↑
    //        後面還有很多 fraction bits
    //
    // frac 原本有 23 個小數 bits，
    // 但 E = 2 代表只有前面 2 個 bits 移到小數點左邊。
    //
    // 所以還剩：
    //
    //     23 - 2 = 21
    //
    // 個 bits 要丟掉。
    //
    // 因此右移 21：
    //
    //     frac >>= 21;
    //
    // 最後剩：
    //
    //     110₂ = 6
    //
    if (E < 23) {
        frac >>= (23 - E);
    }


    // ============================================
    // 情況 2：E == 23
    // ============================================
    //
    // 例如：
    //
    //     1.101 × 2^23
    //
    // frac 本來就有 23 個 fraction bits。
    //
    // 現在 × 2^23，
    // 剛好把小數點完整移過這 23 個 bits。
    //
    // 所以：
    //
    //     E - 23 = 0
    //
    // 等於：
    //
    //     frac <<= 0;
    //
    // 完全不用移動。
    //
    //
    // ============================================
    // 情況 3：E > 23
    // ============================================
    //
    // 例如 E = 25：
    //
    //     1.101 × 2^25
    //
    // frac 只有 23 個 fraction bits，
    // 但是現在要把小數點往右移 25 格。
    //
    // 已經移完原本的 23 格後，
    // 還差：
    //
    //     25 - 23 = 2
    //
    // 格。
    //
    // 所以要在右邊補兩個 0，
    // 也就是左移 2：
    //
    //     frac <<= 2;
    //
    else {
        frac <<= (E - 23);
    }
    // 如果負的返回 2 的補數
    if(signBit){
      return ~frac + 1;
    }
    return frac;
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
  // 最小 normal 是 0.00000000000000000000001 × 2^-126 
  // 0.00000000000000000000001 = 2^-23
  // 2^(-23 - 126) = 2^-149
  if(x < -149)
    return 0;
  // normal number 最小的 exponent bits 是 00000001 也就是 1
  // 真正的 exponent E = 1 - 127 = -126
  // 而 normal number 最大的 exponent bits 是 11111110 也就是 254
  // 真正的 exponent E = 254 - 127 = 127

  //denormal
  if(x < -126){
        return 1u << (x + 149);
    }
  //normal
  if(x <= 127){
        return (x + 127) << 23;
    }
  // Inf
  return 0xFFu << 23;
}
