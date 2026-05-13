# Push_swap · 三语文档 (中文 / English / Español)

> 42 项目：使用两个栈与限定操作，以尽量少的指令完成排序。  
> 42 project: sort integers with two stacks and a restricted instruction set.  
> Proyecto 42: ordenar enteros con dos pilas y un conjunto limitado de instrucciones.

---

## 目录 / Table of Contents / Índice

- [中文（简体）](#中文简体)
- [English](#english)
- [Español](#español)

---

## 中文（简体）

### 1) 项目简介
`push_swap` 需要在**只允许 11 个操作**的前提下，把栈 A 中的整数从小到大排序，并将操作序列输出到标准输出。  
`checker`（bonus）读取同一组输入和一串操作指令，判断最终结果是否正确（输出 `OK` 或 `KO`）。

### 2) 支持的操作（11 条）

| 指令 | 说明 |
|---|---|
| `sa` | 交换 A 栈顶两个元素 |
| `sb` | 交换 B 栈顶两个元素 |
| `ss` | 同时执行 `sa` 与 `sb` |
| `pa` | 将 B 栈顶压入 A |
| `pb` | 将 A 栈顶压入 B |
| `ra` | A 上旋（首元素移到末尾） |
| `rb` | B 上旋 |
| `rr` | 同时执行 `ra` 与 `rb` |
| `rra` | A 下旋（末元素移到开头） |
| `rrb` | B 下旋 |
| `rrr` | 同时执行 `rra` 与 `rrb` |

### 3) 编译
```bash
# 编译 push_swap
make

# 编译 checker（bonus）
make bonus

# 清理目标文件
make clean

# 清理全部（含二进制）
make fclean

# 全量重编
make re
```

生成的可执行文件：`push_swap`、`checker`

### 4) 使用示例
```bash
# 生成操作序列
./push_swap 3 2 5 1 4

# 用 checker 验证
ARG="3 2 5 1 4"
./push_swap $ARG | ./checker $ARG
# 期望输出: OK
```

### 5) 参数与错误处理
以下情况会输出 `Error` 到 `stderr` 并退出：
- 非法整数格式
- 超出 `INT_MIN` ~ `INT_MAX`
- 重复数字

### 6) 算法说明
- 小规模输入（2~5 个）使用专门策略，减少操作数。
- 大规模输入使用基于索引压缩（coordinate compression）的二进制基数排序（radix sort）。

### 7) 仓库结构
```text
Push-swap/
├── Makefile
├── includes/
│   ├── push_swap.h
│   └── push_swap_bonus.h
├── libft/
├── src/
│   ├── ft_main.c
│   ├── ft_parse.c
│   ├── ft_parse_utils.c
│   ├── ft_stack_utils.c
│   ├── ft_index.c
│   ├── ft_ops_swap.c
│   ├── ft_ops_push.c
│   ├── ft_ops_rotate.c
│   ├── ft_ops_rrotate.c
│   ├── ft_sort.c
│   └── ft_sort_small.c
└── bonus/
    ├── checker_bonus.c
    ├── ft_apply_bonus.c
    ├── ft_exec_op_bonus.c
    └── ft_get_line_bonus.c
```

---

## English

### 1) Overview
`push_swap` must sort integers in stack A in ascending order using **only 11 allowed operations**, printing the instruction sequence to stdout.  
`checker` (bonus) reads the same input plus instructions from stdin and verifies whether the final state is correct (`OK` / `KO`).

### 2) Allowed operations (11)

| Instruction | Effect |
|---|---|
| `sa` | Swap top 2 of A |
| `sb` | Swap top 2 of B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push top of B to A |
| `pb` | Push top of A to B |
| `ra` | Rotate A up |
| `rb` | Rotate B up |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate A |
| `rrb` | Reverse rotate B |
| `rrr` | `rra` and `rrb` simultaneously |

### 3) Build
```bash
# Build push_swap
make

# Build checker (bonus)
make bonus

# Remove object files
make clean

# Remove all build artifacts
make fclean

# Rebuild from scratch
make re
```

Generated binaries: `push_swap`, `checker`

### 4) Usage example
```bash
# Generate operations
./push_swap 3 2 5 1 4

# Validate with checker
ARG="3 2 5 1 4"
./push_swap $ARG | ./checker $ARG
# Expected output: OK
```

### 5) Input validation and errors
The program prints `Error` to `stderr` and exits when:
- A token is not a valid integer
- A value is outside `INT_MIN` ~ `INT_MAX`
- Duplicate numbers are provided

### 6) Sorting strategy
- For very small inputs (2 to 5 elements), dedicated minimal-case logic is used.
- For larger inputs, the project uses coordinate compression plus binary radix sort on indices.

### 7) Repository structure
```text
Push-swap/
├── Makefile
├── includes/
│   ├── push_swap.h
│   └── push_swap_bonus.h
├── libft/
├── src/
│   ├── ft_main.c
│   ├── ft_parse.c
│   ├── ft_parse_utils.c
│   ├── ft_stack_utils.c
│   ├── ft_index.c
│   ├── ft_ops_swap.c
│   ├── ft_ops_push.c
│   ├── ft_ops_rotate.c
│   ├── ft_ops_rrotate.c
│   ├── ft_sort.c
│   └── ft_sort_small.c
└── bonus/
    ├── checker_bonus.c
    ├── ft_apply_bonus.c
    ├── ft_exec_op_bonus.c
    └── ft_get_line_bonus.c
```

---

## Español

### 1) Descripción
`push_swap` debe ordenar en forma ascendente los enteros de la pila A usando **solo 11 operaciones permitidas**, imprimiendo la secuencia de instrucciones por stdout.  
`checker` (bonus) recibe los mismos números y una lista de instrucciones por stdin para validar el resultado final (`OK` / `KO`).

### 2) Operaciones permitidas (11)

| Instrucción | Efecto |
|---|---|
| `sa` | Intercambia los 2 primeros de A |
| `sb` | Intercambia los 2 primeros de B |
| `ss` | `sa` y `sb` a la vez |
| `pa` | Mueve el tope de B a A |
| `pb` | Mueve el tope de A a B |
| `ra` | Rota A hacia arriba |
| `rb` | Rota B hacia arriba |
| `rr` | `ra` y `rb` a la vez |
| `rra` | Rota A hacia abajo |
| `rrb` | Rota B hacia abajo |
| `rrr` | `rra` y `rrb` a la vez |

### 3) Compilación
```bash
# Compilar push_swap
make

# Compilar checker (bonus)
make bonus

# Limpiar objetos
make clean

# Limpiar todo
make fclean

# Recompilar desde cero
make re
```

Binarios generados: `push_swap`, `checker`

### 4) Ejemplo de uso
```bash
# Generar instrucciones
./push_swap 3 2 5 1 4

# Validar con checker
ARG="3 2 5 1 4"
./push_swap $ARG | ./checker $ARG
# Salida esperada: OK
```

### 5) Validación y errores
El programa imprime `Error` en `stderr` y termina cuando:
- Hay un token que no es entero válido
- Un valor excede `INT_MIN` ~ `INT_MAX`
- Existen números duplicados

### 6) Estrategia de ordenación
- Para entradas pequeñas (2 a 5), se usan rutinas específicas para minimizar operaciones.
- Para entradas grandes, se aplica compresión de coordenadas y radix sort binario sobre índices.

### 7) Estructura del repositorio
```text
Push-swap/
├── Makefile
├── includes/
│   ├── push_swap.h
│   └── push_swap_bonus.h
├── libft/
├── src/
│   ├── ft_main.c
│   ├── ft_parse.c
│   ├── ft_parse_utils.c
│   ├── ft_stack_utils.c
│   ├── ft_index.c
│   ├── ft_ops_swap.c
│   ├── ft_ops_push.c
│   ├── ft_ops_rotate.c
│   ├── ft_ops_rrotate.c
│   ├── ft_sort.c
│   └── ft_sort_small.c
└── bonus/
    ├── checker_bonus.c
    ├── ft_apply_bonus.c
    ├── ft_exec_op_bonus.c
    └── ft_get_line_bonus.c
```

---

Repositorio / Repository / 仓库: [FranciscoLi2000/Push-swap](https://github.com/FranciscoLi2000/Push-swap)
