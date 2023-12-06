#include <iostream>
using namespace std;
int main() {
    //int mas[10];
    char str1[] = "%9f";
    float t = 4.127;
    int a = 2;
    float result;
    cout << 434343;
    __asm {
        /*
        lea esi, mas;
        mov ecx, 10;
            l2: 
        
        push esi;
        push ecx;
        push esi;
        lea eax, str1
            push eax;
        call scanf;
        add esp, 8;
        pop ecx;
        pop esi
        add esi, 4;
    
    loop l2;
        sub esi, 40;
        mov ecx, 10;
        xor eax, eax
        lea esi, mas
        mov ecx, 10
            l3:
        push esi
        push ecx
        push[esi]
        lea eax, str1
        push eax
        call printf
        add esp, 8
        pop ecx
        pop esi
        add esi, 4
            loop l3
        */
        /*
        fld t
        fidiv a
        fstp result

        lea esi, result
        push esi
        push [esi]
        lea eax, str1
        push eax
        call printf
        pop esi
        add esp, 8
    */ 
        /*fld t
        fidivr a
        fstp result
        movss xmm0, [result]
        call printf
        */
        sub esp, 8
        lea ebx, str1
        fld t
        fstp qword ptr[esp] //Согласно соглашению о вызове cdecl надо приводить к double, а тот двумя частями помещать в стек
        //push eax
        //push edx
        push ebx
        call printf
        //pop ebx
        add esp, 12
  
    }

    return 0;
    //system("pause");
}