# Push-swap
42 Barcelona
Push_swap 是 42 Barcelona Common Core 项目中非常经典的一个算法项目。

这个项目的核心在于：用最少的步数，通过特定的指令集，将无序的数据排序。

作为你的搭档，我将把这份冗长的 PDF 拆解为可执行的开发计划。

1. 一句话总结
你需要编写一个 C 程序 push_swap，接收一串随机整数，利用仅有的 11 条栈操作指令，计算出并输出能将这串数字按升序排列的最短指令序列。

2. 项目目标
根据 PDF (Chapter IV & V)，你的项目必须达成以下具体目标：

*   核心程序 (push_swap)：
    *   输入：命令行参数，即一组互不相同的整数（例如 ./push_swap 3 1 2）。
    *   处理：计算如何通过 sa, sb, pa, pb, ra, rb, rra, rrb 等指令将 Stack A 从小到大排序。
    *   输出：打印出指令列表（每条指令占一行），使得 Stack A 最终有序，且 Stack B 为空。
    *   限制：必须处理错误输入（重复、非整数、溢出），且不能有内存泄漏。
*   加分程序 (checker) (建议先做完核心再做这个)：
    *   接收同样的数字，然后读取你从终端输入的指令，执行后判断 Stack A 是否已排序。

3. 核心思路
PDF 提到“选择最合适的算法”，这暗示了没有唯一的标准答案，但有优劣之分。

*   为什么难？ 因为你不能直接用 qsort。你只有两个栈（Stack A 和 Stack B）和有限的指令（交换、旋转、推入/推出）。
*   策略选择：
    *   暴力法 (Brute Force)：仅适用于极小规模（如 3-5 个数），通过递归尝试所有可能的指令组合。
    *   逻辑分类法 (Recommended)：这是处理大规模数据（100 或 500 个数）的稳妥方案。
        1.  初始化：所有数字都在 Stack A。
        2.  分块/分类：将 Stack A 中的数字按大小分组（例如，把较小的数移到 Stack B，把大的留在 A）。
        3.  归位：将 Stack B 中的数字按顺序“推”回 Stack A 的正确位置。
        4.  微调：使用旋转 (ra/rb) 和反向旋转 (rra/rrb) 来最小化移动步数。

4. 具体步骤 (实现顺序)
建议严格按照此顺序开发，避免返工：

1.  基础建设：创建 Makefile（必须包含 all, clean, fclean, re），建立符合 Norm 的 C 项目结构。
2.  数据结构：定义 t_stack 结构体（通常包含 int value, int index, struct s_stack *next）。实现栈的初始化和销毁。
3.  指令实现：先写好 sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr 这些函数。确保它们能正确修改链表并打印指令名。
4.  解析与校验：实现 main 函数的参数解析。必须检查：
    *   是否为有效整数（int 范围内）。
    *   是否有重复值 (PDF V.1 明确指出不能有重复)。
    *   错误时打印 "Errorn" 到 stderr 并退出。
5.  排序算法 (核心)：
    *   先实现一个简单的版本（如：将所有元素 pb 到 B，排序 B，再 pa 回 A）。
    *   再优化步数（例如：使用“三路快排”思想或“位排序”思想来减少指令数量）。
6.  Checker (Bonus)：读取指令行，模拟执行，最后检查栈是否有序。

5. 代码建议
*   数据结构：强烈建议使用循环双向链表或者带索引的单向链表。
    *   索引(Indexing)：在排序前，先给每个数字分配一个排名（例如最小的数 index=0，次小的 index=1）。这样排序时你只需要检查 index 是否按顺序，而不是原始的 value。
*   算法推荐：
    *   小数据 (< 100)：可以使用简单的插入排序变体。
    *   大数据 (100/500)：推荐使用 Radix Sort (基数排序) 的逻辑。因为基数排序在 Push_swap 中非常容易通过位移操作实现，且步数通常较少，容易通过评分标准（PDF V.3 提到步数限制）。

6. 测试方法
PDF 提到了一个 checker 二进制文件用于验证。
*   自动化测试：
        # 生成随机数并运行你的程序，将指令传给 checker
    ARG="4 67 3 87 23"; ./push_swap ARG | ./checker_OS ARG
    
