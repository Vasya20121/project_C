#include <stdio.h>;
#include <stdlib.h>;
#include <locale.h>;
#include "windows.h";
int n;
typedef struct
{
    float x;
    float y;
} Point2D;
typedef struct
{
    Point2D a;
    Point2D b;
} Segment2D;
typedef struct /* Уравнение прямой имеет вид: Ax+By+C = 0*/
{
    float A;
    float B;
    float C;
} Line2D;
typedef struct
{
    Point2D pt[10];
} Polyline2D;
void sum_vectors()
{ /* используем структуру Point2D для того, чтобы задать координаты векторов*/
    Point2D a, b; /*соответственно 2 отрезка a и b */
    printf("Input coords of vector a: ");
    scanf("%f%f", &a.x, &a.y);
    printf("Input coords of vector b: ");
    scanf("%f%f", &b.x, &b.y);
    printf("\na=(%.2f, %.2f)", a.x, a.y);
    printf("\nb=(%.2f, %.2f)", b.x, b.y);
    printf("\nvector a+b=(%.2f, %.2f)", a.x+b.x, a.y+b.y);
}
void mult()/*Произведение двух векторов, соответственно, они состоят из 3 координат
(не знаю причем тут 2д структуры, поэтому в тупую задаем по 3 переменных для каждого вектора)*/
{
    float x1,x2,y1,y2,z1,z2;
    printf("Input coords of vector a: ");
    scanf("%f%f%f", &x1, &y1, &z1);
    printf("Input coords of vector b: ");
    scanf("%f%f%f", &x2, &y2, &z2);
    printf("\na=(%.2f, %.2f, %.2f)", x1, y1, z1);
    printf("\nb=(%.2f, %.2f, %.2f)", x2, y2, z2);
    printf("\n[a*b]=(%.2f, %.2f, %.2f)", y1*z2-y2*z1, x1*z2-x2*z1, x1*y2-x2*y1);
};
void multS()
{
    Point2D a, b; /*соответственно 2 вектора a и b */
    printf("Input coords of vector a: ");
    scanf("%f%f", &a.x, &a.y);
    printf("Input coords of vector b: ");
    scanf("%f%f", &b.x, &b.y);
    printf("\na=(%.2f, %.2f)", a.x, a.y);
    printf("\nb=(%.2f, %.2f)", b.x, b.y);
    printf("\nvector a*b=%2.f", a.x*b.x+a.y*b.y);
};
int intersaction_line_segment(Segment2D l1, Line2D l2)
{
    float x0, x1, y0, y1;
    float det1, det2, det3, x, y;
    float a1, b1, c1;
    float a2, b2, c2;
    x0 = l1.a.x;
    x1 = l1.b.x;
    y0 = l1.a.y;
    y1 = l1.b.y;
    /* Пряма задана в форматі Ax + By + C = 0 */
    a1 = l2.A; /* A */
    b1 = l2.B; /* B */
    c1 = l2.C; /* C */

    /* Будуємо по 2 точкам пряму в форматі Ax + By + C = 0 */
    a2 = l1.b.y - l1.a.y; /* y1-y0*/
    b2 = l1.b.x - l1.a.x; /* x1-x0*/
    c2 = l1.a.x*l1.b.y - l1.b.x*l1.a.y; /* x1*y0 - x0*y1 */
    /* Розвязок систеи методом Крамера */
    det1 = a1*b2 - a2*b1;
    if (det1 == 0)
        return 0; /* Немає перетину */
    det2 = (-c1)*b2 - (-c2)*b1;
    det3 = a1*(-c2) - a2*(-c1);

    x = -det2/det1;
    y = -det3/det1;
    printf("%.2f %.2f\n", x, y);
    if(x >= x0 && x <= x1 && y >= y0 && y <= y1) printf("%.2f %.2f\n", x, y); /* Шукана точка перетину */
    else return 0;

    return 1;
}

