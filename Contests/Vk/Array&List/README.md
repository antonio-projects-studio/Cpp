# [Массивы и списки](https://cups.online/ru/workareas/education_1914/958/1719)

## Задание 1

На вход подается не отсортированный массив и некоторое число element. \
Необходимо написать функцию, которая вернет количество элементов, которые не равны числу element. \
При этом входной массив после работы функции не должен содержать в себе значения равные element.

**Пример**
| **Входные данные:** | **Выходные данные:** |
|---------------------|----------------------|
| 4                   | 1                    |
| 8 8 8 9             |                      |
| 8                   |                      |

## Задание 2

В школе прошел экзамен по математике. Несколько человек списали решения и были замечены. Этим школьникам поставил 0 баллов. Задача: есть массив с оценками, среди которых есть 0. Необходимо все оценки, равные нулю перенести в конец массива, чтобы все такие школьники оказались в конце списка.

**Пример**
| **Входные данные:**     | **Выходные данные:**    |
|-------------------------|-------------------------|
| 9                       | 33 57 88 60 80 99 0 0 0 |
| 0 33 57 88 60 0 0 80 99 |                         |

## Задание 3

Дан не отсортированный массив целых чисел. Необходимо перенести в начало массива все четные числа, сохраняя их очередность. То есть если 8 стояла после 6, то после переноса в начало, он по-прежнему должна стоять после 6

**Пример**
| **Входные данные:** | **Выходные данные:** |
|---------------------|----------------------|
| 7                   | 2 4 8 1 11 3 9       |
| 3 2 4 1 11 8 9      |                      |