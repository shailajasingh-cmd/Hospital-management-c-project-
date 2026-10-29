#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Patient
{
    int id;
    char name[50];
    char phone[15];
    int age;
    char disease[50];
    int admitted;
};

struct Patient patients[100];
int count = 0;

/* Clears leftover characters from the standard input buffer */
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Validates that a string contains only letters and spaces */
int isValidName(const char *str)
{
    int i, hasAlpha = 0;

    if (str[0] == '\0') return 0;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)str[i]))
        {
            hasAlpha = 1;
        }
        else if (str[i] != ' ')
        {
            return 0; // Contains non-alphabet and non-space characters
        }
    }
    return hasAlpha;
}

/* Validates that a string contains only digits and is within length limits */
int isValidDigits(const char *str, int minLen, int maxLen)
{
    int len = strlen(str);
    int i;

    if (len < minLen || len > maxLen) return 0;

    for (i = 0; i < len; i++)
    {
        if (!isdigit((unsigned char)str[i]))
        {
            return 0;
        }
    }
    return 1;
}

/* Reads and validates a valid numeric ID */
int getValidID(const char *prompt)
{
    char buffer[50];
    int id;

    while (1)
    {
        printf("%s", prompt);
        if (scanf(" %49s", buffer) == 1 && isValidDigits(buffer, 1, 9))
        {
            sscanf(buffer, "%d", &id);
            if (id > 0)
            {
                clearInputBuffer();
                return id;
            }
        }
        clearInputBuffer();
        printf("Invalid ID! Please enter positive digits only.\n");
    }
}

/* Reads and validates an alphabetic name */
void getValidName(const char *prompt, char *dest, int maxLen)
{
    while (1)
    {
        printf("%s", prompt);
        if (scanf(" %49[^\n]", dest) == 1 && isValidName(dest))
        {
            clearInputBuffer();
            return;
        }
        clearInputBuffer();
        printf("Invalid Name! Only alphabetic characters and spaces are allowed.\n");
    }
}

/* Reads and validates a phone number (10 digits) */
void getValidPhone(const char *prompt, char *dest)
{
    while (1)
    {
        printf("%s", prompt);
        if (scanf(" %14s", dest) == 1 && isValidDigits(dest, 10, 10))
        {
            clearInputBuffer();
            return;
        }
        clearInputBuffer();
        printf("Invalid Phone Number! Enter exactly 10 digits (0-9).\n");
    }
}

void registerPatient()
{
    if (count >= 100)
    {
        printf("Patient list is full!\n");
        return;
    }

    printf("\n--- Register New Patient ---\n");
    patients[count].id = getValidID("Enter Patient ID (digits only): ");
    getValidName("Enter Patient Name (alphabets only): ", patients[count].name, 50);
    getValidPhone("Enter Phone Number (10 digits): ", patients[count].phone);

    printf("Enter Patient Age: ");
    while (scanf("%d", &patients[count].age) != 1 || patients[count].age <= 0 || patients[count].age > 125)
    {
        clearInputBuffer();
        printf("Invalid Age! Enter a valid age (1-125): ");
    }
    clearInputBuffer();

    printf("Enter Disease: ");
    scanf(" %49[^\n]", patients[count].disease);
    clearInputBuffer();

    printf("Is patient admitted? (1=Yes, 0=No): ");
    while (scanf("%d", &patients[count].admitted) != 1 || (patients[count].admitted != 0 && patients[count].admitted != 1))
    {
        clearInputBuffer();
        printf("Invalid input! Enter 1 for Yes or 0 for No: ");
    }
    clearInputBuffer();

    count++;
    printf("\nPatient registered successfully!\n");
}

void searchPatient()
{
    int id, i, found = 0;

    id = getValidID("\nEnter Patient ID to search: ");

    for (i = 0; i < count; i++)
    {
        if (patients[i].id == id)
        {
            printf("\nPatient Found!\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Phone: %s\n", patients[i].phone);
            printf("Age: %d\n", patients[i].age);
            printf("Disease: %s\n", patients[i].disease);
            printf("Admitted: %s\n", patients[i].admitted == 1 ? "Yes" : "No");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Patient not found!\n");
    }
}

void updatePatient()
{
    int id, i, found = 0;
    struct Patient *p;

    id = getValidID("\nEnter Patient ID to update: ");

    for (i = 0; i < count; i++)
    {
        if (patients[i].id == id)
        {
            p = &patients[i];

            getValidName("Enter New Name (alphabets only): ", p->name, 50);
            getValidPhone("Enter New Phone Number (10 digits): ", p->phone);

            printf("Enter New Age: ");
            while (scanf("%d", &p->age) != 1 || p->age <= 0 || p->age > 125)
            {
                clearInputBuffer();
                printf("Invalid Age! Enter a valid age (1-125): ");
            }
            clearInputBuffer();

            printf("Enter New Disease: ");
            scanf(" %49[^\n]", p->disease);
            clearInputBuffer();

            printf("Is patient admitted? (1=Yes, 0=No): ");
            while (scanf("%d", &p->admitted) != 1 || (p->admitted != 0 && p->admitted != 1))
            {
                clearInputBuffer();
                printf("Invalid input! Enter 1 for Yes or 0 for No: ");
            }
            clearInputBuffer();

            printf("Patient details updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Patient not found!\n");
    }
}

void displayPatients()
{
    int i;

    if (count == 0)
    {
        printf("\nNo patients registered!\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");

    for (i = 0; i < count; i++)
    {
        printf("\nPatient ID: %d\n", patients[i].id);
        printf("Name: %s\n", patients[i].name);
        printf("Phone: %s\n", patients[i].phone);
        printf("Age: %d\n", patients[i].age);
        printf("Disease: %s\n", patients[i].disease);
        printf("Admitted: %s\n", patients[i].admitted == 1 ? "Yes" : "No");
    }
}

void countAdmittedPatients()
{
    int i, admittedCount = 0;

    for (i = 0; i < count; i++)
    {
        if (patients[i].admitted == 1)
        {
            admittedCount++;
        }
    }

    printf("\nTotal Admitted Patients: %d\n", admittedCount);
}

int main()
{
    int choice;

    do
    {
        printf("\n===== Hospital Patient Management System =====\n");
        printf("1. Register Patient\n");
        printf("2. Search Patient\n");
        printf("3. Update Patient Details\n");
        printf("4. Display All Patients\n");
        printf("5. Count Admitted Patients\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();
            printf("Invalid input! Please enter a number between 1 and 6.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                registerPatient();
                break;

            case 2:
                searchPatient();
                break;

            case 3:
                updatePatient();
                break;

            case 4:
                displayPatients();
                break;

            case 5:
                countAdmittedPatients();
                break;

            case 6:
                printf("Thank you for using the system!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}