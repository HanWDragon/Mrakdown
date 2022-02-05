# KMP算法解决的问题

字符串 `str1` 和 `str2 `，`str1`  是否包含 `str2`，如果包含返回 `str2` 在 `str1` 中开始的位置。 如何做到时间复杂度 $O(N)$ 完成?

**暴力解法**

就是将原先的字符串遍历，再逐一比对开头，再逐个比较

假如 `str1 = 1111111111112 str2 = 1112` 

那么对应的时间复杂度是  $O(M * N)$

# KMP算法的全部细节和实现讲解

**前提算法**

最长前缀后缀问题

就是给定一个字符串，匹配他它们前缀和后缀的最长字符串

但是长度要小于字符串长度

**如何实现**

`str1 i -> x-1 == str2 0 -> y-1`

当给出 `str2` 最长前缀和最长后缀的长度

那么在这个前缀和后缀之间不可能存在满足 `str2` 的字符串

就这样便可以跳过这一段字符串，进行加速

有了以上的前提，就可以进行开始算法设计了

**具体实现**

```java
package class03;

public class Code01_KMP {

    public static int getIndexOf(String s, String m) {
        if (s == null || m == null || m.length() < 1 || s.length() < m.length()) {
            return -1;
        }
        char[] str1 = s.toCharArray();
        char[] str2 = m.toCharArray();
        int i1 = 0;
        int i2 = 0;
        int[] next = getNextArray(str2);
        while (i1 < str1.length && i2 < str2.length) {
            if (str1[i1] == str2[i2]) {
                i1++;
                i2++;
            } else if (next[i2] == -1) {
                i1++;
            } else {
                i2 = next[i2];
            }
        }
        return i2 == str2.length ? i1 - i2 : -1;
    }

    //需要用到之前的信息，和KMP算算法的实现差不多
    //都用到了字符串的信息来加速
    public static int[] getNextArray(char[] ms) {
        if (ms.length == 1) {
            return new int[]{-1};
        }
        int[] next = new int[ms.length];
        next[0] = -1;
        next[1] = 0;
        int i = 2;
        int cn = 0;
        while (i < next.length) {
            if (ms[i - 1] == ms[cn]) {
                next[i++] = ++cn;
            } else if (cn > 0) {
                cn = next[cn];
            } else {
                next[i++] = 0;
            }
        }
        return next;
    }

    public static void main(String[] args) {
        String str = "abcabcababaccc";
        String match = "ababa";
        System.out.println(getIndexOf(str, match));

    }

}

```

# Manacher算法解决的问题

字符串 `str` 中，最长回文子串的长度如何求解? 如何做到时间复杂度 $O(N)$​ 完成?

**暴力解法**

就是经典的双指针算法

但是需要将原来的字符串插入一个标记（这个标记其实用啥都行）

`12211 -> #1#2#2#1#1#`就可以使用双指针

得到的结果除以二即可

# Manacher算法的全部细节和实现讲解

**算法前提**

需要了解回文半径和回文直径

**如何实现**

其实和KMP算法很像

因为都是从暴力解法到加速解法

都是在暴力解法的过程中进行加速

有了上面的回文半径和回文直径就可以开始算法设计了

**代码实现**

```java
package class03;

public class Code02_Manacher {

    public static char[] manacherString(String str) {
        char[] charArr = str.toCharArray();
        char[] res = new char[str.length() * 2 + 1];
        int index = 0;
        for (int i = 0; i != res.length; i++) {
            res[i] = (i & 1) == 0 ? '#' : charArr[index++];
        }
        return res;
    }

    public static int maxLcpsLength(String str) {
        if (str == null || str.length() == 0) {
            return 0;
        }
        //变为处理后的字符串
        char[] charArr = manacherString(str);
        //回文半径数组
        int[] pArr = new int[charArr.length];
        // 中心
        int C = -1;
        //回文右边界再向右一个位置 最右的有效区域为 R-1位置
        int R = -1;
        //扩出来的最大值
        int max = Integer.MIN_VALUE;
        //每一个位置都要求回文半径
        for (int i = 0; i != charArr.length; i++) {
            //至少不用检查的区域
            pArr[i] = R > i ? Math.min(pArr[2 * C - i], R - i) : 1;
           
            while (i + pArr[i] < charArr.length && i - pArr[i] > -1) {
                if (charArr[i + pArr[i]] == charArr[i - pArr[i]])
                    pArr[i]++;
                else {
                    break;
                }
            }
            if (i + pArr[i] > R) {
                R = i + pArr[i];
                C = i;
            }
            max = Math.max(max, pArr[i]);
        }
        return max - 1;
    }

    public static void main(String[] args) {
        String str1 = "abc1234321ab";
        System.out.println(maxLcpsLength(str1));
    }

}

```