*   预期结果：
    *   如果你的 push_swap 输出的指令正确，checker 会输出 OK。
    *   如果输出 KO 或步数超限，你的项目得分为 0。

7. 常见错误 (坑点)
根据 PDF 和过往经验，这些地方最容易丢分：

1.  内存泄漏 (Leaks)：PDF Chapter IV 明确规定“No leaks will be tolerated”。必须确保 malloc 了就必须 free。在程序结束前，释放所有链表节点。
2.  错误处理不全：
    *   忘记检查 int 溢出（例如输入 "2147483648" 或 "-2147483649"）。
    *   忘记检查重复数字。
    *   错误信息必须输出到 stderr，且必须包含换行符。
3.  指令步数过多：对于 100 个数字，如果步数超过几百步（具体限制由学校定），会被判 0 分。简单的冒泡排序逻辑在这里会超时，必须用更优的算法（如基数排序）。
4.  边界情况：
    *   空参数（./push_swap）：应直接退出，不输出任何内容。
    *   单个参数：已经是有序的，不应输出任何指令。

先帮你把 Makefile 和 main 的骨架搭起来，重点解决参数解析和去重问题。这是项目的第一道防线。

第一步：搭建环境与参数解析

1. 文件结构与 Makefile
根据 PDF 的要求（Chapter V），我们需要一个不进行 relink 的 Makefile。

Makefile
NAME= push_swap
CC= gcc
CFLAGS= -Wall -Wextra -Werror -I.
SRCS= main.c utils.c stack_ops.c sort_utils.c
OBJS= (SRCS:.c=.o)
BONUS_SRCS = checker.c # 预留 Bonus 位置
BONUS_NAME = checker

all: (NAME)

(NAME): (OBJS)
(CC) (CFLAGS) -o (NAME) (OBJS)

%.o: %.c
(CC) (CFLAGS) -c 
include 
include 
include  // 用于检查 INT_MAX/MIN

typedef struct s_stack {
    int             value;  // 原始输入的数值
    int             index;  // 排序后的排名索引 (用于压缩数值范围)
    struct s_stack  *next;
    struct s_stack  *prev;  // 如果做双向链表操作会更方便，这里先预留概念
}               t_stack;

// 错误处理宏
void    error_exit(t_stack **a, t_stack **b);

endif

3. 核心：参数解析与去重 (main.c & utils.c)

这是你提到的第一道门槛。我们需要处理 argv，检查非法字符、溢出和重复。

main.c
include "push_swap.h"

