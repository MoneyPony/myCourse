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
        printf("����� ���������� � ��������� ���������� ���������������� �������!\n");
        printf("_________________________________________________________________\n");
        printf("����:\n");
        printf("1. �������� ����\n");
        printf("2. ����� ����� �� ��������\n");
        printf("3. ����� ����� �� ���������\n");
        printf("4. ����������� ����� �� ��������\n");
        printf("5. �������� � ����\n");
        printf("6. ������� ���������� �����\n");
        printf("7. ����� �� ���������\n");
        printf("-----------------------------------------------------------------\n");
        printf("������� ��� �����: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            if (courseCount < 100)
            {
                printf("������� �������� �����: ");
                fgets(course[courseCount].name, sizeof(course->name), stdin);
                printf("������� ��� �������������: ");
                fgets(course[courseCount].instructor, sizeof(course->instructor), stdin);
                printf("������� ���� �����: ");
                fgets(course[courseCount].tema, sizeof(course->tema), stdin);
                printf("������� ������� �����: ");
                scanf("%lf", &course[courseCount].rating);
                getchar();
                printf("������� ��������� �����: ");
                scanf("%lf", &course[courseCount].price);
                getchar();
                printf("������� ������������ ����� (� �����): ");
                scanf("%d", &course[courseCount].time);
                getchar();
                courseCount++;
                printf("���� ������� ��������!\n");
            }
            else
            {
                printf("���������� ������������ ���������� ������!\n");
            }
            break;
        case 2:
            if (courseCount > 0)
            {
                char searchName[50];
                printf("������� �������� ��� ������: ");
                fgets(searchName, sizeof(searchName), stdin);
                int found = SearchName(course, courseCount, searchName);
                if (found != -1)
                {
                    printf("------------------------------------------------\n");
                    printf("��������: %s", course[found].name);
                    printf("�������������: %s", course[found].instructor);
                    printf("����: %s", course[found].tema);
                    printf("�������: %.2f\n", course[found].rating);
                    printf("���������: %.2f\n", course[found].price);
                    printf("������������: %d\n", course[found].time);
                    printf("------------------------------------------------\n");
                }
                else
                {
                    printf("��������� � ����� ��������� �� �������.\n");
                }
            }
            else
            {
                printf("���� ������ �����.\n");
            }
            break;
        case 3:
            if (courseCount > 0)
            {
                double price;
                printf("������� ���� ��� ������: ");
                scanf("%lf", &price);
                int count = SearchPrice(course, courseCount, price);
                if (count > 0)
                {
                    for (int i = 0; i < courseCount; i++)
                    {
                        if (course[i].price == price)
                        {
                            printf("------------------------------------------------\n");
                            printf("��������: %s", course[i].name);
                            printf("�������������: %s", course[i].instructor);
                            printf("����: %s", course[i].tema);
                            printf("�������: %.2f\n", course[i].rating);
                            printf("���������: %.2f\n", course[i].price);
                            printf("������������: %d\n", course[i].time);
                            printf("------------------------------------------------\n");
                        }
                    }
                }
                else
                {
                    printf("��������� � ����� �� %.2lf �� �������.\n", price);
                }
            }
            else
            {
                printf("���� ������ �����.\n");
            }
            break;
        case 4:
            if (courseCount == 0)
            {
                printf("��� ��������� ������ ��� ����������\n");
            }
            else
            {
                bubbleSort(course, courseCount);
                printf("����� ������� ������������� �� �������� (�� ������� � �������)!\n");
                for (int i = 0; i < courseCount; i++)
                {
                    printf("------------------------------------------------\n");
                    printf("��������: %s", course[i].name);
                    printf("�������������: %s", course[i].instructor);
                    printf("����: %s", course[i].tema);
                    printf("�������: %.2f\n", course[i].rating);
                    printf("���������: %.2f\n", course[i].price);
                    printf("������������: %d\n", course[i].time);
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
                    printf("�� ������� �������� ������ � ����.\n");
                }
                else
                {
                    printf("������ ������� �������� � ����.\n");
                }
            }
            else
            {
                printf("���� ������ �����. ������ ���������� � ����.\n");
            }
            break;
        case 6:
            if (courseCount > 0)
            {
                int result = ReadFile(course, courseCount);
                if (result == 0)
                {
                    printf("������ ������� ��������� �� �����.\n");
                }
                else
                {
                    printf("�� ������� ��������� ������ �� �����.\n");
                }
            }
            else
            {
                printf("���� ������ �����. ������ ������ �� �����.\n");
            }
            break;
        case 7:
            printf("����� �� ���������\n");
            break;
        default:
            printf("������������ �����. ����������, ���������� �����\n");
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
        fprintf(file, "��������: %s", course[i].name);
        fprintf(file, "�������������: %s", course[i].instructor);
        fprintf(file, "����: %s", course[i].tema);
        fprintf(file, "�������: %.2f\n", course[i].rating);
        fprintf(file, "���������: %.2f\n", course[i].price);
        fprintf(file, "������������: %d\n", course[i].time);
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
        printf("������ ��� �������� �����");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}