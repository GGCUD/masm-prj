#include <stdio.h>

int main() {
    short array[] = { -3, 2, -6, 4, -9, 6, -12, 8, -15, 10 };
    int arraySize = sizeof(array) / sizeof(short);

    __asm {
        mov esi, offset array
        mov ecx, arraySize

        loopStart :
        cmp esi, offset array + (arraySize - 1) * 2
            je loopEnd

            mov ax, [esi]
            cmp ax, 0
            jge skipDivision

            mov edx, 0
            mov eax, [esi]
            mov ebx, -3
            idiv ebx
            push eax
            fild dword ptr[esp]
            add esp, 4
            fild dword ptr[offset negativeThree]
            fdivp st(1), st(0)
            fstp dword ptr[esi]

            skipDivision:
        add esi, 2
            loop loopStart

            loopEnd :
        mov esi, offset array
            mov ecx, arraySize

            loopStart2 :
        cmp esi, offset array + (arraySize - 1) * 2
            je loopEnd2

            mov ax, [esi]
            push eax
            call printf
            add esp, 4

            add esi, 2
            loop loopStart2

            loopEnd2 :
        fldz
            fstsw ax
            sahf
    }

    return 0;
}