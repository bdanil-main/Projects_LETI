format PE console
entry start
include '%fasminc%/win32wxp.inc'
section '.data' data readable writeable
        s_greetings db 'Please, enter 5 unsigned decimal numbers from 0 to 255 inclusively:', 0x0A, 0
        s_enter db 'Entered numbers (decimal):', 0x0A, 0
        s_result db 'Result (decimal):', 0x0A, 0
        s_press_any db 'Press any key...', 0x0A, 0
        s_empty db 0x0A, 0
        sp_In db '%hhu', 0
        sp_Out db '%hhu ', 0
        sp_S db '%s', 0
        N db 5 dup (?)
section '.text' code readable executable
        start:
                cinvoke printf, sp_S, s_greetings;Please, enter 5 unsigned decimal numbers from 0 to 255 inclusively:
                xor ebx, ebx;счетчик
                mov esi, N;массив
                input:;\\ВВОД ЧИСЕЛ\\\
                cinvoke scanf, sp_In, esi
                inc esi
                inc ebx
                cmp ebx, 5
                jne input;////////////
                cinvoke printf, sp_S, s_empty
                cinvoke printf, sp_S, s_empty
                cinvoke printf, sp_S, s_enter;Entered numbers (decimal):
                xor ebx, ebx;счетчик
                mov esi, N;массив
                output_1:;\\ВЫВОД ЧИСЕЛ\\\
                movzx eax, byte [esi]
                cinvoke printf, sp_Out, eax
                inc esi
                inc ebx
                cmp ebx, 5
                jne output_1;/////////////
                cinvoke printf, sp_S, s_empty
                ;num[i] = num[i] ^ Z | M & i;Treatment
                xor ebx, ebx;счетчик
                mov esi, N;массив
                treatment:;\\ОБРАБОТКА\\\
                movzx eax, byte [esi]
                xor al, 'Z'
                mov cl, 'M'
                and cl, bl
                or al, cl
                mov byte [esi], al
                inc esi
                inc ebx
                cmp ebx, 5
                jne treatment;///////////
                cinvoke printf, sp_S, s_empty
                cinvoke printf, sp_S, s_result;Result (decimal):
                xor ebx, ebx;счетчик
                mov esi, N;массив
                output_2:;\\РЕЗУЛЬТАТ\\\
                movzx eax, byte [esi]
                cinvoke printf, sp_Out, eax
                inc esi
                inc ebx
                cmp ebx, 5
                jne output_2;///////////
                cinvoke printf, sp_S, s_empty
                cinvoke printf, sp_S, s_empty
                cinvoke printf, sp_S, s_press_any;Press any key...
                cinvoke getch
                invoke ExitProcess, dword 0
section '.idata' import data readable writeable
        library kernel32, 'KERNEL32.DLL', \
                msvcrt, 'MSVCRT.DLL'
        import kernel32, ExitProcess, 'ExitProcess'
        import msvcrt, printf, 'printf', \
                       getch, '_getch', \
                       scanf, 'scanf'