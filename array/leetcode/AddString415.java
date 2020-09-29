/**
给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。

提示：

num1 和num2 的长度都小于 5100
num1 和num2 都只包含数字 0-9
num1 和num2 都不包含任何前导零
你不能使用任何內建 BigInteger 库， 也不能直接将输入的字符串转换为整数形式

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-strings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
public class AddString415 {

  /**
  * 字符减法操作快速求偏移
  * 参考代码模板
  */
  public String addStrings(String num1, String num2) {
      char[] charNum1 = num1.toCharArray();
      char[] charNum2 = num2.toCharArray();
      int carrier = 0; // 进位
      StringBuilder ans = new StringBuilder();
      int i = charNum1.length - 1;
      int j = charNum2.length - 1;
      while( i >= 0 || j >= 0 || carrier > 0) {
          int x = i < 0 ? 0 : charNum1[i--] - '0';
          int y = j < 0 ? 0 : charNum2[j--] - '0';
          int sum = x + y + carrier;
          carrier = sum / 10;
          ans.append(sum % 10);
      }
      return ans.reverse().toString();
  }

}
