# Turtle-Like-Module
API Development for work with Turtle Graphics in C OpenGL

---


Программа реализует набор функций (API) для работы с Turtle Graphics на базе библиотеки OpenGL.  

**Краткое описание:**
1) Всё рисование графики выполняется неким объектом (или несколькими), который находится на холсте. Причем данные объекты должны реализовывать следующие базовые действия.
2) Повернуть на указанный угол налево \\ направо.
3) Переместиться вперёд и оставить след.
4) Переместиться вперёд, не оставляя след.
5) Положить текущее положение в стек.
6) Встать на место из верхушки стека.

**API:**
* **Структура `TDrawer{x, y, α}`**, где x, y – координаты объекта на холсте; α – угол поворота против часовой стрелки относительно оси Ox, то есть то направление, куда «смотрит» объект. При α = 0 объект смотрит вдоль оси Ох.

* **Структура `Tstack_Drawer{MAX, stack, tos}`**, где MAX – вместимость стека; stack – массив структур TDrawer размера MAX; tos – индекс верхнего элемента стека в массиве stack.

* **Метод объекта `InitDrawer(obj, x, y, α)`**, где obj – экземпляр структуры TDrawer; x, y – координаты на холсте; α – угол поворота относительно оси Ox, то есть то направление, куда «смотрит» объект. Данный метод, используя аналогию с Объектно-ориентированным программированием (ООП), реализует функционал конструктора для типа TDrawer. То есть, присваивает значения x, y, α экземпляру obj структуры TDrawer.

* **Метод объекта `setD(obj1, obj2)`**, где obj1 и obj2 – экземпляры (скорее всего различные) структуры TDrawer. Метод реализует присваивание атрибутов obj1 к obj2.

* **Метод объекта `putToD(x, y, α, obj)`**, где x, y, α, obj обозначают те же понятия, что и выше. Метод перемещает объект в указанную точку (x, y) на холсте с заданным поворотом α относительно оси Ox.

* **Метод объекта `forwardD(f, obj)`** – аналогичный прошлому метод, за исключением того, что объект obj при перемещении оставляет след. То есть рисуется линия длины f от начальной точки, в которой находится obj, до конечной точки, которая вычисляется через проекцию f (так как известен угол поворота obj) на оси Ox и Oy и прибавлением значений проекций к текущим координатам obj соответственно.

* **Метод объекта `moveToD(f, obj)`**, где f – вещественное число. Метод реализует перемещение объекта obj на f пикселей вперёд, не оставляя след. Конечные координаты вычисляются по аналогии с методом forwardD().

* **Метод объекта `rightD(a, obj)`** a – поворот объекта obj направо на угол α, то есть по часовой стрелке, относительно оси Ox.

* **Метод объекта `leftD(a, obj)`** a – поворот объекта obj налево на угол α, то есть против часовой стрелке, относительно оси Ox.

*  **Метод стека `InitDrawerStack(stack_obj, tos, MAX)`**, где stack_obj – экземпляр структуры Tstack_Drawer; tos – верхушка стека; МАХ – максимальное количество элементов в стеке. Выполняет инициализацию экземпляра структуры Tstack_Drawer. По аналогии с ООП: конструктор структуры Tstack_Dtawer.

* **Метод стека `push_Drawer(stackD, obj)`**, где stackD – стек экземпляров структуры TDrawer; obj – некоторый объект TDrawer. Метод кладёт объект obj в верхушку стека. То есть obj как бы «запоминает», где он находится.

* **Метод стека `pop_Drawer(stackD, obj)`** – метод  достаёт из верхушки стека stackD экземпляр TDrawer и присваивает значения его атрибутов объекту obj. То есть obj возвращается на место, где был последний элемент стека.

Наличие стека очень полезно, когда требуется, например, нарисовать дерево

Пример использования API (выполняется в окружении OpenGL):
```C
TDrawer d;
InitDrawer(&d, 300, 300, 0);

// Circle
for (int i = 0; i < 50; i++)
{
	forwardD(20, &d);
	leftD(7.2, &d);
}

// Pentagon
float n = 5;
putToD(0,0, 360/n, &d);
for (int i = 0; i < n; i++)
{
	forwardD(200, &d);
	rightD(360/n, &d);
}

// Sample dotted line
for (int i = 0; i < 100; i++)
{
	if (i % 2 == 0)
		forwardD(i/2, &d2);
	else
		moveToD(i/2, &d2);
	rightD(7.2/2, &d2);
}

// Sample filled line 
for (int i = 0; i < 101; i++)
{
	forwardD(i/2, &d2);
	leftD(7.2/2, &d2);
}
```

*Результат выполнения*

![Pasted image 20230512220505](https://github.com/rusanoph/Turtle-Like-Module/assets/70108263/debd6d7d-5bfd-458b-ae40-1fa53939ef59)