#include "ui.h"
#include "tests.h"
#include <crtdbg.h>
#include <stdio.h>

int main()
{
    run_all_tests();
    printf("Tests passed!\n");
    main_ui();
    _CrtDumpMemoryLeaks();
}
