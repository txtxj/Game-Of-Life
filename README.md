# Game-Of-Life

生命游戏

已完成：

 - 支持自定义输入规则
 - 随机依概率生成初始细胞（调用 `randomize` 函数）
 - 鼠标点击生成/消灭细胞

TODO:
 - 范围选取

操作：
 - Enter 键进入下一张
 - 鼠标点击生成/消灭细胞
 - 空格暂停/自动播放

可供修改的各种参数：
 - `col * rows` 行列（不要问咱哪个是行哪个是列，咱也不知道）
 - `coef` 放大系数（感觉不应该起名叫 `coef` ）
 - `rule` 规则，输入形如 `"BxxSxx"` 的字符串，其中 `x` 为一位十进制数字
 - `fore_color` 细胞颜色
 - `back_color` 背景颜色
 - `pr` 随机生成细胞时的概率

其他参数，正常使用应该是不需要修改的。
