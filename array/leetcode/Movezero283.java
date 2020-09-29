/**
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/move-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
public class Movezero283 {

  /**
  * 一个很直接的想法就是删除，但要在不改变数组长度前提下
  * 对于数组的删除操作，要想象成“空槽”处理，等待后面元素的填充
  */
  public void moveZeroes(int[] nums) {
    int slotStart = 0;
    for(int i = 0; i < nums.length; i++) {
        if(nums[i] != 0) {
            nums[slotStart++] = nums[i];
        }
    }
    for(int i = slotStart; i < nums.length; ++i) {
        nums[i] = 0;
    }
  }

}
