#include "test.h"

void testSyntax() {
    ElementList list0 = createMockListTrue();
    ElementList list1 = createMockListTrue1();
    ElementList list2 = createMockListTrue2();
    ElementList list3 = createMockListTrue3();
    ElementList list4 = createMockListTrue4();
    ElementList list5 = createMockListTrue5();
    ElementList list6 = createMockListTrue6();
    ElementList list7 = createMockListTrue7();
    ElementList list8 = createMockListTrue8();
    ERRORS err1 = syntaxChecker(createMockListFalse1());
    ERRORS err2 = syntaxChecker(createMockListFalse2());
    ERRORS err3 = syntaxChecker(createMockListFalse3());
    ERRORS err4 = syntaxChecker(createMockListFalse4());
    ERRORS err5 = syntaxChecker(createMockListFalse5());
    ERRORS err6 = syntaxChecker(createMockListFalse6());
    Entity tree0 = createTree(list0);
    Entity tree1 = createTree(list1);
    Entity tree2 = createTree(list2);
    Entity tree3 = createTree(list3);
    Entity tree4 = createTree(list4);
    Entity tree5 = createTree(list5);
    Entity tree6 = createTree(list6);
    Entity tree7 = createTree(list7);
    Entity tree8 = createTree(list8);
    return;
}

void testAnalyst() {

}

void testInterpreter() {
    ElementList list0 = createMockListTrue();
    ElementList list1 = createMockListTrue1();
    ElementList list2 = createMockListTrue2();
    ElementList list3 = createMockListTrue3();
    ElementList list4 = createMockListTrue4();
    ElementList list5 = createMockListTrue5();
    ElementList list6 = createMockListTrue6();
    ElementList list7 = createMockListTrue7();
    ElementList list8 = createMockListTrue8();
    Entity tree0 = createTree(list0);
    Entity tree1 = createTree(list1);
    Entity tree2 = createTree(list2);
    Entity tree3 = createTree(list3);
    Entity tree4 = createTree(list4);
    Entity tree5 = createTree(list5);
    Entity tree6 = createTree(list6);
    Entity tree7 = createTree(list7);
    Entity tree8 = createTree(list8);
    Result r0 = result(tree0, 6); // -0.96
    Result r1 = result(tree1, 2.5); // -31.5
    Result r2 = result(tree2, -5); // 26
    Result r3 = result(tree3, M_PI_4); //10.01
    Result r4 = result(tree4, 5); // 2.415
    Result r5 = result(tree5, 500); // 1000
    Result r6 = result(tree6, 0.5); // 0.46211
    Result r7 = result(tree7, 5); //DIVIDE_BY_ZERO
    Result r8 = result(tree8, -1); // NON_REAL_OPERATION
    printf("Test done");
}

ElementList createMockElement(TOKENS token, Valeur u) {
    ElementList list = (ElementList) malloc(sizeof(struct elementListSt));
    Element e;
    e.token = token;
    e.value = u;
    list->element = e;
    return list;
}

ElementList createMockListTrue() {
    // sin((2*x)+5)
    Valeur u1;
    u1.functions = SIN;
    ElementList list = createMockElement(FUNCTION, u1);
    Valeur u2;
    u2.real = 0.0f;
    list->nextElement = createMockElement(PAR_OPN, u2);
    list->nextElement->nextElement = createMockElement(PAR_OPN, u2);
    Valeur u3;
    u3.real = 2.0f;
    list->nextElement->nextElement->nextElement = createMockElement(REAL, u3);
    Valeur u4;
    u4.operators = MULTIPLY;
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(PAR_CLS, u4);
    Valeur u5;
    u5.operators = PLUS;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            OPERATOR,
            u5);
    Valeur u6;
    u6.real = 5;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            REAL, u6);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            PAR_CLS, u6);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListTrue1() {
    // ((3*x)+3)*3
    ElementList list;
    Valeur u1;
    u1.real = 3.0f;
    list = createMockElement(PAR_OPN, u1);
    Valeur u3;
    u3.operators = MULTIPLY;
    list->nextElement = createMockElement(PAR_OPN, u1);
    list->nextElement->nextElement = createMockElement(REAL, u1);
    list->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u1);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(PAR_CLS, u1);
    Valeur u2;
    u2.operators = PLUS;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR,
                                                                                                           u2);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            REAL, u1);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            PAR_CLS, u1);

    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            OPERATOR, u3);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            REAL, u1);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListTrue2() {
    // 5*(-x+1)
    ElementList list;
    Valeur u1;
    u1.real = 5.0f;
    list = createMockElement(REAL, u1);
    Valeur u2;
    u2.operators = MULTIPLY;
    list->nextElement = createMockElement(OPERATOR, u2);
    list->nextElement->nextElement = createMockElement(PAR_OPN, u2);
    Valeur u3;
    u3.operators = MINUS;
    list->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u3);
    Valeur u4;
    u4.operators = PLUS;
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u4);
    Valeur u5;
    u5.real = 1.0f;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(REAL, u5);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            PAR_CLS, u5);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListTrue3() {
    // -tan(-x+2.5)*1.45
    ElementList list;
    Valeur u1;
    u1.operators = MINUS;
    list = createMockElement(OPERATOR, u1);
    Valeur u2;
    u2.functions = TAN;
    list->nextElement = createMockElement(FUNCTION, u2);
    list->nextElement->nextElement = createMockElement(PAR_OPN, u2);
    list->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u1);
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u1);
    Valeur u3;
    u3.operators = PLUS;
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u3);
    Valeur u4;
    u4.real = 2.5f;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(REAL, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            PAR_CLS, u4);
    Valeur u5;
    u5.operators = MULTIPLY;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            OPERATOR, u5);
    Valeur u6;
    u6.real = 1.45f;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            REAL, u6);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListTrue4() {
    // 2.415
    ElementList list;
    Valeur u1;
    u1.real = 2.415;
    list = createMockElement(REAL, u1);
    list->nextElement = NULL;
    return list;
}

