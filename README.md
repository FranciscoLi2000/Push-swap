# Push-swap — Guía completa en español

> Proyecto 42 Barcelona · Algoritmos de ordenación con pilas

---

## Índice

1. [¿Qué es este proyecto?](#1-qué-es-este-proyecto)
2. [Reglas del juego](#2-reglas-del-juego)
3. [Estructura del repositorio](#3-estructura-del-repositorio)
4. [Compilación](#4-compilación)
5. [Estructura de datos](#5-estructura-de-datos)
6. [Parte 1 — push_swap: implementación paso a paso](#6-parte-1--push_swap-implementación-paso-a-paso)
7. [Parte 2 — checker (bonus): implementación paso a paso](#7-parte-2--checker-bonus-implementación-paso-a-paso)
8. [Makefile explicado](#8-makefile-explicado)
9. [Testing y verificación](#9-testing-y-verificación)
10. [Errores frecuentes y cómo evitarlos](#10-errores-frecuentes-y-cómo-evitarlos)

---

## 1. ¿Qué es este proyecto?

`push_swap` es un proyecto de algoritmos de 42. El objetivo es:

> Dado un conjunto de enteros sin orden, imprime la **secuencia mínima de instrucciones** que ordena la pila A de menor a mayor usando únicamente dos pilas (A y B) y 11 operaciones predefinidas.

El programa `checker` (bonus) hace la función inversa: recibe los mismos números,
lee una lista de instrucciones desde stdin y responde `OK` si el resultado está
ordenado o `KO` si no.

---

## 2. Reglas del juego

### Las 11 operaciones

| Instrucción | Efecto |
|-------------|--------|
| `sa` | Intercambia los dos primeros elementos de A |
| `sb` | Intercambia los dos primeros elementos de B |
| `ss` | `sa` y `sb` simultáneamente |
| `pa` | Mueve el tope de B al tope de A |
| `pb` | Mueve el tope de A al tope de B |
| `ra` | Rota A hacia arriba (el primero pasa al final) |
| `rb` | Rota B hacia arriba |
| `rr` | `ra` y `rb` simultáneamente |
| `rra` | Rota A hacia abajo (el último pasa al principio) |
| `rrb` | Rota B hacia abajo |
| `rrr` | `rra` y `rrb` simultáneamente |

### Condiciones de error

- Entrada no entera.
- Valor fuera del rango `INT_MIN`..`INT_MAX`.
- Valores duplicados.
- En todos los casos se imprime `Error\n` en `stderr` y se sale con código 1.

### Límites de pasos (evaluación)

| Tamaño | Pasos máximos orientativos |
|--------|---------------------------|
| 3      | ≤ 3                        |
| 5      | ≤ 12                       |
| 100    | ≤ 700                      |
| 500    | ≤ 5 500                    |

---

## 3. Estructura del repositorio

```
Push-swap/
├── Makefile
├── includes/
│   ├── push_swap.h          <- cabecera principal
│   └── push_swap_bonus.h    <- cabecera del checker
├── libft/                   <- biblioteca mínima propia
│   ├── Makefile
│   ├── libft.h
│   ├── ft_isdigit.c
│   ├── ft_strlen.c
│   ├── ft_calloc.c
│   ├── ft_split.c
│   └── ft_putstr_fd.c
├── src/                     <- fuentes de push_swap
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
└── bonus/                   <- fuentes del checker
    ├── checker_bonus.c
    ├── ft_apply_bonus.c
    ├── ft_exec_op_bonus.c
    └── ft_get_line_bonus.c
```

---

## 4. Compilación

```bash
# Compila solo push_swap
make

# Compila también el checker (bonus)
make bonus

# Limpia objetos
make clean

# Limpia todo (binarios incluidos)
make fclean

# Recompila desde cero
make re
```

Binarios generados: `push_swap` y `checker`.

---

## 5. Estructura de datos

Todo el proyecto gira en torno a una **lista enlazada simple** que actúa como pila
(el nodo cabeza es el tope).

```c
// includes/push_swap.h

typedef struct s_stack
{
    int             value;   // valor original del número
    int             index;   // rango normalizado (0 = mínimo)
    struct s_stack  *next;
}   t_stack;
```

`value` se usa solo para parsear y para la comprobación final en el checker.
`index` es el campo sobre el que trabajan todos los algoritmos de ordenación.

---

## 6. Parte 1 — `push_swap`: implementación paso a paso

### 6.1 Cabecera y libft mínima

El archivo `includes/push_swap.h` concentra:

- La definición de `t_stack`.
- La constante `MAX_NUM_LEN 20` (longitud máxima de una cadena que representa un `int`).
- Los prototipos de todas las funciones del proyecto.

La `libft` propia solo implementa las funciones que este proyecto necesita:

| Función | Uso en el proyecto |
|---------|--------------------|
| `ft_isdigit` | Validar caracteres numéricos |
| `ft_strlen` | Base para otras funciones |
| `ft_calloc` | Reservar memoria inicializada a cero |
| `ft_split` | Disponible pero no imprescindible aquí |
| `ft_putstr_fd` | Las ops usan `write` directamente |

> **Regla práctica**: en 42 no se puede usar funciones de string estándar sin
> implementarlas uno mismo. Usa siempre tu `libft`.

---

### 6.2 Utilidades de pila

**Archivo:** `src/ft_stack_utils.c`

```
ft_stack_new(value)       -> crea un nodo nuevo con malloc
ft_stack_add_back(lst, n) -> añade un nodo al fondo de la pila
ft_stack_size(stack)      -> cuenta los nodos
ft_free_stack(stack)      -> libera toda la lista y pone el puntero a NULL
ft_error_exit(a, b)       -> libera ambas pilas, escribe "Error\n" en stderr y sale
```

Puntos clave de implementación:

- `ft_stack_new` inicializa `index = 0` y `next = NULL`.
- `ft_free_stack` recibe `t_stack **` para asignar `NULL` al puntero original y
  evitar punteros colgantes.
- `ft_error_exit` comprueba que los punteros no sean `NULL` antes de liberar.

```c
// Ejemplo: ft_stack_new
t_stack *ft_stack_new(int value)
{
    t_stack *node;

    node = malloc(sizeof(t_stack));
    if (!node)
        return (NULL);
    node->value = value;
    node->index = 0;
    node->next  = NULL;
    return (node);
}
```

```c
// Ejemplo: ft_error_exit
void ft_error_exit(t_stack **a, t_stack **b)
{
    if (a && *a)
        ft_free_stack(a);
    if (b && *b)
        ft_free_stack(b);
    write(2, "Error\n", 6);
    exit(1);
}
```

---

### 6.3 Parseo y validación de argumentos

**Archivos:** `src/ft_parse.c`, `src/ft_parse_utils.c`

El programa acepta los números de dos formas:

```
./push_swap 3 1 2        <- argc > 2, cada argv[i] es un número
./push_swap "3 1 2"      <- argc == 2, argv[1] es una cadena con espacios
```

#### `ft_atol` — conversión segura a `long`

```c
long ft_atol(const char *str)
```

Convierte a `long` con desbordamiento controlado: si el valor supera `LONG_MAX`
devuelve `LONG_MAX` para que el validador posterior lo detecte.

#### `ft_is_valid_num` — validación completa

```c
int ft_is_valid_num(char *str)
```

1. Acepta un `+` o `-` inicial opcional.
2. Verifica que todos los demás caracteres sean dígitos.
3. Llama a `ft_atol` y comprueba que el resultado esté dentro de `[INT_MIN, INT_MAX]`.

#### `ft_parse_args` — punto de entrada

```c
void ft_parse_args(int argc, char **argv, t_stack **a, t_stack **b)
```

- Si `argc < 2`: retorna sin hacer nada (el `main` saldrá limpiamente).
- Si `argc == 2`: llama a `ft_parse_str` que divide la cadena palabra a palabra
  (maneja espacios y tabulaciones, sin usar `ft_split`).
- Si `argc > 2`: llama a `ft_parse_word` por cada `argv[i]`.
- Al final comprueba duplicados con `ft_has_duplicates`.

#### `ft_has_duplicates`

Comparación O(n²) con dos bucles anidados. Para n ≤ 500 es perfectamente eficiente.

---

### 6.4 Asignación de índices (coordinate compression)

**Archivo:** `src/ft_index.c`

El truco que hace funcionar el radix sort es convertir los valores originales
(que pueden ser negativos y dispersos) en índices consecutivos `0, 1, 2, …, n-1`.

Algoritmo:

1. Copia los `value` de la pila en un array temporal.
2. Ordena ese array con **insertion sort** (simple y correcto para n ≤ 500).
3. Para cada nodo de la pila, busca su posición en el array ordenado y asigna
   ese índice al campo `index`.

```c
void ft_assign_index(t_stack **a)
{
    int *sorted = malloc(sizeof(int) * n);
    ft_fill_arr(*a, sorted);   // copia los values
    ft_isort(sorted, n);       // ordena el array
    curr = *a;
    while (curr)
    {
        i = 0;
        while (sorted[i] != curr->value)
            i++;
        curr->index = i;
        curr = curr->next;
    }
    free(sorted);
}
```

Después de este paso el elemento más pequeño tiene `index = 0`,
el siguiente `index = 1`, etc. Los algoritmos de ordenación solo miran `index`.

---

### 6.5 Las 11 operaciones

Cada operación tiene una función interna (sin `write`) y una o varias funciones
públicas que llaman a la interna y después imprimen el nombre de la instrucción
en stdout.

#### Swap — `src/ft_ops_swap.c`

```c
// Helper interno: intercambia value e index de los dos primeros nodos
static void ft_swap(t_stack *s)
{
    int tmp;

    tmp          = s->value;
    s->value     = s->next->value;
    s->next->value = tmp;
    tmp          = s->index;
    s->index     = s->next->index;
    s->next->index = tmp;
}

void ft_sa(t_stack **a) { if (*a && (*a)->next) { ft_swap(*a); write(1, "sa\n", 3); } }
void ft_sb(t_stack **b) { if (*b && (*b)->next) { ft_swap(*b); write(1, "sb\n", 3); } }
void ft_ss(t_stack **a, t_stack **b)
{
    if (*a && (*a)->next) ft_swap(*a);
    if (*b && (*b)->next) ft_swap(*b);
    write(1, "ss\n", 3);
}
```

> **Nota**: `ft_ss` siempre imprime `ss` aunque una de las pilas tenga menos de
> 2 elementos. La operación ocurre en las pilas que puedan; la impresión es siempre.

#### Push — `src/ft_ops_push.c`

```c
void ft_pb(t_stack **a, t_stack **b)
{
    t_stack *tmp;

    if (!*a)
        return ;
    tmp    = *a;          // guarda el tope de A
    *a     = tmp->next;   // A avanza al siguiente
    tmp->next = *b;       // el nodo apunta al antiguo tope de B
    *b     = tmp;         // B apunta al nodo recién movido
    write(1, "pb\n", 3);
}
// ft_pa es simétrica
```

#### Rotate — `src/ft_ops_rotate.c`

```c
static void ft_rotate(t_stack **s)
{
    t_stack *tmp;
    t_stack *last;

    tmp    = *s;          // guarda el tope
    *s     = tmp->next;   // el segundo nodo pasa a ser el tope
    tmp->next = NULL;     // desconecta el antiguo tope
    last   = *s;
    while (last->next)
        last = last->next;
    last->next = tmp;     // enlaza el antiguo tope al final
}
```

#### Reverse rotate — `src/ft_ops_rrotate.c`

```c
static void ft_rrotate(t_stack **s)
{
    t_stack *tmp;
    t_stack *prev;

    tmp  = *s;
    prev = NULL;
    while (tmp->next) { prev = tmp; tmp = tmp->next; }  // llega al último
    prev->next = NULL;   // desconecta el último
    tmp->next  = *s;     // el último apunta al antiguo tope
    *s         = tmp;    // el último es ahora el tope
}
```

---

### 6.6 Algoritmos de ordenación

**Archivos:** `src/ft_sort.c`, `src/ft_sort_small.c`

El punto de entrada es:

```c
void ft_sort(t_stack **a, t_stack **b)
{
    int size = ft_stack_size(*a);
    if (size <= 5)
        ft_sort_small(a, b);
    else
        ft_radix_sort(a, b);
}
```

#### Ordenación para 2 elementos

```c
void ft_sort_two(t_stack **a)
{
    if ((*a)->index > (*a)->next->index)
        ft_sa(a);
}
```

#### Ordenación para 3 elementos

Hay 6 permutaciones. Se cubren con una tabla de casos:

| Orden (top, mid, bot) | Operaciones |
|-----------------------|-------------|
| 0 1 2 (ya ordenado)   | —           |
| 0 2 1                 | `rra` + `sa` |
| 1 0 2                 | `sa`         |
| 1 2 0                 | `ra`         |
| 2 0 1                 | `rra`        |
| 2 1 0                 | `sa` + `rra` |

```c
static void ft_sort_three_cases(t_stack **a, int top, int mid, int bot)
{
    if (top < mid && mid < bot)          return ;
    if (top < bot && bot < mid)        { ft_rra(a); ft_sa(a); }
    else if (mid < top && top < bot)     ft_sa(a);
    else if (mid < bot && bot < top)     ft_ra(a);
    else if (bot < top && top < mid)     ft_rra(a);
    else                               { ft_sa(a); ft_rra(a); }
}
```

#### Ordenación para 4–5 elementos

Se usa `ft_push_min`: encuentra la posición del mínimo y lo rota al tope
eligiendo la dirección más corta (ra o rra), luego lo manda a B con `pb`.

- **4 elementos**: saca el mínimo a B, ordena los 3 restantes, devuelve con `pa`.
- **5 elementos**: saca los 2 mínimos a B, ordena los 3 restantes, devuelve con 2×`pa`.

```c
static void ft_push_min(t_stack **a, t_stack **b, int size)
{
    int pos = ft_find_min_pos(*a);
    if (pos <= size / 2)
        while (pos-- > 0) ft_ra(a);
    else
    {
        pos = size - pos;
        while (pos-- > 0) ft_rra(a);
    }
    ft_pb(a, b);
}
```

#### Radix sort binario (≥ 6 elementos)

Funciona con los `index` normalizados. Ordena bit a bit de menos significativo
a más significativo.

En cada pasada sobre el bit `i`:
- Si el bit `i` del `index` del tope es **0** → `pb` (va a B).
- Si el bit `i` del `index` del tope es **1** → `ra` (se queda en A).
- Al terminar la pasada, devuelve todo B a A con `pa`.

Tras `⌈log₂(n)⌉` pasadas, A queda ordenado.

```c
void ft_radix_sort(t_stack **a, t_stack **b)
{
    int size     = ft_stack_size(*a);
    int max_bits = 0;
    int i        = size - 1;

    while ((i >> max_bits) > 0)
        max_bits++;
    i = 0;
    while (i < max_bits)
    {
        int j = 0;
        while (j < size)
        {
            if (((*a)->index >> i) & 1)
                ft_ra(a);
            else
                ft_pb(a, b);
            j++;
        }
        while (*b)
            ft_pa(a, b);
        i++;
    }
}
```

**¿Por qué funciona?**
Después de procesar el bit 0 todos los índices pares están antes que los impares
en el orden relativo correcto. Después del bit 1 la distinción se refina.
Tras todas las pasadas el orden de los índices es ascendente.

---

### 6.7 Función `main`

**Archivo:** `src/ft_main.c`

```c
int main(int argc, char **argv)
{
    t_stack *stack_a = NULL;
    t_stack *stack_b = NULL;

    ft_parse_args(argc, argv, &stack_a, &stack_b);

    if (!stack_a)                         // sin argumentos -> salida limpia
        return (0);
    if (ft_stack_size(stack_a) == 1)      // un solo elemento -> ya ordenado
    {
        ft_free_stack(&stack_a);
        return (0);
    }

    ft_assign_index(&stack_a);            // normaliza los valores a índices

    if (!ft_is_sorted(stack_a))           // si ya está ordenado no hace nada
        ft_sort(&stack_a, &stack_b);

    ft_free_stack(&stack_a);
    ft_free_stack(&stack_b);
    return (0);
}
```

`ft_is_sorted` recorre la pila y devuelve `1` si cada `index` es menor que
el siguiente.

---

## 7. Parte 2 — `checker` (bonus): implementación paso a paso

El `checker` recibe los mismos argumentos que `push_swap`, pero en lugar de
calcular instrucciones las **lee desde stdin** y las ejecuta. Al final imprime
`OK` o `KO`.

### 7.1 Cabecera bonus

**Archivo:** `includes/push_swap_bonus.h`

```c
#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include "push_swap.h"

# define LINEBUF_SIZE 128   // tamaño máximo de una línea de instrucción

void  ft_apply_swap(t_stack **s);
void  ft_apply_push(t_stack **from, t_stack **to);
void  ft_apply_rotate(t_stack **s);
void  ft_apply_rrotate(t_stack **s);
int   ft_exec_op(char *op, t_stack **a, t_stack **b);
char *ft_get_line(int fd);

#endif
```

Las funciones `ft_apply_*` son versiones **silenciosas** de las operaciones
(sin `write`).

---

### 7.2 Lectura de línea sin `get_next_line`

**Archivo:** `bonus/ft_get_line_bonus.c`

Lee carácter a carácter hasta `\n` o EOF. Devuelve `NULL` cuando no hay más
entrada. El caller debe llamar `free(line)` después de cada uso.

```c
char *ft_get_line(int fd)
{
    char *line = malloc(LINEBUF_SIZE);
    int   i    = 0;
    char  buf[2];
    int   ret;

    if (!line)
        return (NULL);
    ret = read(fd, buf, 1);
    while (ret > 0 && buf[0] != '\n')
    {
        if (i < LINEBUF_SIZE - 1)
            line[i++] = buf[0];
        ret = read(fd, buf, 1);
    }
    line[i] = '\0';
    if (ret <= 0 && i == 0)    // EOF sin datos -> no hay más líneas
    {
        free(line);
        return (NULL);
    }
    return (line);
}
```

---

### 7.3 Operaciones silenciosas

**Archivo:** `bonus/ft_apply_bonus.c`

Idénticas a las de `src/ft_ops_*.c` pero sin `write`. Se separan para no
contaminar la salida estándar durante la verificación.

```c
void ft_apply_push(t_stack **from, t_stack **to)
{
    t_stack *tmp;

    if (!*from)
        return ;
    tmp    = *from;
    *from  = tmp->next;
    tmp->next = *to;
    *to    = tmp;
}
```

---

### 7.4 Despacho de operaciones por nombre

**Archivo:** `bonus/ft_exec_op_bonus.c`

Recibe el nombre de la operación como cadena y llama a la función correspondiente.
Devuelve `1` si la operación es válida, `0` si es desconocida.

```c
// Comparación de cadenas sin usar strcmp
static int ft_streq(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] == s2[i]);
}

int ft_exec_op(char *op, t_stack **a, t_stack **b)
{
    if (!op || !op[0]) return (0);
    if      (ft_streq(op, "sa"))  ft_apply_swap(a);
    else if (ft_streq(op, "sb"))  ft_apply_swap(b);
    else if (ft_streq(op, "ss")) { ft_apply_swap(a); ft_apply_swap(b); }
    else if (ft_streq(op, "pa"))  ft_apply_push(b, a);
    else if (ft_streq(op, "pb"))  ft_apply_push(a, b);
    else if (ft_streq(op, "ra"))  ft_apply_rotate(a);
    else if (ft_streq(op, "rb"))  ft_apply_rotate(b);
    else if (ft_streq(op, "rr")) { ft_apply_rotate(a); ft_apply_rotate(b); }
    else if (ft_streq(op, "rra")) ft_apply_rrotate(a);
    else if (ft_streq(op, "rrb")) ft_apply_rrotate(b);
    else if (ft_streq(op, "rrr")){ ft_apply_rrotate(a); ft_apply_rrotate(b); }
    else return (0);              // instrucción desconocida
    return (1);
}
```

---

### 7.5 Función `main` del checker

**Archivo:** `bonus/checker_bonus.c`

```c
int main(int argc, char **argv)
{
    t_stack *a    = NULL;
    t_stack *b    = NULL;
    char    *line;

    ft_parse_args(argc, argv, &a, &b);  // reutiliza el parser de push_swap

    line = ft_get_line(0);
    while (line)
    {
        if (!ft_exec_op(line, &a, &b))  // instrucción inválida
        {
            free(line);
            ft_free_stack(&a);
            ft_free_stack(&b);
            write(2, "Error\n", 6);
            return (1);
        }
        free(line);
        line = ft_get_line(0);
    }

    // A debe estar ordenada por value y B debe estar vacía
    if (ft_is_sorted_val(a) && !b)
        write(1, "OK\n", 3);
    else
        write(1, "KO\n", 3);

    ft_free_stack(&a);
    ft_free_stack(&b);
    return (0);
}
```

> El checker comprueba por **`value`** (no por `index`) porque no llama a
> `ft_assign_index`. Los valores son los originales del usuario.

---

## 8. Makefile explicado

```makefile
NAME    = push_swap
CHECKER = checker
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./libft

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

# Fuentes de push_swap
SRCS = src/ft_main.c src/ft_parse.c src/ft_parse_utils.c \
       src/ft_stack_utils.c src/ft_ops_swap.c src/ft_ops_push.c \
       src/ft_ops_rotate.c src/ft_ops_rrotate.c \
       src/ft_index.c src/ft_sort.c src/ft_sort_small.c

# Fuentes del checker (comparte parse y stack con push_swap)
BONUS_SRCS = bonus/checker_bonus.c bonus/ft_apply_bonus.c \
             bonus/ft_exec_op_bonus.c bonus/ft_get_line_bonus.c \
             src/ft_parse.c src/ft_parse_utils.c src/ft_stack_utils.c

OBJS       = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft -o $(CHECKER)

$(LIBFT):
$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
$(MAKE) -C $(LIBFT_DIR) clean
rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
$(MAKE) -C $(LIBFT_DIR) fclean
rm -f $(NAME) $(CHECKER)

re: fclean all

.PHONY: all bonus clean fclean re
```

**Puntos clave**:

- El checker comparte `ft_parse.c`, `ft_parse_utils.c` y `ft_stack_utils.c`
  con `push_swap` para no duplicar código.
- La regla `%.o: %.c` compila cada `.c` en su propio `.o` en el mismo directorio.
- `-Wall -Wextra -Werror` convierte todos los warnings en errores.

---

## 9. Testing y verificación

### Pruebas básicas

```bash
# Sin argumentos -> no imprime nada
./push_swap

# Un solo elemento -> no imprime nada
./push_swap 42

# Ya ordenado -> no imprime nada
./push_swap 1 2 3

# Caso simple
./push_swap 3 1 2
# Salida: ra

# Error: duplicado
./push_swap 1 2 1
# stderr: Error

# Error: overflow
./push_swap 2147483648
# stderr: Error
```

### Verificación con el checker

```bash
make bonus

ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG
# Debe imprimir: OK
```

### Contar el número de pasos

```bash
# Para 100 números (debe ser <= 700 para nota máxima)
./push_swap $(shuf -i 1-100 -n 100 | tr '\n' ' ') | wc -l

# Para 500 números (debe ser <= 5500 para nota máxima)
./push_swap $(shuf -i 1-500 -n 500 | tr '\n' ' ') | wc -l
```

### Script de test automatizado

```bash
#!/bin/bash
ERRORS=0
for i in $(seq 1 100); do
    ARG=$(shuf -i -10000-10000 -n 100 | tr '\n' ' ')
    RESULT=$(./push_swap $ARG | ./checker $ARG)
    if [ "$RESULT" != "OK" ]; then
        echo "FALLO con: $ARG"
        ERRORS=$((ERRORS + 1))
    fi
done
echo "Errores: $ERRORS / 100"
```

---

## 10. Errores frecuentes y cómo evitarlos

### 1. Fugas de memoria

**Regla**: todo `malloc` debe tener su `free` correspondiente.

- Pasa siempre `**` a las funciones que liberan para poder asignar `NULL`.
- Llama a `ft_free_stack` antes de cualquier `exit` o `return` en `main`.
- Verifica con `valgrind --leak-check=full ./push_swap 3 1 2`.

### 2. Desbordamiento de entero

- Usa `long` en `ft_atol` y compara el resultado contra `INT_MAX` / `INT_MIN`
  antes de hacer el cast a `int`.
- Entradas como `2147483648` o `-2147483649` deben producir `Error`.

### 3. Argumentos vacíos o de solo espacios

- `./push_swap ""` y `./push_swap "   "` no deben producir error ni instrucciones:
  salida completamente vacía.

### 4. El checker verifica `value`, no `index`

- El checker no llama a `ft_assign_index`, así que ordena por `value` directamente.
- La función `ft_is_sorted_val` del checker compara `value`, no `index`.

### 5. `ss`, `rr`, `rrr` siempre imprimen

- Aunque una de las pilas tenga un solo elemento, la instrucción combinada siempre
  imprime su nombre. No pongas el `write` dentro de un `if` de tamaño.

### 6. Número fijo de pasos del radix sort

El radix sort binario produce exactamente `max_bits × n` operaciones independientemente
de la permutación de entrada. Para n=100 esto da ~1 084 pasos (superior al límite
de 700 para nota máxima). Para mejorar la puntuación habría que implementar un
algoritmo más eficiente como el algoritmo "turk" (greedy con coste mínimo por
elemento).

---

*Repositorio: [FranciscoLi2000/Push-swap](https://github.com/FranciscoLi2000/Push-swap)*
