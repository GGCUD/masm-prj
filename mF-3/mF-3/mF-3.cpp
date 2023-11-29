﻿/*Обработка одномерных массивов.
Обязательно! Реализация на ассемблере (можно встроенном). 
Ввод с клавиатуры и вывод делается исключительно в ассемблере. 
Вместо ввода с клавиатуры можно прикрутить рандом на ввод. 
Вне ассемблера разрешено только задания типов переменных. 
Переменные массива однобайтовые.

Дополнительная сложность – переменные размера двубайтовые (заработок доп.
баллов). 

Материалы:
https://hackware.ru/?p=8654#11

https://www.youtube.com/watch?v=XnHY4ais77A

https://www.i-assembler.ru/25/Text/Data.htm

В массиве из 10 чисел поделить все отрицательные элементы на
максимальный элемент массива.
 */

#include <iostream>
#include <fstream>

using namespace std;
int N = 10;

void in(int* mass);
void out(int* mass);
void math(int* mass);
void in(int* mass) {
	cout << "Введите 10 чисел" << endl;
	const char* F = "%d";	//объявляет F типа const char* и присваивает значение "%d" - форматная строкой, которая для форматирования вывода числа типа int.
	_asm
	{
		mov esi, mass	;в регистр esi помещается адрес массива mas
		mov ecx, N		;в регистр ecx помещается размер массива = 10

		c :				; точка начала цикла
		push ecx		;заносим значение 10 в стек, сохранение состояния
		push esi		;заносим в стек адрес текущего элемента массива ячейки для записи, сохранение состояния
		push F			;заносим формат с которым будет вызываться scanf

		call scanf		;вызов команды ввода элемента
		add esp, 8		;очистка стека
		pop ecx			;Извлечение операнда из стека,восстановление состояния
		add esi, 4		;переход к следующей ячейке
		loop c			; выполняет декремент, а затем проверяет его значение, если содержимое не
						;равно нулю, то осуществляется переход на метку с, иначе упрвление переходит к следующей после loop команде
					
	}
	out(mass);

}
void out(int* mass) {
	const char* F = "%4d ";	//вывод ячейки под одно число шириной 4
	int Number = N;			//инициализируем копию N
	_asm
	{
		mov esi, mass		; в регистр esi заносим адрес нулевого элемента массива mas
		mov ecx, Number		; инициализируем счетчик
		c :
		mov eax, [esi]		;в регистр eax заносим значение текущего элемента массива
		push eax			;заносим в стек адрес текущего элемента массива ячейки для записи
		push F				;заносим формат с которым будет вызываться вывод
		call printf			;вызов команды вывода того, что находится в стеке
		mov ecx, Number		;инициализируем заново счетчик
		dec Number			;уменьшаем значение Number на 1
		pop ebx				;Извлечение операнда из стека
		add esi, 4			;переход к следующей ячейке
		loop c
	}
	cout << endl;
}

void math(int *mass) {
	const char* F = "%4d";
	const char* F1 = "%4f";
	int Num = N;
	short int Max;
	float result;
	_asm {

		; --------------------------------Поиск максималочки------------
			;находим максимальный элемент массива
		mov ecx, 10		; кол - во элементов в массиве
		mov esi, mass	; адрес начала массива
		mov ax, [esi]	; сохраняем первый элемент в аккумулятор

		max_loop :
		cmp ax, [esi]	; сравниваем текущий элемент с максимальным
		jge not_max		; если текущий элемент больше или равен максимальному, то переходим к следующему элементу

		mov ax, [esi]	; иначе сохраняем текущий элемент как новый максимальный

		not_max :
		add esi, 4		; увеличиваем указатель на 2 байта(размер элемента массива)
		loop max_loop	; повторяем цикл, пока не пройдем все элементы массива


		
		; ----------------------------------------ДЕЛЕНИЕ-------------------------------------
		;--------------------------В ДЕЛЕНИЕ ВХОДИТ ВЫВОД ЭЛЕМЕНТА---------------------------
		mov esi, mass	;в esi адрес начала массива
		mov ecx, 10		;счетчик 
		start_loop:		

		movsx eax, [esi]
		cmp eax, 0			;Проверка если число положительное, то переходим по метке positive_value и деления не происходит
		jge positive_value
		fild dword ptr[esi]
		fidiv Max
		fstp result			;резултат деления записывается в отдельную переменную
		
		;--------------------------------ВЫВОД ОТРИЦАТЕЛЬНОГО РЕЗУЛЬТАТА---------------------------		
		//sub esp, 4
		//mov eax, offset result
		movss xmm0, [result]
		//push eax
		//push F1				
		call printf			
		mov ecx, Num		
		dec Num			
		//pop ebx

		cmp eax, 0
		jge negative_value

		positive_value:
		;--------------------------------ВЫВОД ПОЛОЖИТЕЛЬНОГО РЕЗУЛЬТАТА---------------------------
		mov eax, [esi]		
		push eax			
		push F				
		call printf			
		mov ecx, Num		
		dec Num			
		pop ebx

			negative_value:
		add esi, 4			
		loop start_loop

	}
	cout << endl << Max << endl << result << endl;
	//out(mass);
}

int main()
{
	setlocale(LC_ALL, "RUS");
    int* mass;
    mass = new int[N];
    in(mass);
    std::cout << std::endl;
	math(mass);
    
   // system("pause");
    delete[] mass;
    return 0;
}