int intersaction_segments(Segment2D l1, Segment2D l2)
{

    float det1, det2, det3, x, y;
    float a1, b1, c1;
    float a2, b2, c2;

    /* Будуємо по 2 точкам пряму в форматі Ax + By + C = 0 */
    a1 = l1.b.y - l1.a.y; /* y2-y1*/
    b1 = l1.b.x - l1.a.x; /* x2-x1*/
    c1 = l1.b.x*l1.a.y - l1.a.x*l1.b.y; /* x2*y1 - x1*y2 */

    /* Будуємо по 2 точкам пряму в форматі Ax + By + C = 0 */
    a2 = l2.b.y - l2.a.y; /* y2-y1*/
    b2 = l2.b.x - l2.a.x; /* x2-x1*/
    c2 = l2.b.x*l2.a.y - l2.a.x*l2.b.y; /* x2*y1 - x1*y2 */

    /* Розвязок систеи методом Крамера */
    det1 = a1*b2 - a2*b1;
    if (det1 == 0)
        return 0; /* Немає перетину */
    det2 = (-c1)*b2 - (-c2)*b1;
    det3 = a1*(-c2) - a2*(-c1);

    x = det2/det1;
    y = det3/det1;
    if(check_intersection(l1, l2) == 1)
        {
            printf("%.2f %.2f\n", x, y); /* Шукана точка перетину */
        }

    return 1;
}
int check_intersection(Segment2D l1, Segment2D l2) /* Проверка на пересечение отрезков с помощью векторных произведений на плоскости
        (нам нужно лишь координата z) */
{
    Point2D AB, CD, AC, CA, AD, CB; /* Наши нужные вектора */
    float v1, v2, v3, v4; /* Векторные произвидения */
    AB.x = l1.b.x - l1.a.x;
    AB.y = l1.b.y - l1.a.y;
    AC.x = l2.a.x - l1.a.x;
    AC.y = l2.a.y - l1.a.y;
    CD.x = l2.b.x - l2.a.x;
    CD.y = l2.b.y - l2.a.y;
    CA.x = l1.a.x - l2.a.x;
    CA.y = l1.a.y - l2.a.y;
    AD.x = l2.b.x - l1.a.x;
    AD.y = l2.b.y - l1.a.y;
    CB.x = l1.b.x - l2.a.x;
    CB.y = l1.b.y - l2.a.y;
    v1 = CD.x*CA.y - CD.y*CA.x;
    v2 = CD.x*CB.y - CD.y*CB.x;
    v3 = AB.x*AC.y - AB.y*AC.x;
    v4 = AB.x*AD.y - AB.y*AD.x;
    if(v1*v2<0 && v3*v4<0) return 1;
    else return 0;
}
int intersaction_lines(Line2D l1, Line2D l2)
{
    float det1, det2, det3, x, y;
    float a1, b1, c1;
    float a2, b2, c2;

    /* Пряма задана в форматі Ax + By + C = 0 */
    a1 = l2.A; /* A2 */
    b1 = l2.B; /* B2 */
    c1 = l2.C; /* C2 */

    /* Будуємо по 2 точкам пряму в форматі Ax + By + C = 0 */
    a2 = l1.A; /* A1 */
    b2 = l1.B; /* B1 */
    c2 = l1.C; /* C1 */
    /* Розвязок систеи методом Крамера */
    det1 = a1*b2 - a2*b1;
    if (det1 == 0)
        return 0; /* Немає перетину */
    det2 = (-c1)*b2 - (-c2)*b1;
    det3 = a1*(-c2) - a2*(-c1);

    x = det2/det1;
    y = det3/det1;

    printf("%.2f %.2f\n", x, y); /* Шукана точка перетину */

    return 1;
}
int main(void)
{
    SetConsoleCP(1251); /*Для вывода украинских символов*/
    SetConsoleOutputCP(1251);
    int choice; /*Вибор функции */
    printf("1. Функція додавання векторів\n2. Функція векторного добутку\n3. Функція скалярного добутку\n");
    printf("4. Перетин прямої та відразка\n5. Перетин відрізків\n6. Перетин прямих\n");
    scanf("%d", &choice);
    if(choice == 1) sum_vectors();
    else if(choice == 2) mult();
    else if(choice == 3) multS();
    else if(choice == 4)
        {
        Line2D line;
        Segment2D segment;
        printf("Введіть координати прямої (A, B, C) i відрізка (точки а і b) ");
        scanf("%f%f%f", &line.A, &line.B, &line.C);
        scanf("%f%f%f%f", &segment.a.x, &segment.a.y, &segment.b.x, &segment.b.y);
        intersaction_line_segment(segment, line);
        }
    else if(choice == 5)
        {
        Segment2D segment1, segment2;
        printf("Введіть координати відрізків (точки а і b) ");
        scanf("%f%f%f%f", &segment1.a.x, &segment1.a.y, &segment1.b.x, &segment1.b.y);
        scanf("%f%f%f%f", &segment2.a.x, &segment2.a.y, &segment2.b.x, &segment2.b.y);
        intersaction_segments(segment2, segment1);
        }
    else if(choice == 6)
        {
        Line2D line1, line2;
        printf("Введіть прямої(А B C): ");
        scanf("%f%f%f", &line1.A, &line1.B, &line1.C);
        scanf("%f%f%f", &line2.A, &line2.B, &line2.C);
        intersaction_lines(line1, line2);
        }
    else printf("bad choice");
    return 0;

}