ElementList createMockListTrue5() {
    // 2*x
    ElementList list;
    Valeur u1;
    u1.real = 2.0f;
    list = createMockElement(REAL, u1);
    Valeur u2;
    u2.operators = MULTIPLY;
    list->nextElement = createMockElement(OPERATOR, u2);
    list->nextElement->nextElement = createMockElement(VARIABLE, u1);
    list->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListTrue6() {
    // tanh(x)
    Valeur u;
    u.functions = TANH;
    ElementList list = createMockElement(FUNCTION, u);
    list->nextElement = createMockElement(PAR_OPN, u);
    list->nextElement->nextElement = createMockElement(VARIABLE, u);
    list->nextElement->nextElement->nextElement = createMockElement(PAR_CLS, u);
    list->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListTrue7() {
    // 5/0
    Valeur u1;
    u1.real = 0.0f;
    Valeur u2;
    u2.real = 5.0f;
    ElementList list = createMockElement(REAL, u2);
    Valeur u3;
    u3.operators = DIVIDE;
    list->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement = createMockElement(REAL, u1);
    list->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListTrue8() {
    Valeur u1;
    u1.operators = SQRT;
    Valeur u2;
    u2.real = -1.0f;
    ElementList  list = createMockElement(FUNCTION, u1);
    list->nextElement = createMockElement(PAR_OPN, u1);
    list->nextElement->nextElement = createMockElement(VARIABLE, u1);
    list->nextElement->nextElement->nextElement = createMockElement(PAR_CLS, u1);
    list->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}
ElementList createMockListFalse1() {
    //*5x
    Valeur u1;
    u1.operators = MULTIPLY;
    ElementList list = createMockElement(OPERATOR, u1);
    Valeur u2;
    u2.real = 5.0f;
    list->nextElement = createMockElement(REAL, u2);
    list->nextElement->nextElement = createMockElement(VARIABLE, u2);
    list->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse2() {
    // cos3+x
    Valeur u1;
    u1.functions = SIN;
    ElementList list = createMockElement(FUNCTION, u1);
    Valeur u2;
    u2.real = 3.0f;
    list->nextElement = createMockElement(REAL, u2);
    Valeur u3;
    u3.operators = PLUS;
    list->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u3);
    list->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse3() {
    // 5*(3-x
    Valeur u1;
    u1.real = 5.0f;
    ElementList list = createMockElement(REAL, u1);
    Valeur u2;
    u2.operators = MULTIPLY;
    list->nextElement = createMockElement(OPERATOR, u2);
    list->nextElement->nextElement = createMockElement(PAR_OPN, u2);
    Valeur u3;
    u3.real = 3.0f;
    list->nextElement->nextElement->nextElement = createMockElement(REAL, u3);
    Valeur u4;
    u4.operators = MINUS;
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse4() {
    // )5-x(
    Valeur u1;
    u1.real = 0;
    ElementList list = createMockElement(PAR_OPN, u1);
    Valeur u2;
    u2.real = 5.0f;
    list->nextElement = createMockElement(REAL, u2);
    Valeur u3;
    u3.operators = MINUS;
    list->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u3);
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(PAR_OPN, u3);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}


ElementList createMockListFalse5() {
    // cos()
    Valeur u1;
    u1.functions = COS;
    ElementList list = createMockElement(OPERATOR, u1);
    list->nextElement = createMockElement(PAR_OPN, u1);
    list->nextElement->nextElement = createMockElement(PAR_CLS, u1);
    list->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse6() {
    // 5+*x
    Valeur u1;
    u1.real = 5.0f;
    ElementList list = createMockElement(REAL, u1);
    Valeur u2;
    u2.operators = PLUS;
    list->nextElement = createMockElement(OPERATOR, u2);
    Valeur u3;
    u3.operators = MULTIPLY;
    list->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u3);
    list->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}


double test_evaluation() { //test function of the program : creating a tree and returning the value of f(x)
    double res = 0; //Value to return
    Result r;
    Entity e = malloc(sizeof(struct entitySt));

    /*
    // sin(9) x ln(2x)
    e->right_operand = malloc(sizeof(struct entitySt)); //allocating memory to the tree
    e->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->right_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->left_operand = malloc(sizeof(struct entitySt));

    e->element.token = OPERATOR; //main node is an operator
    e->element.value.operators = MULTIPLY; // the value of this operator is a multiply
    e->right_operand->element.token = FUNCTION; //right node is a function
    e->right_operand->element.value.functions = LN; // value of this function
    e->right_operand->left_operand->element.token = OPERATOR; // left node of the function is an operator
    e->right_operand->left_operand->element.value.operators = MULTIPLY;
    e->right_operand->left_operand->right_operand->element.token = REAL;
    e->right_operand->left_operand->left_operand->element.token = VARIABLE;
    e->right_operand->left_operand->right_operand->element.value.real = 2;
    e->left_operand->element.token = FUNCTION; //left node is a function
    e->left_operand->element.value.functions = SIN; // value of this function
    e->left_operand->left_operand->element.token = REAL; // left node of this function is a real
    e->left_operand->left_operand->element.value.real = 9; //value of this real

    e->left_operand->right_operand = NULL; // assigning NULL to every sons of node without sons
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->left_operand = NULL;
    e->right_operand->left_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand->left_operand = NULL;
    */


    /*
    // exp(x) / cos(2x)
    e->right_operand = malloc(sizeof(struct entitySt)); //allocating memory to the tree
    e->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->right_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->left_operand = malloc(sizeof(struct entitySt));

    e->element.token = OPERATOR; //main node is an operator
    e->element.value.operators = DIVIDE; // the value of this operator is a divide
    e->right_operand->element.token = FUNCTION; //right node is a function
    e->right_operand->element.value.functions = COS; // value of this function
    e->right_operand->left_operand->element.token = OPERATOR; // left node of the function is an operator
    e->right_operand->left_operand->element.value.operators = MULTIPLY;
    e->right_operand->left_operand->right_operand->element.token = REAL;
    e->right_operand->left_operand->left_operand->element.token = VARIABLE;
    e->right_operand->left_operand->right_operand->element.value.real = 2;
    e->left_operand->element.token = FUNCTION; //left node is a function
    e->left_operand->element.value.functions = EXP; // value of this function
    e->left_operand->left_operand->element.token = VARIABLE; // left node of this function is a variable

    e->left_operand->right_operand = NULL; // assigning NULL to every sons of node without sons
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->left_operand = NULL;
    e->right_operand->left_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand->left_operand = NULL;
    */


    // sqrt(x) - 6^x

    e->left_operand = malloc(sizeof(struct entitySt)); //allocating memory to the tree
    e->right_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->right_operand = malloc(sizeof(struct entitySt));

    e->element.token = OPERATOR; //main node is an operator
    e->element.value.operators = MINUS; // the value of this operator is a minus
    e->left_operand->element.token = FUNCTION; //left node is a function
    e->left_operand->element.value.functions = SQRT; // value of this function
    e->left_operand->left_operand->element.token = VARIABLE; // left node of this function is a variable
    e->right_operand->element.token = OPERATOR; //right node is a function
    e->right_operand->element.value.functions = POWER; // value of this function
    e->right_operand->right_operand->element.token = REAL; // left node of this function is a real
    e->right_operand->right_operand->element.value.real = 6;
    e->right_operand->left_operand->element.token = VARIABLE; //right node of this function is a variable

    e->left_operand->right_operand = NULL; // assigning NULL to every sons of node without sons
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand = NULL;
    e->right_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand->left_operand = NULL;
    e->right_operand->right_operand->right_operand = NULL;


    r = result(e, 2); // calling the function that calculates f(x)
    res = r.value; //assigning the correct value to the returned value


    // free sqrt(x) - 6^x
    free(e->right_operand->left_operand);
    free(e->right_operand->right_operand);
    free(e->left_operand->left_operand);
    free(e->right_operand);
    free(e->left_operand);
    free(e);

    /*
    // free exp(x) / cos(2x)
    free(e->right_operand->left_operand->right_operand );
    free(e->right_operand->left_operand->left_operand );
    free(e->right_operand->left_operand );
    free(e->left_operand->left_operand );
    free( e->right_operand);
    free(e->left_operand);
    free(e);
    */

    return res;
}