#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

struct Course
{
    char name[50];
    char instructor[50];
    char tema[50];
    double rating;
    double price;
    int time;
};

int SearchName(struct Course* course, int courseCount, char* searchName);
int SearchPrice(struct Course* course, int courseCount, double price);
void bubbleSort(struct Course* course, int courseCount);
int WriteFile(struct Course* course, int courseCount);
int ReadFile(struct Course* course, int courseCount);

int main()
{
    setlocale(LC_ALL, "RUS");
    struct Course course[100];
    int courseCount = 0;
    int choice;
    system("chcp 1251");
    do
    {
        printf("Добро пожаловать в программу управления образовательными курсами!\n");
        printf("_________________________________________________________________\n");
        printf("Меню:\n");
        printf("1. Добавить курс\n");
        printf("2. Поиск курса по названию\n");
        printf("3. Поиск курса по стоимости\n");
        printf("4. Сортировать курсы по рейтингу\n");
        printf("5. Записать в файл\n");
        printf("6. Вывести содержимое файла\n");
        printf("7. Выйти из программы\n");
        printf("-----------------------------------------------------------------\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            if (courseCount < 100)
            {
                printf("Введите название курса: ");
                fgets(course[courseCount].name, sizeof(course->name), stdin);
                printf("Введите имя преподавателя: ");
                fgets(course[courseCount].instructor, sizeof(course->instructor), stdin);
                printf("Введите тему курса: ");
                fgets(course[courseCount].tema, sizeof(course->tema), stdin);
                printf("Введите рейтинг курса: ");
                scanf("%lf", &course[courseCount].rating);
                getchar();
                printf("Введите стоимость курса: ");
                scanf("%lf", &course[courseCount].price);
                getchar();
                printf("Введите длительность курса (в часах): ");
                scanf("%d", &course[courseCount].time);
                getchar();
                courseCount++;
                printf("Курс успешно добавлен!\n");
            }
            else
            {
                printf("Достигнуто максимальное количество курсов!\n");
            }
            break;
        case 2:
            if (courseCount > 0)
            {
                char searchName[50];
                printf("Введите название для поиска: ");
                fgets(searchName, sizeof(searchName), stdin);
                int found = SearchName(course, courseCount, searchName);
                if (found != -1)
                {
                    printf("------------------------------------------------\n");
                    printf("Название: %s", course[found].name);
                    printf("Преподаватель: %s", course[found].instructor);
                    printf("Тема: %s", course[found].tema);
                    printf("Рейтинг: %.2f\n", course[found].rating);
                    printf("Стоимость: %.2f\n", course[found].price);
                    printf("Длительность: %d\n", course[found].time);
                    printf("------------------------------------------------\n");
                }
                else
                {
                    printf("Программа с таким названием не найдена.\n");
                }
            }
            else
            {
                printf("База данных пуста.\n");
            }
            break;
        case 3:
            if (courseCount > 0)
            {
                double price;
                printf("Введите цену для поиска: ");
                scanf("%lf", &price);
                int count = SearchPrice(course, courseCount, price);
                if (count > 0)
                {
                    for (int i = 0; i < courseCount; i++)
                    {
                        if (course[i].price == price)
                        {
                            printf("------------------------------------------------\n");
                            printf("Название: %s", course[i].name);
                            printf("Преподаватель: %s", course[i].instructor);
                            printf("Тема: %s", course[i].tema);
                            printf("Рейтинг: %.2f\n", course[i].rating);
                            printf("Стоимость: %.2f\n", course[i].price);
                            printf("Длительность: %d\n", course[i].time);
                            printf("------------------------------------------------\n");
                        }
                    }
                }
                else
                {
                    printf("Программы с ценой до %.2lf не найдены.\n", price);
                }
            }
            else
            {
                printf("База данных пуста.\n");
            }
            break;
        case 4:
            if (courseCount == 0)
            {
                printf("Нет доступных курсов для сортировки\n");
            }
            else
            {
                bubbleSort(course, courseCount);
                printf("Курсы успешно отсортированы по рейтингу (от лучшего к худшему)!\n");
                for (int i = 0; i < courseCount; i++)
                {
                    printf("------------------------------------------------\n");
                    printf("Название: %s", course[i].name);
                    printf("Преподаватель: %s", course[i].instructor);
                    printf("Тема: %s", course[i].tema);
                    printf("Рейтинг: %.2f\n", course[i].rating);
                    printf("Стоимость: %.2f\n", course[i].price);
                    printf("Длительность: %d\n", course[i].time);
                    printf("------------------------------------------------\n");
                }
            }
            break;
        case 5:
            if (courseCount > 0)
            {
                int result = WriteFile(course, courseCount);
                if (result == 0)
                {
                    printf("Не удалось записать данные в файл.\n");
                }
                else
                {
                    printf("Данные успешно записаны в файл.\n");
                }
            }
            else
            {
                printf("База данных пуста. Нечего записывать в файл.\n");
            }
            break;
        case 6:
            if (courseCount > 0)
            {
                int result = ReadFile(course, courseCount);
                if (result == 0)
                {
                    printf("Данные успешно прочитаны из файла.\n");
                }
                else
                {
                    printf("Не удалось прочитать данные из файла.\n");
                }
            }
            else
            {
                printf("База данных пуста. Нечего читать из файла.\n");
            }
            break;
        case 7:
            printf("Выход из программы\n");
            break;
        default:
            printf("Некорректный выбор. Пожалуйста, попробуйте снова\n");
            break;
        }
    } while (choice != 7);
}

void bubbleSort(struct Course* course, int courseCount)
{
    int i, j;
    struct Course temp;
    for (i = 0; i < courseCount - 1; i++)
    {
        for (j = 0; j < courseCount - i - 1; j++)
        {
            if (course[j].rating < course[j + 1].rating)
            {
                temp = course[j];
                course[j] = course[j + 1];
                course[j + 1] = temp;
            }
        }
    }
}

int SearchName(struct Course* course, int courseCount, char* searchName)
{
    for (int i = 0; i < courseCount; i++)
    {
        if (strstr(course[i].name, searchName) != NULL)
        {
            return i;
        }
    }
    return -1;
}

int SearchPrice(struct Course* course, int courseCount, double price)
{
    int count = 0;
    for (int i = 0; i < courseCount; i++)
    {
        if (course[i].price == price)
        {
            count++;
        }
    }
    return count;
}

int WriteFile(struct Course* course, int courseCount)
{
    FILE* file = fopen("course.txt", "w");
    if (file == NULL)
    {
        return 0;
    }
    for (int i = 0; i < courseCount; i++)
    {
        fprintf(file, "Название: %s", course[i].name);
        fprintf(file, "Преподаватель: %s", course[i].instructor);
        fprintf(file, "Тема: %s", course[i].tema);
        fprintf(file, "Рейтинг: %.2f\n", course[i].rating);
        fprintf(file, "Стоимость: %.2f\n", course[i].price);
        fprintf(file, "Длительность: %d\n", course[i].time);
        fprintf(file, "------------------------------\n");
    }
    fclose(file);
    return 1;
}

int ReadFile(struct Course* course, int courseCount)
{
    FILE* file;
    char filename[] = "course.txt";
    char buffer[1000];
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Ошибка при открытии файла");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}