#include "main.h"

int main() {
    initGraphics();
    startMainLoop();
    ElementList list = createMockListTrue();
    Entity tree = createTree(list);
    Result r = result(tree, 6);
    double res = r.value;
    printf("%lf", res);

    return 0;
}