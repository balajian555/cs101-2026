#include <stdio.h>
#include <string.h>

#define NAME_LENGTH 50
#define EMPLOYEE_COUNT 3

typedef struct employee {
    int id;
    int age;
    double salary;
    char name[NAME_LENGTH];
} employee_t;

void emp_info(employee_t emp);
int emp_average_age(employee_t emp[], int n);
int emp_writefile(employee_t emp[], int n);
int emp_readfile(employee_t emp[], int capacity);

void emp_info(employee_t emp) {
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %f\n\n", emp.salary);
}

int emp_average_age(employee_t emp[], int n) {
    int total_age = 0;
    if (n <= 0) return 0;
    for (int i = 0; i < n; i++) total_age += emp[i].age;
    return total_age / n;
}

int emp_writefile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "wb");
    if (fp == NULL) {
        perror("Cannot create employee.bin");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (fwrite(&emp[i], sizeof(employee_t), 1, fp) != 1) {
            perror("Cannot write employee data");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

int emp_readfile(employee_t emp[], int capacity) {
    FILE *fp = fopen("employee.bin", "rb");
    int count = 0;
    if (fp == NULL) {
        perror("Cannot open employee.bin");
        return 0;
    }
    while (count < capacity && fread(&emp[count], sizeof(employee_t), 1, fp) == 1) {
        printf("[%d] %d %s\n", count, emp[count].id, emp[count].name);
        count++;
    }
    fclose(fp);
    return count;
}

int main(void) {
    employee_t emp[EMPLOYEE_COUNT] = {0};
    employee_t read_emp[EMPLOYEE_COUNT] = {0};

    emp[0].id = 1;
    emp[0].age = 20;
    emp[0].salary = 30000.0;
    strcpy(emp[0].name, "IU");

    emp[1].id = 2;
    emp[1].age = 26;
    emp[1].salary = 36000.0;
    strcpy(emp[1].name, "taylor");

    emp[2].id = 3;
    emp[2].age = 31;
    emp[2].salary = 90000.0;
    strcpy(emp[2].name, "swift");

    if (!emp_writefile(emp, EMPLOYEE_COUNT)) return 1;
    printf("employee.bin created.\n\n");

    int read_count = emp_readfile(read_emp, EMPLOYEE_COUNT);
    printf("\nEmployees read: %d\n", read_count);
    for (int i = 0; i < read_count; i++) emp_info(read_emp[i]);
    printf("Average age = %d\n", emp_average_age(emp, EMPLOYEE_COUNT));
    return 0;
}
