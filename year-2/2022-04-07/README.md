# Задачи за 7 апреля 2022 года
| Курс | Язык | Компилятор | Тема
|:-:|:-:|:-:|:-:|
| 2 | `C++` | `g++ --std=c++11` | Библиотека `deque` |

## `task1.cpp`
На вход подается последовательность чисел, маркером конца которой служит точка `.`. Необходимо записать в двунаправленную очередь `deque`, вывести ее в консоль. Затем создать очередь, в которой элементы лежат в обратном порядке, и снова вывести результат в консоль.

_Смотрите также: `task6.cpp`_

Пример:
```
Awaiting items... (full-stop terminates sequence)
1 8 -3 8 2 9 .
Sequence ended

Initial deque
1 8 -3 8 2 9 
Reversed deque
9 2 8 -3 8 1 
```

## `task2.cpp`
На вход подается последовательность чисел, маркером конца которой служит ноль `0`, а также некоторое целое число `N`. Необходимо записать ввод в двунаправленную очередь `deque`, после чего удалить числа, большие `N`.

Пример:
```
Awaiting items... (0 terminates sequence)
12 8 -8 -6 2 4 1 0
Sequence ended
Enter N: 4

Initial deque
12 8 -8 -6 2 4 1 
Modified deque
-8 -6 2 4 1 
```

## `task3.cpp`
На вход подается последовательность чисел, маркером конца которой служит ноль `0`. Необходимо проверить, симметрична ли последовательность. Симметрия соблюдается, когда n-ый элемент с начала равен n-ому элементу с конца.

Пример:
```
Awaiting items... (0 terminates sequence)
1 2 3 4 3 2 1 0
Sequence ended

Deque
1 2 3 4 3 2 1 
Symmetric
```

## `task4.cpp`
На вход подается последовательность строк, маркером конца которой служит точка `.`. Исключить из последовательности все строки, начинающиеся на букву `a`, после чего вывести первый элемент, последний элемент и длину новой последовательности.

Пример:
```
Awaiting items... (full-stop terminates sequence)
apple despair hope anger stress ambush set .
Sequence ended

Initial deque
apple despair hope anger stress ambush set 
Modified deque
despair hope stress set 

Length: 4
First element: despair
Last element: set
```

## `task5.cpp`
Создать структуру `Student`, в которой хранится фамилия, год рождения и группа студента. Сгенерировать и вывести список студентов в количестве, указанном пользователем. Затем показать студентов, год рождения которых совпадает с указанным пользователем.

Пример:
```
Amount of students: 4

Student List
Nibobo born in 1984 and studying in group 1062
Saboni born in 2002 and studying in group 1011
Sasasabo born in 1996 and studying in group 1086
Veboni born in 1998 and studying in group 1029

Filter by year: 2002
Born in 2002: 
Saboni from group 1011
```

## `task6.cpp`
Сгенерировать последовательность чисел в количестве, указанном пользователем, и записать в очередь. Вывести перевернутую очередь.

_Смотрите также: `task1.cpp`_

Пример:
```
Amount of numbers: 5
Queue
140 -190 -191 48 -68 
Reversed queue
-68 48 -191 -190 140 
```

## `task7.cpp`
Сгенерировать два списка с фамилиями клиентов, размер которых определяет пользователь. Создать общий список, добавляя все фамилии от конца к началу каждого из исходных списков.

Пример:
```
Amount of clients: 5
Deques
Bosanini Satuni Tuvetuboni Botusa Bobosa 
Vetutu Ninituve Nisanisatu Satunibo Tutuve 

Result
Bobosa Tutuve Botusa Satunibo Tuvetuboni Nisanisatu Satuni Ninituve Bosanini Vetutu
```