int main(int argc, char **argv) {
    t_stack *stack_a = NULL;
    t_stack *stack_b = NULL;

    if (argc 

// 简单的链表添加节点函数
void    stack_add_back(t_stack **lst, t_stack *new) {
    t_stack *tmp;

    if (!lst || !new)
        return ;
    if (!*lst) {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

// 检查重复值的核心逻辑
bool has_duplicates(t_stack *stack) {
    t_stack *tmp;
    t_stack *current;

    current = stack;
    while (current) {
        tmp = current->next; // 从当前节点的下一个开始比较
        while (tmp) {
            // 如果发现相同的值，返回 true (有重复)
            if (current->value == tmp->value) 
                return (true);
            tmp = tmp->next;
        }
        current = current->next;
    }
    return (false);
}

// 错误处理函数：打印 Error 并退出
void error_exit(t_stack **a, t_stack **b) {
    if (a && *a)
        free_stack(a);
    if (b && *b)
        free_stack(b);
    write(2, "Errorn", 6); // 必须写入 stderr (fd 2)
    exit(1);
}

// 辅助函数：释放链表内存 (防止泄漏)
void free_stack(t_stack **stack) {
    t_stack *tmp;
    t_stack *current;

    if (!stack || !*stack)
        return ;
    current = *stack;
    while (current) {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    *stack = NULL;
}

解析参数的难点 (parse_args 思路)：
由于 ./push_swap 1 2 3 和 ./push_swap "1 2 3" 都是合法的输入格式，你通常需要写一个函数来处理这两种情况：
1.  如果 argc > 2，直接遍历 argv[1] 到 argv[argc-1]。
2.  如果 argc == 2，需要检查 argv[1] 是否包含空格，如果有，需要用 strtok 或手动分割字符串。

第二步：讨论排序算法（如何步数最少？）

既然你对“步数最少”感兴趣，我们直接跳过简单的冒泡排序（Bubble Sort）变体。对于 100 或 500 个数字，冒泡排序的指令数会爆炸。

1. 推荐算法：基数排序 (Radix Sort)
这是 Push_swap 项目中公认的“稳妥且步数少”的方案。它在处理大量数据时表现极佳。

*   为什么选它？
    *   时间复杂度：O(d cdot (n + k))。在二进制位操作下，它非常稳定。
    *   适应性：Push_swap 的指令集（ra, rb, pa, pb）非常适合模拟“分桶”和“合并”的过程。
    *   步数控制：对于 500 个数字，基数排序通常能控制在几百步以内，远超快速排序的变体。

*   核心原理 (通俗版)：
    想象你有一堆混在一起的扑克牌（数字）。
    1.  按花色分桶：先看二进制的最低位（Bit 0）。如果是 0，就 pb (推到 B 栈)；如果是 1，就留在 A 栈。
    2.  合并：把 B 栈的牌再 pa (推回 A 栈)。
    3.  按点数分桶：再看二进制的第二位（Bit 1）。重复上述过程。
    4.  直到最高位：当处理完所有二进制位（对于 int 通常是 31 位，但实际数据可能只需要 8-10 位），排序就完成了。

*   具体步骤：
    1.  预处理（Indexing）：先不要直接用原始数字排序。因为原始数字可能很大（如 2147483647），但数量很少（如 100 个）。
        *   你先对原始数组排序，得到排名。
        *   将原始链表中的 value 替换为 index（例如，最小的数变成 0，第二小变成 1...）。
        *   好处：这样你只需要处理 0 到 N-1 的数字，大大减少了需要处理的二进制位数（例如 100 个数只需要 7 位：2^7 = 128）。
    2.  执行排序：
        *   循环遍历每一位（从 0 到 31，或者根据最大索引决定）。
        *   对于当前位：
            *   遍历 Stack A 的所有元素。
            *   如果该元素在该位上是 1，执行 ra（留在 A）。
            *   如果该元素在该位上是 0，执行 pb（移到 B）。
        *   循环结束后，将 Stack B 中的所有元素 pa 回 Stack A。
    3.  结束：当处理完最高位，Stack A 就是有序的。

2. 备选方案：三路快排逻辑 (Smart Sort)
如果你处理的数据量较小（< 100），或者你想追求极致的优化，可以使用“分类法”。
*   思路：将数字分为大、中、小三组。
*   操作：将“小”和“中”组的数字移到 B 栈，保留“大”组在 A 栈。然后将 B 栈中的数字按顺序送回 A 栈。
*   优点：逻辑直观，对于小数据集可能比基数排序更快。
*   缺点：代码逻辑非常复杂，容易出错，且在大数据集下步数不如基数排序稳定。

总结建议
1.  先跑通：先用上面的代码把环境搭好，确保 malloc 和 free 配对，确保去重逻辑正确。
2.  实现 Indexing：在排序前，先写一个函数把链表里的 value 转换成 index。这是基数排序高效的关键。
3.  再攻算法：直接上手 基数排序 (Radix Sort)。虽然理解起来稍微绕一点（需要懂位运算），但代码量少，逻辑清晰，且绝对能过 500 个数的测试。

参数解析（parse_args）确实是 Push_swap 项目中最繁琐且最容易出错的环节之一。

难点在于：./push_swap "1 2 3"（一个参数）和 ./push_swap 1 2 3（三个参数）必须被解析成同样的链表。而且你不能使用 strtok（因为它会修改原字符串，且不符合 Norm 的某些严格要求），也不能使用 atoi（必须自己检查溢出）。

作为你的导师，我将提供一个符合 42 Norm、无内存泄漏、严格检查错误的实现方案。

1. 整体思路

我们将分三步走：
1.  Count & Allocate：先遍历一遍 argv，把所有数字提取到一个临时的 int 数组中。同时检查是否有非法字符（非数字、非空格、非正负号）。
2.  Check Duplicates：在数组层面检查重复（比在链表上检查快且简单）。
3.  Build Stack：利用数组创建链表。

2. 头文件更新 (push_swap.h)

我们需要引入 bool 类型。

ifndef PUSH_SWAP_H
define PUSH_SWAP_H

include 
include 
include 
include  // 新增

typedef struct s_stack {
    int             value;
    int             index;
    struct s_stack  *next;
}               t_stack;

// --- 新增函数声明 ---
int     count_nums(char **argv);
long    ft_atol(const char *str); // 我们自己写的 atol，用于检查溢出
void    free_array(void **ptr);
void    parse_args(int argc, char **argv, t_stack **stack_a);

endif

3. 核心实现 (utils.c)

这是最核心的部分，请仔细阅读注释，因为面试（Defense）时可能会问到这些细节。

A. parse_args 主函数
include "push_swap.h"

void parse_args(int argc, char **argv, t_stack **stack_a) {
    long    *numbers; // 使用 long 临时存储，防止 int 溢出判断失误
    int     count;
    int     i;

    // 1. 统计数字个数并转换
    // 如果有多个参数 (argc > 2)，直接处理 argv[1] 到 argv[argc-1]
    // 如果只有一个参数 (argc == 2)，需要处理字符串内的空格分隔
    numbers = malloc(sizeof(long) * (argc - 1)); // 临时数组
    if (!numbers)
        error_exit(stack_a, NULL);
    
    count = 0;
    i = 0;
    while (++i  INT_MAX || numbers[i]  '9')
            return (false);
        i++;
    }
    return (true);
}

C. 辅助函数：自定义 ft_atol (Ascii to Long)
为什么不用 atoi？ 因为 atoi 遇到错误不报错，直接返回 0。我们需要它能处理溢出。

long ft_atol(const char *str) {
    int     i = 0;
    int     sign = 1;
    long    result = 0;

    // 跳过空格
    while ((str[i] >= 9 && str[i] = '0' && str[i] value = value;
    new->index = 0; // 初始化为 0，后续排序算法会重新赋值
    new->next = NULL;
    return (new);
}

void stack_add_back(t_stack **lst, t_stack *new) {
    t_stack *tmp;
    if (!lst || !new)
        return ;
    if (!*lst) {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

4. 导师的特别叮嘱 (面试 Defense 预测)

1.  关于 ft_atol vs atoi：
    *   面试官可能会问：“你为什么自己写 atoi？”
    *   回答：标准库的 atoi 在遇到错误（如溢出或非法字符）时行为不明确，通常返回 0。为了严格遵守项目要求（遇到错误必须输出 "Error"），我需要一个能精确检测输入格式和数值范围的版本。

2.  关于内存管理：
    *   你看到了 numbers 数组是 malloc 出来的。千万记得在构建完链表后 free 它。如果你在这里忘记 free，会被判 Leak。

3.  关于负号处理：
    *   注意 is_valid_number 函数。它严格限制了 + 或 - 只能出现在数字的最开始。像 12-3 这种中间带负号的，会被判定为非法。

1. assign_index 函数实现

include "push_swap.h"

void assign_index(t_stack **stack) {
    t_stack *current;
    int     *sorted;
    int     count;
    int     i;

    // 1. 统计节点数量
    count = stack_size(*stack);
    if (count value;
        current = current->next;
    }

    // 4. 对数组进行排序
    quick_sort(sorted, 0, count - 1);

    // 5. 为每个节点分配索引
    current = *stack;
    while (current) {
        i = 0;
        while (i value == sorted[i]) {
                current->index = i;
                break;
            }
            i++;
        }
        current = current->next;
    }

    free(sorted); // 释放数组
}

2. 辅助函数

快速排序（用于索引分配）
static void quick_sort(int *arr, int low, int high) {
    if (low next;
    }
    return (count);
}

3. 作用与优势

1. 标准化数据范围  
   将任意范围的 value 映射为 0 到 N-1 的索引，使得排序算法（如基数排序）可以高效处理，避免对大整数的复杂操作。

2. 保持相对顺序  
   索引分配严格保持原数据的相对大小顺序，确保排序结果正确。

3. 内存安全  
   使用临时数组进行排序和索引分配，不会修改原链表的值，只更新 index 字段。

4. 符合 Norm 要求  
   - 无内存泄漏（malloc 与 free 成对出现）  
   - 严格错误处理（遇到错误调用 error_exit）  
   - 代码结构清晰、可读性强  

4. 导师的特别提醒

- 为什么用快速排序？  
  快速排序平均时间复杂度为 O(n log n)，适合中等规模数据（Push_swap 的输入规模通常较小）。

- 为什么不用库函数 qsort？  
  42 的 Norm 通常禁止使用标准库的排序函数，要求自己实现。

- 索引化后的效果示例  
    原始链表:  100 → 50 → 200
  索引化后:   1   → 0  →  2
  

- 面试 Defense 提示  
  面试官可能会问：“为什么索引化能提升排序效率？”  
  回答：基数排序等算法对 0 到 N-1 的整数操作效率最高，索引化将任意范围的数值标准化为连续小整数，大幅减少比较和移动次数

1. radix_sort 函数实现

include "push_swap.h"

void radix_sort(t_stack **stack_a, t_stack **stack_b) {
    int max_bits = 0;
    int i = 0;
    int size = stack_size(*stack_a);
    int max_value = 0;
    t_stack *current = *stack_a;

    // 1. 找到最大索引值
    while (current) {
        if (current->index > max_value)
            max_value = current->index;
        current = current->next;
    }

    // 2. 计算最大位数（bit 数）
    while ((max_value >> i) > 0) {
        max_bits++;
        i++;
    }

    // 3. 按位排序
    for (i = 0; i index >> i & 1) {
                ra(stack_a); // 如果当前位为 1，旋转到 stack_a 顶部
            } else {
                pb(stack_a, stack_b); // 如果当前位为 0，移动到 stack_b
            }
            j++;
        }

        // 4. 将 stack_b 中的元素移回 stack_a
        while (*stack_b) {
            pa(stack_a, stack_b);
        }
    }
}

2. 辅助函数

旋转操作（ra）
void ra(t_stack **stack) {
    if (!stack || !(stack)->next)
        return;
    t_stack *tmp = *stack;
    stack = (stack)->next;
    tmp->next = NULL;
    stack_add_back(stack, tmp);
}

移动操作（pb 和 pa）
void pb(t_stack **stack_a, t_stack **stack_b) {
    if (!*stack_a)
        return;
    t_stack *tmp = *stack_a;
    stack_a = (stack_a)->next;
    tmp->next = NULL;
    stack_add_front(stack_b, tmp);
}

void pa(t_stack **stack_a, t_stack **stack_b) {
    if (!*stack_b)
        return;
    t_stack *tmp = *stack_b;
    stack_b = (stack_b)->next;
    tmp->next = NULL;
    stack_add_front(stack_a, tmp);
}

前端添加节点
void stack_add_front(t_stack **lst, t_stack *new) {
    if (!lst || !new)
        return;
    new->next = *lst;
    *lst = new;
}

3. 算法原理与优势

1. 基数排序思想  
   - 将每个索引视为二进制数，从最低位到最高位依次排序。  
   - 每次只关注当前位是 0 还是 1，将数据分成两组（stack_b 存 0，stack_a 存 1）。  
   - 最后将 stack_b 合并回 stack_a，完成当前位的排序。

2. 高效性  
   - 时间复杂度为 O(n log n)，适合处理 Push_swap 的典型输入规模。  
   - 每次只处理一位，避免了复杂的比较操作。

3. 稳定性  
   - 保持相同位值的元素相对顺序不变，确保最终排序结果正确。

4. 内存安全  
   - 所有链表操作均通过指针完成，无额外内存分配，避免内存泄漏。

4. 导师的特别提醒

- 为什么用位运算？  
  位运算（>> 和 &）比取模运算（%）更快，且能直接访问二进制位，适合基数排序。

- 面试 Defense 提示  
  面试官可能会问：“为什么基数排序比快速排序更适合 Push_swap？”  
  回答：基数排序在处理小整数（0 到 N-1）时具有线性时间复杂度 O(n)，而快速排序的平均复杂度为 O(n log n)。此外，基数排序不需要比较操作，减少了指令数量。

- 优化建议  
  - 如果输入规模非常小（如 n < 10），可以考虑使用插入排序替代基数排序。  
  - 对于超大输入，可以结合多线程优化位处理阶段。

- 调试技巧  
  在每轮位排序后，使用 print_stack 函数输出链表状态，验证当前位排序是否正确。

1. 常见错误类型

1. 内存泄漏  
   - 表现：程序运行时内存占用持续增加。  
   - 原因：malloc 后未正确 free，或链表节点未正确释放。  
   - 解决：使用 valgrind 检测泄漏点，确保所有动态分配的内存都有对应的释放操作。

2. 逻辑错误  
   - 表现：排序结果不正确，或链表状态异常。  
   - 原因：索引分配错误、位运算逻辑错误，或链表指针操作不当。  
   - 解决：通过日志输出中间状态，验证每一步的正确性。

3. 边界条件遗漏  
   - 表现：小规模输入（如 2 个元素）或特殊顺序输入（如已排序）失败。  
   - 原因：未处理极端情况，如空链表、单节点链表。  
   - 解决：设计测试用例覆盖所有边界条件。

2. 调试工具使用

1. Valgrind  
      valgrind --leak-check=full --show-leak-kinds=all ./push_swap 5 3 1 2 4
   
   - 用途：检测内存泄漏、非法内存访问。  
   - 关键输出：definitely lost（确定泄漏）和 invalid read/write（非法访问）。  
   - 技巧：结合 --track-origins=yes 追踪未初始化变量的来源。

2. GDB  
      gdb ./push_swap
   (gdb) run 5 3 1 2 4
   (gdb) bt  # 查看调用栈
   (gdb) print *stack_a  # 检查链表状态
   
   - 用途：定位段错误、逻辑错误。  
   - 技巧：设置断点在关键函数（如 radix_sort），逐步执行并观察变量变化。

3. 测试用例设计

1. 基础测试  
   - 输入：5 3 1 2 4（随机顺序）  
   - 预期：输出排序后的链表 1 → 2 → 3 → 4 → 5。

2. 边界测试  
   - 输入：1（单元素）  
   - 预期：无需排序，直接返回原链表。  
   - 输入：2 1（两元素逆序）  
   - 预期：输出 1 → 2。

3. 特殊顺序测试  
   - 输入：1 2 3 4 5（已排序）  
   - 预期：输出与输入相同。  
   - 输入：5 4 3 2 1（完全逆序）  
   - 预期：输出 1 → 2 → 3 → 4 → 5。

4. 大规模测试  
   - 输入：100 个随机数（如 ./push_swap $(shuf -i 1-100 -n 100)）  
   - 预期：输出严格递增序列。

4. 日志输出技巧

1. 链表状态打印  
      void print_stack(t_stack *stack) {
       while (stack) {
           printf("%d → ", stack->value);
           stack = stack->next;
       }
       printf("NULLn");
   }
   
   - 用法：在 assign_index 和 radix_sort 的关键步骤后调用，验证中间状态。

2. 操作计数器  
      int op_count = 0;
   void ra(t_stack **stack) {
       op_count++;
       // ...原有逻辑
   }
   
   - 用法：统计操作次数，验证是否符合 Norm 要求（如操作数不超过某阈值）。

3. 颜色化输出  
      #define RED "033[0;31m"
   #define GREEN "033[0;32m"
   #define RESET "033[0m"
   
   - 用法：用颜色区分不同阶段的输出（如红色表示错误，绿色表示成功）。

5. 优化建议

1. 减少操作次数  
   - 在 radix_sort 中，避免不必要的 ra 操作（如当前位为 1 且已在顶部时）。  
   - 合并连续的相同操作（如多个 ra 可替换为单次旋转）。

2. 提前终止条件  
   - 在 radix_sort 中，若当前位所有值相同（全 0 或全 1），可跳过该位处理。

3. 代码复用  
   - 将链表操作（如 stack_size、stack_add_front）封装为独立函数，提高可读性。

4. 防御式编程  
   - 在关键函数开头添加 NULL 检查（如 if (!stack) return），避免段错误。
